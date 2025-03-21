
// (c) Copyright Dmitriy Shikhov 2016, 2019

#include <boost/test/unit_test.hpp>
#include "utils/has_field.hpp"

struct a
{
    int x;
    int val;
    int z;

    UTILS_FIELDS(x, val, z)
};

struct b
{
};

struct c
{
    int x;
    int y;

    UTILS_FIELDS(x, y)
};

BOOST_AUTO_TEST_SUITE(has_field)

BOOST_AUTO_TEST_CASE(test_has_field)
{
    static_assert(utils::has_field<a>("x") == true, "");
    static_assert(utils::has_field<a>("y") == false, "");
    static_assert(utils::has_field<a>("z") == true, "");

    static_assert(utils::has_field<b>("x") == false, "");
}

BOOST_AUTO_TEST_CASE(test_fields)
{
    std::vector<utils::detail::string> fields_etalon = {"x", "val", "z"};
    std::vector<utils::detail::string> fields;

    for (auto field : a::fields())
    {
        fields.push_back(field);
    }

    BOOST_CHECK(fields == fields_etalon);
}

BOOST_AUTO_TEST_CASE(test_index_field_and_get)
{
    static_assert(utils::index_field<a>("val") == 1, "");

    a v{1, 2, 3};

    BOOST_CHECK_EQUAL(v.get<utils::index_field<a>("val")>(), 2);
}

BOOST_AUTO_TEST_CASE(test_get_field)
{
    a v{1, 2, 3};

    BOOST_CHECK(utils::get_field<0>(v) == 1);
}

BOOST_AUTO_TEST_CASE(test_call_if_field_exist)
{
    a v{1, 2, 3};

    UTILS_CALL_IF_FIELD_EXIST(
        v, x,
        [](auto x)
        {
            BOOST_CHECK(x == 1);
        });

    UTILS_CALL_IF_FIELD_EXIST(
        v, val,
        [](auto val)
        {
            BOOST_CHECK(val == 2);
        });

    UTILS_CALL_IF_FIELD_EXIST(
        v, noexist,
        [](auto)
        {
            BOOST_ERROR("no exist field!");
        });
}

BOOST_AUTO_TEST_CASE(test_call_if_field_exist_for_ref)
{
    a v{1, 2, 3};
    a& ref = v;

    UTILS_CALL_IF_FIELD_EXIST(
        ref, x,
        [](auto x)
        {
            BOOST_CHECK(x == 1);
        });
}

BOOST_AUTO_TEST_CASE(test_has_field_vs2015_bug)
{
    static_assert(utils::has_field<a>("x") == true, "");
    static_assert(utils::has_field<c>("x") == true, "");
}

BOOST_AUTO_TEST_SUITE_END()
