
// (c) Copyright Dmitriy Shikhov 2017, 2020

#include <boost/test/unit_test.hpp>
#include "utils/integer_cast.hpp"

BOOST_AUTO_TEST_SUITE(integer_cast)

// throw version
BOOST_AUTO_TEST_SUITE(throw_version)

template <typename From, typename To>
void try_cast_max()
{
    utils::integer_cast<To>(std::numeric_limits<From>::max());
}

template <typename From, typename To>
void try_cast_min()
{
    utils::integer_cast<To>(std::numeric_limits<From>::min());
}

BOOST_AUTO_TEST_SUITE(unsigned_to_unsigned)

BOOST_AUTO_TEST_CASE(good)
{
    BOOST_CHECK_EQUAL(utils::integer_cast<uint32_t>(uint16_t{64000}), 64000);
    BOOST_CHECK_EQUAL(utils::integer_cast<uint16_t>(uint32_t{64000}), 64000);
    BOOST_CHECK_EQUAL(utils::integer_cast<uint32_t>(uint32_t{64000}), 64000);
}

BOOST_AUTO_TEST_CASE(too_big)
{
    BOOST_CHECK_THROW((try_cast_max<uint32_t, uint16_t>()),
                      utils::integer_cast_error);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(signed_to_signed)

BOOST_AUTO_TEST_CASE(good)
{
    BOOST_CHECK_EQUAL(utils::integer_cast<int32_t>(int16_t{32000}), 32000);
    BOOST_CHECK_EQUAL(utils::integer_cast<int16_t>(int32_t{32000}), 32000);
    BOOST_CHECK_EQUAL(utils::integer_cast<int32_t>(int32_t{32000}), 32000);

    BOOST_CHECK_EQUAL(utils::integer_cast<int32_t>(int16_t{-32000}), -32000);
    BOOST_CHECK_EQUAL(utils::integer_cast<int16_t>(int32_t{-32000}), -32000);
    BOOST_CHECK_EQUAL(utils::integer_cast<int32_t>(int32_t{-32000}), -32000);
}

BOOST_AUTO_TEST_CASE(too_big)
{
    BOOST_CHECK_THROW((try_cast_max<int32_t, int16_t>()),
                      utils::integer_cast_error);
}

BOOST_AUTO_TEST_CASE(too_small)
{
    BOOST_CHECK_THROW((try_cast_min<int32_t, int16_t>()),
                      utils::integer_cast_error);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(signed_to_unsigned)

BOOST_AUTO_TEST_CASE(good)
{
    BOOST_CHECK_EQUAL(utils::integer_cast<uint32_t>(int16_t{32000}), 32000);
}

BOOST_AUTO_TEST_CASE(too_big)
{
    BOOST_CHECK_THROW((try_cast_max<int32_t, uint16_t>()),
                      utils::integer_cast_error);
}

BOOST_AUTO_TEST_CASE(negative_value)
{
    BOOST_CHECK_THROW(utils::integer_cast<uint32_t>(-1),
                      utils::integer_cast_error);

    BOOST_CHECK_THROW((try_cast_min<int32_t, uint32_t>()),
                      utils::integer_cast_error);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(unsigned_to_signed)

BOOST_AUTO_TEST_CASE(good)
{
    BOOST_CHECK_EQUAL(utils::integer_cast<int32_t>(uint16_t{64000}), 64000);
}

BOOST_AUTO_TEST_CASE(too_big)
{
    BOOST_CHECK_THROW((try_cast_max<uint32_t, int32_t>()),
                      utils::integer_cast_error);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

// nothrow version
BOOST_AUTO_TEST_SUITE(nothrow_version)

template <typename From, typename To>
auto try_cast_max()
{
    return utils::try_integer_cast<To>(std::numeric_limits<From>::max());
}

template <typename From, typename To>
auto try_cast_min()
{
    return utils::try_integer_cast<To>(std::numeric_limits<From>::min());
}

BOOST_AUTO_TEST_SUITE(unsigned_to_unsigned)

BOOST_AUTO_TEST_CASE(good)
{
    BOOST_CHECK_EQUAL(
        utils::try_integer_cast<uint32_t>(uint16_t{64000}).value(), 64000);
    BOOST_CHECK_EQUAL(
        utils::try_integer_cast<uint16_t>(uint32_t{64000}).value(), 64000);
    BOOST_CHECK_EQUAL(
        utils::try_integer_cast<uint32_t>(uint32_t{64000}).value(), 64000);
}

BOOST_AUTO_TEST_CASE(too_big)
{
    BOOST_TEST(!(try_cast_max<uint32_t, uint16_t>().has_value()));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(signed_to_signed)

BOOST_AUTO_TEST_CASE(good)
{
    BOOST_CHECK_EQUAL(utils::try_integer_cast<int32_t>(int16_t{32000}).value(),
                      32000);
    BOOST_CHECK_EQUAL(utils::try_integer_cast<int16_t>(int32_t{32000}).value(),
                      32000);
    BOOST_CHECK_EQUAL(utils::try_integer_cast<int32_t>(int32_t{32000}).value(),
                      32000);

    BOOST_CHECK_EQUAL(utils::try_integer_cast<int32_t>(int16_t{-32000}).value(),
                      -32000);
    BOOST_CHECK_EQUAL(utils::try_integer_cast<int16_t>(int32_t{-32000}).value(),
                      -32000);
    BOOST_CHECK_EQUAL(utils::try_integer_cast<int32_t>(int32_t{-32000}).value(),
                      -32000);
}

BOOST_AUTO_TEST_CASE(too_big)
{
    BOOST_TEST(!(try_cast_max<int32_t, int16_t>().has_value()));
}

BOOST_AUTO_TEST_CASE(too_small)
{
    BOOST_TEST(!(try_cast_min<int32_t, int16_t>().has_value()));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(signed_to_unsigned)

BOOST_AUTO_TEST_CASE(good)
{
    BOOST_CHECK_EQUAL(utils::try_integer_cast<uint32_t>(int16_t{32000}).value(),
                      32000);
}

BOOST_AUTO_TEST_CASE(too_big)
{
    BOOST_TEST(!(try_cast_max<int32_t, uint16_t>().has_value()));
}

BOOST_AUTO_TEST_CASE(negative_value)
{
    BOOST_TEST(!utils::try_integer_cast<uint32_t>(-1).has_value());
    BOOST_TEST(!(try_cast_min<int32_t, uint32_t>().has_value()));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(unsigned_to_signed)

BOOST_AUTO_TEST_CASE(good)
{
    BOOST_CHECK_EQUAL(utils::try_integer_cast<int32_t>(uint16_t{64000}).value(),
                      64000);
}

BOOST_AUTO_TEST_CASE(too_big)
{
    BOOST_TEST(!(try_cast_max<uint32_t, int32_t>().has_value()));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
