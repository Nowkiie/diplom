#pragma once

// (c) Copyright Dmitriy Shikhov 2014, 2015, 2016, 2018

#include <memory>
#include <mutex>
#include <vector>

namespace utils
{
namespace detail
{
template <typename ElementType>
class blocks_pool
    : public std::enable_shared_from_this<blocks_pool<ElementType>>
{
    using std::enable_shared_from_this<
        blocks_pool<ElementType>>::shared_from_this;

public:
    blocks_pool(size_t blocks_count, size_t block_size)
        : buffer_size_(blocks_count * block_size)
        , buffer_(new ElementType[buffer_size_])
    {
        blocks_.resize(blocks_count);

        const auto buffer_start = buffer_.get();
        for (size_t i = 0; i < blocks_.size(); ++i)
        {
            blocks_[i] = buffer_start + (block_size * i);
        }
    }

    std::shared_ptr<ElementType> get_block()
    {
        ElementType* block = nullptr;

        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (blocks_.empty())
            {
                return {};
            }
            block = blocks_.back();
            blocks_.pop_back();
        }

        const auto this_valid_assurance = shared_from_this();
        return {
            block, [this, this_valid_assurance](ElementType* block)
            {
                std::lock_guard<std::mutex> lock(mutex_);
                blocks_.push_back(block);
            }};
    }

    size_t buffer_size() const
    {
        return buffer_size_;
    }

private:
    const size_t buffer_size_;
    const std::unique_ptr<ElementType[]> buffer_;
    std::vector<ElementType*> blocks_;
    std::mutex mutex_;
};

}  // namespace detail

template <typename ElementType>
using blocks_pool_t = std::shared_ptr<detail::blocks_pool<ElementType>>;

template <typename ElementType>
blocks_pool_t<ElementType> make_blocks_pool(size_t blocks_count,
                                            size_t block_size)
{
    return std::make_shared<detail::blocks_pool<ElementType>>(blocks_count,
                                                              block_size);
}

}  // namespace utils
