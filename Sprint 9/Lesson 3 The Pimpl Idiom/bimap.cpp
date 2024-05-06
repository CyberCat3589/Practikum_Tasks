#include "bimap.h"
#include <unordered_map>
#include<string>
#include <deque>
#include <cassert>
#include <iostream>

struct KeyVal
{
    std::string key;
    std::string value;
};

struct BiMap::Impl
{
    bool Add(std::string_view key, std::string_view value)
    {
        if(key_to_value.count(key) || value_to_key.count(value))
        {
            return false;
        }

        storage.push_back({std::string(key), std::string(value)});

        KeyVal kv = storage.back();

        key_to_value[kv.key] = kv.value;
        value_to_key[kv.value] = kv.key;

        std::cout << "Добавлен ключ " << key_to_value[kv.value]
        << " Добавлено значение " << value_to_key[kv.key] << std::endl;

        return true;
    }

    std::optional<std::string_view> FindValue(std::string_view key) const noexcept
    {
        if(auto it = key_to_value.find(key); it != key_to_value.end())
        {
            std::cout << "Value - " << it->second;
            return it->second;
        }
        std::cout << "NULL";
        return std::nullopt;
    }

    std::optional<std::string_view> FindKey(std::string_view value) const noexcept
    {
        if(auto it = value_to_key.find(value); it != value_to_key.end())
        {
            return it->second;
        }
        return std::nullopt;
    }

  private:
    std::unordered_map<std::string_view, std::string_view> key_to_value;
    std::unordered_map<std::string_view, std::string_view> value_to_key;
    std::deque<KeyVal> storage;
};

BiMap::BiMap() : impl_(std::make_unique<Impl>()) {}

BiMap::~BiMap() = default;
BiMap::BiMap(BiMap&& other) noexcept = default;
BiMap& BiMap::operator=(BiMap&&) noexcept = default;

BiMap::BiMap(const BiMap& other) : impl_(other.impl_ ? std::make_unique<Impl>(*other.impl_) : nullptr){}

BiMap& BiMap::operator=(const BiMap& other)
{
    if (this != std::addressof(other))
    {
        impl_ = other.impl_ ? std::make_unique<Impl>(*other.impl_) : nullptr;
    }
    return *this;
}

bool BiMap::Add(std::string_view key, std::string_view value)
{
    return impl_->Add(key, value);
}

std::optional<std::string_view> BiMap::FindValue(std::string_view key) const noexcept
{
    return impl_->FindValue(key);
}

std::optional<std::string_view> BiMap::FindKey(std::string_view value) const noexcept
{
    return impl_->FindKey(value);
}