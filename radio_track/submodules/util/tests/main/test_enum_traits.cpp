
// (c) Copyright Dmitriy Shikhov 2016, 2017, 2018, 2020

#include <utils/enum_traits.hpp>
#include <boost/test/unit_test.hpp>
#include <vector>

void test_is_equal()
{
    using utils::enum_traits::detail::is_equal;

    static_assert(is_equal("", ""), "");
    static_assert(is_equal("banana", "banana"), "");
    static_assert(!is_equal("banana1", "banana"), "");
    static_assert(!is_equal("banana", "banana2"), "");
    static_assert(!is_equal("banana1", "banana2"), "");
}

void test_optional()
{
    using std::optional;

    static_assert(!optional<int>(), "");
    static_assert(optional<int>(137), "");
    static_assert(optional<int>(137).value() == 137, "");

    constexpr const optional<int> opt;
    static_assert(opt.value_or(137) == 137, "");
}

ENUM(fruits, int, apple, banana, orange)

namespace trees
{
ENUM(fruits, int, apple, banana, orange)

struct multitree
{
    ENUM(fruits, int, apple, banana, orange)
};
}  // namespace trees

ENUM(fruits2, int, kiwi, (apple, 100), banana, orange)
ENUM_Q(fruits3, int, 100, kiwi, apple, banana, orange)

ENUM_REG(, fruits)
ENUM_REG(trees::, fruits)
ENUM_REG(trees::multitree::, fruits)
ENUM_REG(, fruits2)
ENUM_REG(, fruits3)

void test_scopes()
{
    using utils::enum_traits::detail::is_equal;
    using namespace utils::enum_traits;

    static_assert(is_equal(name<fruits>(), "fruits"), "");
    static_assert(is_equal(name<trees::fruits>(), "fruits"), "");
    static_assert(is_equal(name<trees::multitree::fruits>(), "fruits"), "");
}

void test_base_traits()
{
    using utils::enum_traits::detail::is_equal;
    using namespace utils::enum_traits;

    static_assert(is_equal(name<fruits>(), "fruits"), "");

    static_assert(values<fruits>().size() == 3, "");
    static_assert(values<fruits>().at(0).value() == fruits::apple, "");
    static_assert(values<fruits>().at(1).value() == fruits::banana, "");
    static_assert(values<fruits>().at(2).value() == fruits::orange, "");

    static_assert(names<fruits>().size() == 3, "");
    static_assert(is_equal(names<fruits>().at(0).value(), "apple"), "");
    static_assert(is_equal(names<fruits>().at(1).value(), "banana"), "");
    static_assert(is_equal(names<fruits>().at(2).value(), "orange"), "");

    static_assert(integrals<fruits>().size() == 3, "");
    static_assert(integrals<fruits>().at(0).value() == 0, "");
    static_assert(integrals<fruits>().at(1).value() == 1, "");
    static_assert(integrals<fruits>().at(2).value() == 2, "");
}

void test_correct_transformations()
{
    using utils::enum_traits::detail::is_equal;
    using namespace utils::enum_traits;

    static_assert(is_equal(to_string(fruits::apple), "apple"), "");
    static_assert(is_equal(to_string(fruits::banana), "banana"), "");
    static_assert(is_equal(to_string(fruits::orange), "orange"), "");

    static_assert(from_string<fruits>("apple") == fruits::apple, "");
    static_assert(from_string<fruits>("banana") == fruits::banana, "");
    static_assert(from_string<fruits>("orange") == fruits::orange, "");

    static_assert(to_integral(fruits::apple) == 0, "");
    static_assert(to_integral(fruits::banana) == 1, "");
    static_assert(to_integral(fruits::orange) == 2, "");

    static_assert(from_integral<fruits>(0) == fruits::apple, "");
    static_assert(from_integral<fruits>(1) == fruits::banana, "");
    static_assert(from_integral<fruits>(2) == fruits::orange, "");
}

