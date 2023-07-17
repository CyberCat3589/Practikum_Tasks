#include <map>
#include <numeric>
#include <vector>
#include <iostream>

using namespace std;

class Rational {
public:

    Rational() = default;

    Rational(int numerator)
    {
        numerator_ = numerator;
        denominator_ = 1;
    }

    Rational(int numerator, int denominator)
    {
        pair<int, int> fr = ShortenFraction(numerator, denominator);
        numerator_ = fr.first;
        denominator_ = fr.second;
    }

    int Numerator() const 
    {
        return numerator_;
    }

    int Denominator() const 
    {
        return denominator_;
    }

private:
    int numerator_ = 0;
    int denominator_ = 1;

    pair<int, int> ShortenFraction(const int& numerator, const int& denominator)
    {
        pair<int, int> result_fraction(numerator, denominator);

        int divisor = gcd(numerator, denominator);

        if(denominator < 0)
        {
            result_fraction.first *= -1;
            result_fraction.second *= -1;
        }

        result_fraction.first /= divisor;
        result_fraction.second /= divisor;
        
        return result_fraction;
    }
};

Rational Add(Rational r1, Rational r2) {
    int numerator = r1.Numerator() * r2.Denominator() + r2.Numerator() * r1.Denominator();
    int denominator = r1.Denominator() * r2.Denominator();
    // Создаём и возвращаем дробь с заданным числителем и знаменателем
    return Rational{numerator, denominator};
}
int main() {
    Rational zero;     // Дробь 0/1 = 0
    const Rational seven(7); // Дробь 7/1 = 7
    const Rational one_third(1, 3); // Дробь 1/3
    vector<Rational> numbers;
    numbers.push_back(Rational{7, 8});
    // Следующие 2 строки эквивалентны - добавляют в numbers дробь 3/1
    numbers.push_back(Rational{3});
    numbers.push_back(3);
    Rational sum = Add(Rational{1,6}, one_third);
    // Выведет 1/2
    cout << sum.Numerator() << "/" << sum.Denominator();
}