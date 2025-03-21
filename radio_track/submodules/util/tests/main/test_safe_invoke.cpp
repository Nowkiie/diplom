
// (c) Copyright Dmitriy Shikhov 2018

#include <memory>
#include <boost/test/unit_test.hpp>
#include "utils/safe_invoke.hpp"

BOOST_AUTO_TEST_SUITE(safe_invoke)

class something
{
public:
    explicit something()
        : value1_{}
        , value2_{}
    {
    }

    void non_const_memfn()
    {
        non_const_memfn_i();
    }

    void const_memfn() const
    {
        const_memfn_i();
    }

    int non_const_memfn_i()
    {
        return non_const_memfn_i_param(1);
    }

    int const_memfn_i() const
    {
        return const_memfn_i_param(2);
    }

    int non_const_memfn_i_param(int v)
    {
        value1_ = v;
        return value();
    }

    int const_memfn_i_param(int v) const
    {
        value2_ = v;
        return value();
    }

    something* this_ptr()
    {
        return this;
    }

    int value() const
    {
        return value1_ + value2_;
    }

private:
    int value1_;
    mutable int value2_;
};

BOOST_AUTO_TEST_SUITE(raw_ptr)

BOOST_AUTO_TEST_CASE(non_const_memfn)
{
    something object;

    utils::safe_invoke(&something::non_const_memfn, &object);

    BOOST_TEST(object.value() == 1);
}

BOOST_AUTO_TEST_CASE(const_memfn)
{
    something object;

    utils::safe_invoke(&something::const_memfn, &object);

    BOOST_TEST(object.value() == 2);
}

BOOST_AUTO_TEST_CASE(non_const_memfn_i)
{
    something object;

    auto v = utils::safe_invoke(&something::non_const_memfn_i, &object);

    static_assert(std::is_same_v<decltype(v), std::optional<int>>);

    BOOST_TEST(!!v);
    BOOST_TEST((v == 1));
    BOOST_TEST(object.value() == 1);
}

BOOST_AUTO_TEST_CASE(const_memfn_i)
{
    something object;

    auto v = utils::safe_invoke(&something::const_memfn_i, &object);

    static_assert(std::is_same_v<decltype(v), std::optional<int>>);

    BOOST_TEST(!!v);
    BOOST_TEST((v == 2));
    BOOST_TEST(object.value() == 2);
}

BOOST_AUTO_TEST_CASE(non_const_memfn_i_param)
{
    const int e = 3;
    something object;

    auto v =
        utils::safe_invoke(&something::non_const_memfn_i_param, &object, e);

    static_assert(std::is_same_v<decltype(v), std::optional<int>>);

    BOOST_TEST(!!v);
    BOOST_TEST((v == e));
    BOOST_TEST(object.value() == e);
}

BOOST_AUTO_TEST_CASE(const_memfn_i_param)
{
    const int e = 4;
    something object;

    auto v = utils::safe_invoke(&something::const_memfn_i_param, &object, e);

    static_assert(std::is_same_v<decltype(v), std::optional<int>>);

    BOOST_TEST(!!v);
    BOOST_TEST((v == e));
    BOOST_TEST(object.value() == e);
}

BOOST_AUTO_TEST_CASE(pointer)
{
    something object;

    auto v = utils::safe_invoke(&something::this_ptr, &object);

    static_assert(std::is_same_v<decltype(v), something*>);

    BOOST_TEST(!!v);
    BOOST_TEST((v == &object));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(null_ptr)

BOOST_AUTO_TEST_CASE(non_const_memfn)
{
    something* ptr = nullptr;
    utils::safe_invoke(&something::non_const_memfn, ptr);
}

BOOST_AUTO_TEST_CASE(const_memfn)
{
    something* ptr = nullptr;
    utils::safe_invoke(&something::const_memfn, ptr);
}

BOOST_AUTO_TEST_CASE(non_const_memfn_i)
{
    something* ptr = nullptr;
    auto v = utils::safe_invoke(&something::non_const_memfn_i, ptr);

    static_assert(std::is_same_v<decltype(v), std::optional<int>>);

    BOOST_TEST(!v);
}

BOOST_AUTO_TEST_CASE(const_memfn_i)
{
    something* ptr = nullptr;
    auto v = utils::safe_invoke(&something::const_memfn_i, ptr);

    static_assert(std::is_same_v<decltype(v), std::optional<int>>);

    BOOST_TEST(!v);
}

BOOST_AUTO_TEST_CASE(non_const_memfn_i_param)
{
    something* ptr = nullptr;
    auto v = utils::safe_invoke(&something::non_const_memfn_i_param, ptr, 0);

    static_assert(std::is_same_v<decltype(v), std::optional<int>>);

    BOOST_TEST(!v);
}

BOOST_AUTO_TEST_CASE(const_memfn_i_param)
{
    something* ptr = nullptr;
    auto v = utils::safe_invoke(&something::const_memfn_i_param, ptr, 0);

    static_assert(std::is_same_v<decltype(v), std::optional<int>>);

    BOOST_TEST(!v);
}

BOOST_AUTO_TEST_CASE(pointer)
{
    something* ptr = nullptr;
    auto v = utils::safe_invoke(&something::this_ptr, ptr);

    static_assert(std::is_same_v<decltype(v), something*>);

    BOOST_TEST(!v);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(smart_ptr)

BOOST_AUTO_TEST_CASE(non_const_memfn)
{
    auto ptr = std::make_shared<something>();

    utils::safe_invoke(&something::non_const_memfn, ptr);

    BOOST_TEST(ptr->value() == 1);
}

BOOST_AUTO_TEST_CASE(const_memfn)
{
    auto ptr = std::make_shared<something>();

    utils::safe_invoke(&something::const_memfn, ptr);

    BOOST_TEST(ptr->value() == 2);
}

BOOST_AUTO_TEST_CASE(non_const_memfn_i)
{
    auto ptr = std::make_shared<something>();

    auto v = utils::safe_invoke(&something::non_const_memfn_i, ptr);

    static_assert(std::is_same_v<decltype(v), std::optional<int>>);

    BOOST_TEST(!!v);
    BOOST_TEST((v == 1));
    BOOST_TEST(ptr->value() == 1);
}

BOOST_AUTO_TEST_CASE(const_memfn_i)
{
    auto ptr = std::make_shared<something>();

    auto v = utils::safe_invoke(&something::const_memfn_i, ptr);

    static_assert(std::is_same_v<decltype(v), std::optional<int>>);

    BOOST_TEST(!!v);
    BOOST_TEST((v == 2));
    BOOST_TEST(ptr->value() == 2);
}

BOOST_AUTO_TEST_CASE(non_const_memfn_i_param)
{
    const int e = 3;
    auto ptr = std::make_shared<something>();

    auto v = utils::safe_invoke(&something::non_const_memfn_i_param, ptr, e);

    static_assert(std::is_same_v<decltype(v), std::optional<int>>);

    BOOST_TEST(!!v);
    BOOST_TEST((v == e));
    BOOST_TEST(ptr->value() == e);
}

BOOST_AUTO_TEST_CASE(const_memfn_i_param)
{
    const int e = 4;
    auto ptr = std::make_shared<something>();

    auto v = utils::safe_invoke(&something::const_memfn_i_param, ptr, e);

    static_assert(std::is_same_v<decltype(v), std::optional<int>>);

    BOOST_TEST(!!v);
    BOOST_TEST((v == e));
    BOOST_TEST(ptr->value() == e);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