void test_correct_transformations_nothrow()
{
    using utils::enum_traits::detail::is_equal;
    using namespace utils::enum_traits::nothrow;

    static_assert(is_equal(to_string(fruits::apple).value(), "apple"), "");
    static_assert(is_equal(to_string(fruits::banana).value(), "banana"), "");
    static_assert(is_equal(to_string(fruits::orange).value(), "orange"), "");

    static_assert(from_string<fruits>("apple").value() == fruits::apple, "");
    static_assert(from_string<fruits>("banana").value() == fruits::banana, "");
    static_assert(from_string<fruits>("orange").value() == fruits::orange, "");

    static_assert(to_integral(fruits::apple).value() == 0, "");
    static_assert(to_integral(fruits::banana).value() == 1, "");
    static_assert(to_integral(fruits::orange).value() == 2, "");

    static_assert(from_integral<fruits>(0).value() == fruits::apple, "");
    static_assert(from_integral<fruits>(1).value() == fruits::banana, "");
    static_assert(from_integral<fruits>(2).value() == fruits::orange, "");
}

void test_incorrect_transformations_nothrow()
{
    using utils::enum_traits::detail::is_equal;
    using namespace utils::enum_traits::nothrow;

    static_assert(!from_string<fruits>("cherry"), "");
    static_assert(!from_integral<fruits>(3), "");

    constexpr const auto opt1 = from_string<fruits>("cherry");
    static_assert(opt1.value_or(fruits::apple) == fruits::apple, "");

    constexpr const auto opt2 = from_integral<fruits>(3);
    static_assert(opt2.value_or(fruits::apple) == fruits::apple, "");
}

void test_explicit_values()
{
    using namespace utils::enum_traits;

    static_assert(to_integral(fruits2::kiwi) == 0, "");
    static_assert(to_integral(fruits2::apple) == 100, "");
    static_assert(to_integral(fruits2::banana) == 101, "");
    static_assert(to_integral(fruits2::orange) == 102, "");

    static_assert(from_integral<fruits2>(0) == fruits2::kiwi, "");
    static_assert(from_integral<fruits2>(100) == fruits2::apple, "");
    static_assert(from_integral<fruits2>(101) == fruits2::banana, "");
    static_assert(from_integral<fruits2>(102) == fruits2::orange, "");
}

void test_q_with_start_value()
{
    using namespace utils::enum_traits;

    static_assert(names<fruits3>().size() == 4, "");

    static_assert(to_integral(fruits3::kiwi) == 100, "");
    static_assert(to_integral(fruits3::apple) == 101, "");
    static_assert(to_integral(fruits3::banana) == 102, "");
    static_assert(to_integral(fruits3::orange) == 103, "");

    static_assert(from_integral<fruits3>(100) == fruits3::kiwi, "");
    static_assert(from_integral<fruits3>(101) == fruits3::apple, "");
    static_assert(from_integral<fruits3>(102) == fruits3::banana, "");
    static_assert(from_integral<fruits3>(103) == fruits3::orange, "");
}

BOOST_AUTO_TEST_SUITE(utils_enum_traits)

BOOST_AUTO_TEST_CASE(runtime_access)
{
    using namespace utils;

    {
        std::vector<fruits> vals;
        for (auto fruit : enum_traits::values<fruits>())
        {
            vals.push_back(fruit);
        }

        std::vector<fruits> vals_{
            {fruits::apple, fruits::banana, fruits::orange}};

        BOOST_CHECK(vals_ == vals);
    }
    {
        std::vector<enum_traits::string> vals;
        for (auto fruit : enum_traits::names<fruits>())
        {
            vals.push_back(fruit);
        }

        std::vector<enum_traits::string> vals_{{"apple", "banana", "orange"}};

        BOOST_CHECK(enum_traits::detail::is_equal(vals_[0], vals[0]));
        BOOST_CHECK(enum_traits::detail::is_equal(vals_[1], vals[1]));
        BOOST_CHECK(enum_traits::detail::is_equal(vals_[2], vals[2]));
    }
    {
        std::vector<int> vals;
        for (auto fruit : enum_traits::integrals<fruits>())
        {
            vals.push_back(fruit);
        }

        std::vector<int> vals_{{0, 1, 2}};

        BOOST_CHECK(vals_ == vals);
    }
}

BOOST_AUTO_TEST_SUITE_END()
