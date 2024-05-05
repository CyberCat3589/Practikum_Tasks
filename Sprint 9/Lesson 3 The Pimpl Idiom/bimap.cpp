#include "bimap.h"
#include <map>

struct BiMap::Impl
{
    bool Add(std::string_view key, std::string_view value)
    {
        // TODO: Реализуйте метод самостоятельно
        return false;
    }

    std::optional<std::string_view> FindValue(std::string_view key) const noexcept
    {
        // TODO: Реализуйте метод самостоятельно
        return std::nullopt;
    }

    std::optional<std::string_view> FindKey(std::string_view key) const noexcept
    {
        // TODO: Реализуйте метод самостоятельно
        return std::nullopt;
    }

  private:
    std::map<std::string, std::string> storage;
};

BiMap::BiMap() : impl_(std::make_unique<Impl>()) {}

BiMap::~BiMap() = default;
BiMap::BiMap(BiMap&&) noexcept = default;
BiMap& BiMap::operator=(BiMap&&) noexcept = default;

BiMap::BiMap(const BiMap& other) : impl_(other.impl_ ? std::make_unique<Impl>(*other.impl_) : nullptr){}

BiMap& BiMap::operator=(const BiMap& other)
{
    if(this != std::addressof(other))
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