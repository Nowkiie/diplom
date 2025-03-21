#pragma once

// (c) Copyright Dmitriy Shikhov 2023

#include <cctype>
#include <ctime>
#include <atomic>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <memory>
#include <mutex>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>
#include <utils/enum_traits.hpp>
#include <utils/thread_name.hpp>

namespace utils::logging
{
// level ///////////////////////////////////////////////////////////////////////
ENUM(level, int, not_set, debug, info, warning, error, critical)
}  // namespace utils::logging
ENUM_REG(utils::logging::, level)

namespace utils::logging
{
namespace detail
{
class base
{
public:
    base() = default;
    virtual ~base() = default;

    base(const base&) = default;
    base& operator=(const base&) = default;
    base(base&&) = default;
    base& operator=(base&&) = default;
};

// log_record //////////////////////////////////////////////////////////////////
struct log_record
{
    using clock_type = std::chrono::system_clock;

    level lvl{level::not_set};
    clock_type::time_point time;
    std::string thread_name;
    std::string name;
    std::string message;

    auto make(level level, std::string const& message) const -> log_record
    {
        auto record(*this);
        record.lvl = level;
        record.time = std::chrono::system_clock::now();
        record.thread_name = utils::thread_name();
        record.message = message;
        return record;
    }
};

// level_mixin /////////////////////////////////////////////////////////////////
class level_mixin : public base
{
public:
    void set_level(level level);
    void set_level(std::string const& level_str);
    auto get_level() const -> level;
    auto is_enabled_for(level level) const -> bool;

private:
    std::atomic<level> level_{level::not_set};
};

inline void level_mixin::set_level(level level)
{
    level_ = level;
}

inline void level_mixin::set_level(std::string const& level_str)
{
    const auto lvl = utils::enum_traits::from_string<level>(level_str.c_str());
    set_level(lvl);
}

inline auto level_mixin::get_level() const -> level
{
    return level_;
}
inline auto level_mixin::is_enabled_for(level level) const -> bool
{
    return level >= level_;
}

}  // namespace detail

// formatter ///////////////////////////////////////////////////////////////////
class formatter : public detail::base
{
public:
    virtual auto format(detail::log_record const& record) -> std::string = 0;
};

using formatter_ptr = std::shared_ptr<formatter>;

// default_formatter ///////////////////////////////////////////////////////////
class default_formatter final : public formatter
{
public:
    auto format(detail::log_record const& record) -> std::string override;
};

inline auto default_formatter::format(detail::log_record const& record)
    -> std::string
{
    const auto upper = [](std::string s)
    {
        for (auto& c : s)
        {
            c = std::toupper(c);
        }
        return s;
    };

    const auto t = detail::log_record::clock_type::to_time_t(record.time);
    const auto tm = std::localtime(&t);
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                        record.time.time_since_epoch())
                        .count()
                    % 1000;

    std::stringstream stream;
    const auto fill = stream.fill();
    stream << ""                                                       //
           << std::put_time(tm, "%F %T")                               //
           << ","                                                      //
           << std::setfill('0') << std::setw(3) << ms                  //
           << std::setfill(fill)                                       //
           << std::put_time(tm, " %z")                                 //
           << ":"                                                      //
           << record.thread_name << ":"                                //
           << upper(utils::enum_traits::to_string(record.lvl)) << ":"  //
           << record.name << ": "                                      //
           << record.message                                           //
           << std::endl;
    return stream.str();
}

// handler /////////////////////////////////////////////////////////////////////
class handler : public detail::level_mixin
{
public:
    explicit handler(formatter_ptr formatter = {});
    void set_formatter(formatter_ptr formatter);
    void emit(detail::log_record const& record);

protected:
    virtual void emit(std::string const& text) = 0;

private:
    formatter_ptr formatter_{};
};

using handler_ptr = std::shared_ptr<handler>;

inline handler::handler(formatter_ptr formatter)
{
    set_formatter(std::move(formatter));
}
inline void handler::set_formatter(formatter_ptr formatter)
{
    formatter_ = formatter ? std::move(formatter)
                           : std::make_shared<default_formatter>();
}
inline void handler::emit(detail::log_record const& record)
{
    if (is_enabled_for(record.lvl))
    {
        if (formatter_)
        {
            const auto text = formatter_->format(record);
            emit(text);
        }
    }
}

