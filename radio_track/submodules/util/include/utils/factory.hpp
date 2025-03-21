#pragma once

// (c) Copyright Dmitriy Shikhov 2012, 2013, 2017, 2023

#include <functional>
#include <map>
#include <utility>

namespace utils
{
template <typename KeyType, typename CreatorFunctionType>
class factory;

template <typename KeyType, typename ResultType, typename... ParameterTypes>
class factory<KeyType, ResultType(ParameterTypes...)>
{
public:
    factory()
        : default_creator_{
              [](auto...) -> ResultType
              {
                  return {};
              }}
    {
    }

    template <typename Creator>
    explicit factory(Creator&& default_creator)
        : default_creator_{std::forward<Creator>(default_creator)}
    {
    }

    template <typename Creator>
    bool registry(KeyType const& key, Creator&& creator)
    {
        return creators_.emplace(key, std::forward<Creator>(creator)).second;
    }

    bool unregistry(KeyType const& key)
    {
        return creators_.erase(key) != 0;
    }

    ResultType create(KeyType const& key, ParameterTypes... parameters) const
    {
        const auto creator = creators_.find(key);
        return (creator != creators_.end())
                   ? creator->second(
                         std::forward<ParameterTypes>(parameters)...)
                   : default_creator_(
                         std::forward<ParameterTypes>(parameters)...);
    }

    std::vector<KeyType> registered() const
    {
        std::vector<KeyType> keys;
        keys.reserve(creators_.size());
        for (auto& [key, _] : creators_)
        {
            keys.push_back(key);
        }
        return keys;
    }

private:
    using creator_type = std::function<ResultType(ParameterTypes...)>;

    std::map<KeyType, creator_type> creators_;
    creator_type default_creator_;
};

}  // namespace utils
