#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

using namespace std;

class SumAggregation {
public:
    void PutValue(double value);
    optional<double> Get() const;

    static string_view GetValueName() {
        return "sum"sv;
    }

private:
    double sum_ = 0;
};

class AggregateMaximum {
public:
    void PutValue(double value);
    optional<double> Get() const;

    static string_view GetValueName() {
        return "max"sv;
    }

private:
    optional<double> cur_max_;
};

class AggregatorAverage {
public:
    void PutValue(double value);
    optional<double> Get() const;

    static string_view GetValueName() {
        return "mean"sv;
    }

private:
    ::SumAggregation sum_;
    size_t count_ = 0;
};

class AggregStd {
public:
    void PutValue(double value);
    optional<double> Get() const;

    static string_view GetValueName() {
        return "standard deviation"sv;
    }

private:
    ::SumAggregation sum_;
    ::SumAggregation sum_sq_;
    size_t count_ = 0;
};

class Mode {
public:
    void PutValue(double value);
    optional<double> Get() const;

    static string_view GetValueName() {
        return "mode"sv;
    }

private:
    ::unordered_map<double, size_t> counts_;
    optional<double> cur_max_;
    size_t cur_count_ = 0;
};

template <typename Aggreg>
class AggregPrinter {
public:
    void PutValue(double value) {
        inner_.PutValue(value);
    }

    void Print(ostream& out) const {
        auto val = inner_.Get();
        out << inner_.GetValueName() << " is "sv;
        if (val) {
            out << *val;
        } else {
            out << "undefined"sv;
        }
        out << endl;
    }

private:
    Aggreg inner_;
};

void TestStatAggregSum();
void TestStatAggregMax();
void TestStatAggregMean();
void TestStatAggregStandardDeviation();
void TestStatAggregMode();
void TestStatAggregPrinter();