// null_handler ////////////////////////////////////////////////////////////////
class null_handler final : public handler
{
protected:
    void emit(std::string const&) override {}
};

// stream_handler //////////////////////////////////////////////////////////////
class stream_handler : public handler
{
public:
    explicit stream_handler(std::ostream* stream);
    virtual void set_stream(std::ostream* stream);

protected:
    void emit(std::string const& text) override;

private:
    std::ostream* stream_;
};

inline stream_handler::stream_handler(std::ostream* stream)
    : stream_{stream}
{
}
inline void stream_handler::set_stream(std::ostream* stream)
{
    stream_ = stream;
}
inline void stream_handler::emit(std::string const& text)
{
    if (stream_)
    {
        *stream_ << text;
        stream_->flush();
    }
}

// concurrent_stream_handler ///////////////////////////////////////////////////
class concurrent_stream_handler : public stream_handler
{
public:
    explicit concurrent_stream_handler(std::ostream* stream);
    void set_stream(std::ostream* stream) override;

protected:
    void emit(std::string const& text) override;

private:
    std::mutex mutex_;
};

inline concurrent_stream_handler::concurrent_stream_handler(
    std::ostream* stream)
    : stream_handler{stream}
{
}
inline void concurrent_stream_handler::set_stream(std::ostream* stream)
{
    std::lock_guard<std::mutex> guard(mutex_);
    stream_handler::set_stream(stream);
}
inline void concurrent_stream_handler::emit(std::string const& text)
{
    std::lock_guard<std::mutex> guard(mutex_);
    stream_handler::emit(text);
}

// concurrent_file_handler /////////////////////////////////////////////////////
class concurrent_file_handler final : public concurrent_stream_handler
{
public:
    explicit concurrent_file_handler(std::filesystem::path const& path);

private:
    using concurrent_stream_handler::set_stream;

    std::ofstream file_stream_;
};

inline concurrent_file_handler::concurrent_file_handler(
    std::filesystem::path const& path)
    : concurrent_stream_handler{nullptr}
{
    if (const auto dir_path = path.parent_path(); !exists(dir_path))
    {
        if (is_directory(dir_path))
        {
            create_directories(dir_path);
        }
    }
    file_stream_.open(path, std::ofstream::out | std::ofstream::app);
    if (!file_stream_.is_open())
    {
        throw std::runtime_error("Logging: can't open file " + path.string());
    }
    concurrent_stream_handler::set_stream(&file_stream_);
}

// logger //////////////////////////////////////////////////////////////////////
class logger : public detail::level_mixin
{
public:
    explicit logger(std::string name = {}, handler_ptr handler = {});
    void set_handler(handler_ptr handler);
    void log(level level, std::string const& message) const;
    void debug(std::string const& message) const;
    void info(std::string const& message) const;
    void warning(std::string const& message) const;
    void error(std::string const& message) const;
    void critical(std::string const& message) const;

private:
    detail::log_record record_{};
    handler_ptr handler_{};
};

inline logger::logger(std::string name, handler_ptr handler)
{
    record_.name = std::move(name);
    set_handler(std::move(handler));
}
inline void logger::set_handler(handler_ptr handler)
{
    handler_ = handler ? std::move(handler) : std::make_shared<null_handler>();
}
inline void logger::log(level level, std::string const& message) const
{
    if (is_enabled_for(level))
    {
        const auto record = record_.make(level, message);
        handler_->emit(record);
    }
}
inline void logger::debug(std::string const& message) const
{
    log(level::debug, message);
}
inline void logger::info(std::string const& message) const
{
    log(level::info, message);
}
inline void logger::warning(std::string const& message) const
{
    log(level::warning, message);
}
inline void logger::error(std::string const& message) const
{
    log(level::error, message);
}
inline void logger::critical(std::string const& message) const
{
    log(level::critical, message);
}

}  // namespace utils::logging
