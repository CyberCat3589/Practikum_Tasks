#include "libstat.h"

void statistics::aggregations::Sum::PutValue(double value)
{
    sum_ += value;
}

std::optional<double> statistics::aggregations::Sum::Get() const
{
    return sum_;
}

void statistics::aggregations::Max::PutValue(double value)
{
    cur_max_ = std::max(value, cur_max_.value_or(value));
}

std::optional<double> statistics::aggregations::Max::Get() const
{
    return cur_max_;
}

void statistics::aggregations::Mean::PutValue(double value)
{
    sum_.PutValue(value);
    ++count_;
}

std::optional<double> statistics::aggregations::Mean::Get() const
{
    auto val = sum_.Get();
    if (!val || count_ == 0)
    {
        return std::nullopt;
    }

    return *val / count_;
}

void statistics::aggregations::StandardDeviation::PutValue(double value)
{
    sum_.PutValue(value);
    sum_sq_.PutValue(value * value);
    ++count_;
}

std::optional<double> statistics::aggregations::StandardDeviation::Get() const
{
    auto val = sum_.Get();
    auto val2 = sum_sq_.Get();

    if (!val || !val2 || count_ < 2)
    {
        return std::nullopt;
    }

    return ::std::sqrt((*val2 - *val * *val / count_) / count_);
}

void statistics::aggregations::Mode::PutValue(double value)
{
    const size_t new_count = ++counts_[std::round(value)];

    if (new_count > cur_count_)
    {
        cur_max_ = value;
        cur_count_ = new_count;
    }
}

std::optional<double> statistics::aggregations::Mode::Get() const
{
    return cur_max_;
}