
// (c) Copyright Dmitriy Shikhov 2017, 2019

#include <boost/test/unit_test.hpp>
#include <boost/test/tools/output_test_stream.hpp>
#include "utils/exception_catcher.hpp"

using pair_t = std::pair<std::string, size_t>;

BOOST_TEST_DONT_PRINT_LOG_VALUE(pair_t)

BOOST_AUTO_TEST_SUITE(exception_catcher)

BOOST_AUTO_TEST_CASE(test_exception_catcher)
{
    utils::exception_catcher catcher;

    BOOST_CHECK(catcher.empty());

    std::vector<std::string> error_messages{"a", "b", "c"};

    for (auto const& error_message : error_messages)
    {
        BOOST_CHECK_NO_THROW(
            catcher.catch_in(
                [&]
                {
                    throw std::runtime_error{error_message};
                }));
    }

    BOOST_CHECK(!catcher.empty());

    size_t i{0};

    catcher.apply_visitor_to_each(
        [&](std::exception_ptr exception_ptr)
        {
            BOOST_CHECK_EXCEPTION(
                rethrow_exception(exception_ptr), std::runtime_error,
                [&](std::runtime_error const& e)
                {
                    return e.what() == error_messages[i++];
                });
        });

    BOOST_CHECK(catcher.empty());
}

BOOST_AUTO_TEST_CASE(test_exception_catcher_nested)
{
    utils::exception_catcher catcher;

    BOOST_CHECK(catcher.empty());

    std::vector<std::string> error_messages{"a", "b", "c"};

    for (auto const& error_message : error_messages)
    {
        BOOST_CHECK_NO_THROW(
            catcher.catch_in(
                error_message + "+", [&]
                {
                    throw std::runtime_error{error_message};
                }));
    }

    BOOST_CHECK(!catcher.empty());

    size_t i{0};

    catcher.apply_visitor_to_each(
        [&](std::exception_ptr exception_ptr)
        {
            BOOST_CHECK_EXCEPTION(
                rethrow_exception(exception_ptr), std::runtime_error,
                [&](std::runtime_error const& e)
                {
                    return e.what() == error_messages[i++] + "+";
                });
        });

    BOOST_CHECK(catcher.empty());
}

BOOST_AUTO_TEST_CASE(test_simple_exception_visitor)
{
    std::vector<pair_t> visited;

    utils::simple_exception_visitor exception_visitor(
        [&visited](const char* what, size_t level)
        {
            visited.push_back(std::make_pair(what, level));
        });

    try
    {
        try
        {
            throw "first";
        }
        catch (...)
        {
            try
            {
                throw_with_nested(std::runtime_error{"middle"});
            }
            catch (...)
            {
                throw_with_nested(std::runtime_error{"last"});
            }
        }
    }
    catch (std::exception const& exception)
    {
        exception_visitor(exception);
    }

    std::vector<pair_t> visited_etalon{std::make_pair("last", 0),
                                       std::make_pair("middle", 1),
                                       std::make_pair("Unknown exception", 2)};

    BOOST_CHECK_EQUAL_COLLECTIONS(visited.begin(), visited.end(),
                                  visited_etalon.begin(), visited_etalon.end());
}

BOOST_AUTO_TEST_CASE(test_simple_exception_visitor_with_exception_ptr)
{
    std::vector<pair_t> visited;

    utils::simple_exception_visitor exception_visitor(
        [&visited](const char* what, size_t level)
        {
            visited.push_back(std::make_pair(what, level));
        });

    std::exception_ptr exception_ptr;
    try
    {
        try
        {
            throw "first";
        }
        catch (...)
        {
            try
            {
                throw_with_nested(std::runtime_error{"middle"});
            }
            catch (...)
            {
                throw_with_nested(std::runtime_error{"last"});
            }
        }
    }
    catch (...)
    {
        exception_ptr = std::current_exception();
    }

    exception_visitor(exception_ptr);

    std::vector<pair_t> visited_etalon{std::make_pair("last", 0),
                                       std::make_pair("middle", 1),
                                       std::make_pair("Unknown exception", 2)};

    BOOST_CHECK_EQUAL_COLLECTIONS(visited.begin(), visited.end(),
                                  visited_etalon.begin(), visited_etalon.end());
}

BOOST_AUTO_TEST_SUITE_END()
