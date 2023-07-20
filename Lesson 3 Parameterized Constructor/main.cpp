#include <map>
#include <numeric>
#include <vector>
#include <iostream>

using namespace std;

class Rational {
public:

    Rational() = default;

    Rational(int numerator) : numerator_(numerator), denominator_(1) {}

    Rational(int numerator, int denominator) : numerator_(numerator), denominator_(denominator)
    {
        numerator_ = numerator;
        denominator_ = denominator;
        Normalize();
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
    void Normalize() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

    int numerator_ = 0;
    int denominator_ = 1;
};

istream& operator>>(istream& in, Rational& rational)
{
    int n, d;
    char slash;
    in >> n >> slash >> d;
    rational = Rational(n, d);
    
    return in;
}

ostream& operator<<(ostream& out, const Rational& rational)
{
    out << rational.Numerator() << "/" << rational.Denominator();
    return out;
}

Rational operator+(Rational rational)
{
    return rational;
}

Rational operator-(Rational rational)
{
    return {-rational.Numerator(), rational.Denominator()};
}

Rational operator+(Rational left, Rational right)
{
    int numerator = left.Numerator() * right.Denominator() + right.Numerator() * left.Denominator();
    int denominator = left.Denominator() * right.Denominator();

    return {numerator, denominator};
}

Rational operator-(Rational left, Rational right)
{
    int numerator = left.Numerator() * right.Denominator() - right.Numerator() * left.Denominator();
    int denominator = left.Denominator() * right.Denominator();

    return {numerator, denominator};
}

int main() 
{
    Rational rational1, rational2;
    cout << "Введите первую дробь:" << endl;
    cin >> rational1;
    cout << "Введите вторую дробь:" << endl;
    cin >> rational2;

    cout << "Результат сложения дробей:" << endl;
    cout << rational1 + rational2 << endl;

    cout << "Результат вычитания дробей:" << endl;
    cout << rational1 - rational2 << endl;

    cout << "Результат операции унарного плюса:" << endl;
    cout << +rational1 << endl;

    cout << "Результат операции унарного минуса:" << endl;
    cout << -rational2 << endl;

    cout << rational1 << " "s << rational2;
}