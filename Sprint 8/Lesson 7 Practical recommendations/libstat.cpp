#include "libstat.h"

void SumAggregation::PutValue(double value) {
    sum_ += value;
}

optional<double> SumAggregation::Get() const {
    return sum_;
}

void AggregateMaximum::PutValue(double value) {
    cur_max_ = max(value, cur_max_.value_or(value));
}

optional<double> AggregateMaximum::Get() const {
    return cur_max_;
}

void AggregatorAverage::PutValue(double value) {
    sum_.PutValue(value);
    ++count_;
}

optional<double> AggregatorAverage::Get() const {
    auto val = sum_.Get();
    if (!val || count_ == 0) {
        return nullopt;
    }

    return *val / count_;
}

void AggregStd::PutValue(double value) {
    sum_.PutValue(value);
    sum_sq_.PutValue(value * value);
    ++count_;
}

optional<double> AggregStd::Get() const {
    auto val = sum_.Get();
    auto val2 = sum_sq_.Get();

    if (!val || !val2 || count_ < 2) {
        return nullopt;
    }

    return ::std::sqrt((*val2 - *val * *val / count_) / count_);
}

void Mode::PutValue(double value) {
    const size_t new_count = ++counts_[round(value)];

    if (new_count > cur_count_) {
        cur_max_ = value;
        cur_count_ = new_count;
    }
}

optional<double> Mode::Get() const {
    return cur_max_;
}