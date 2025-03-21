
// (c) Copyright Dmitriy Shikhov 2019

#include <boost/test/unit_test.hpp>
#include "utils/free_function_helper.hpp"

BOOST_AUTO_TEST_SUITE(free_function_helper)

BOOST_AUTO_TEST_CASE(test_free_function)
{
    using helper = utils::free_function_helper<int(int, int)>;

    bool is_sum_called = false;
    helper::function_type sum{
        [&is_sum_called](int a, int b) -> int
        {
            is_sum_called = true;
            return a + b;
        }};

    [](void* uptr, helper::free_function_type fptr)
    {
        const auto sum = helper::from_free_function(uptr, fptr);

        BOOST_TEST(sum(1, 2) == 3);
        //
    }(&sum, &helper::free_function);

    BOOST_TEST(is_sum_called);
}

BOOST_AUTO_TEST_SUITE_END()
