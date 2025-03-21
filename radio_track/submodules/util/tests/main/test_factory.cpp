
// (c) Copyright Dmitriy Shikhov 2017, 2023

#include <memory>
#include <string>
#include <boost/test/unit_test.hpp>
#include "utils/factory.hpp"

BOOST_AUTO_TEST_SUITE(factory)

struct something
{
    explicit something(int value1, int value2)
        : value1{value1}
        , value2{value2}
    {
    }

    int value1;
    int value2;
};

using factory_t = utils::factory<std::string, std::shared_ptr<something>(int)>;

std::shared_ptr<something> default_creator(int value)
{
    return std::make_shared<something>(value, -value);
}

BOOST_AUTO_TEST_CASE(explicit_default_creator)
{
    factory_t factory{default_creator};

    auto object = factory.create({}, 13);

    BOOST_TEST(object);
    BOOST_TEST(object->value1 == 13);
    BOOST_TEST(object->value2 == -13);
}

BOOST_AUTO_TEST_CASE(implicit_default_creator)
{
    factory_t factory{};

    auto object = factory.create({}, 555);

    BOOST_TEST(!object);
}

BOOST_AUTO_TEST_CASE(registry_unregistry)
{
    factory_t factory{};

    std::string key1{"key1"};
    std::string key2{"key2"};

    auto object1 = factory.create(key1, 42);

    BOOST_TEST(!object1);

    BOOST_TEST(
        factory.registry(
            key1, [](int value)
            {
                return std::make_shared<something>(value * 10, value * 20);
            }));

    auto object2 = factory.create(key1, 42);

    BOOST_TEST(object2);
    BOOST_TEST(object2->value1 == 420);
    BOOST_TEST(object2->value2 == 840);

    auto object3 = factory.create(key2, 42);

    BOOST_TEST(!object3);

    BOOST_TEST(factory.unregistry(key1));

    auto object4 = factory.create(key1, 42);

    BOOST_TEST(!object4);
}

BOOST_AUTO_TEST_CASE(reqistry_already_registered)
{
    factory_t factory{};

    std::string key{"key"};

    BOOST_TEST(
        factory.registry(
            key, [](int value)
            {
                return std::make_shared<something>(value, value + 1);
            }));

    BOOST_TEST(
        !factory.registry(
            key,
            [](int) -> std::shared_ptr<something>
            {
                throw "";
            }));

    auto object = factory.create(key, 137);

    BOOST_TEST(object);
    BOOST_TEST(object->value1 == 137);
    BOOST_TEST(object->value2 == 138);
}

BOOST_AUTO_TEST_CASE(unregistry_unregistered)
{
    factory_t factory{};

    BOOST_TEST(!factory.unregistry("key"));
}

BOOST_AUTO_TEST_CASE(registered)
{
    const auto creator = [](int value)
    {
        return value;
    };

    utils::factory<int, int(int)> factory{};

    auto registered = factory.registered();
    BOOST_TEST(registered.empty());

    BOOST_TEST(factory.registry(1, creator));
    registered = factory.registered();
    BOOST_TEST(registered.size() == 1);
    BOOST_TEST(registered == std::vector<int>({1}));

    BOOST_TEST(factory.registry(2, creator));
    BOOST_TEST(factory.registry(3, creator));
    registered = factory.registered();
    std::sort(begin(registered), end(registered));
    BOOST_TEST(registered.size() == 3);
    BOOST_TEST(registered == std::vector<int>({1, 2, 3}));
}

BOOST_AUTO_TEST_SUITE_END()
