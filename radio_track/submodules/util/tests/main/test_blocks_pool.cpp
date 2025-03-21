
// (c) Copyright Dmitriy Shikhov 2018

#include <boost/test/unit_test.hpp>
#include "utils/blocks_pool.hpp"

BOOST_AUTO_TEST_SUITE(blocks_pool)

BOOST_AUTO_TEST_CASE(get_block)
{
    auto pool = utils::make_blocks_pool<int>(4, 1024);

    auto block1 = pool->get_block();
    auto block2 = pool->get_block();
    auto block3 = pool->get_block();
    auto block4 = pool->get_block();
    BOOST_CHECK(block1);
    BOOST_CHECK(block2);
    BOOST_CHECK(block3);
    BOOST_CHECK(block4);

    auto block5 = pool->get_block();
    BOOST_CHECK(!block5);

    block1.reset();

    block5 = pool->get_block();
    BOOST_CHECK(block5);
}

BOOST_AUTO_TEST_SUITE_END()
