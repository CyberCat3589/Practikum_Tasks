#include <map>
#include <numeric>
#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

class Rational {
public:

    Rational() = default;

    Rational(int numerator) : numerator_(numerator), denominator_(1) {}

    Rational(int numerator, int denominator) : numerator_(numerator), denominator_(denominator)
    {
        if(denominator == 0) throw domain_error("Создание дроби с 0 знаменателем!!!"s);
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

    Rational& operator+=(Rational right)
    {
        numerator_ = numerator_ * right.Denominator() + right.Numerator() * denominator_;
        denominator_ = denominator_ * right.Denominator();
        Normalize();

        return *this;
    }

    Rational& operator-=(Rational right)
    {
        numerator_ = numerator_ * right.Denominator() - right.Numerator() * denominator_;
        denominator_ = denominator_ * right.Denominator();
        Normalize();

        return *this;
    }

    Rational& operator*=(Rational right)
    {
        numerator_ *= right.Numerator();
        denominator_ *= right.Denominator();
        Normalize();

        return *this;
    }

    Rational& operator/=(Rational right)
    {
        if(right.Numerator() == 0) throw invalid_argument("Деление на ноль запрешено торговой федерацией!!!"s);

        numerator_ = numerator_ * right.Denominator();
        denominator_ = denominator_ * right.Numerator();
        Normalize();

        return *this;
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

Rational operator+(Rational right)
{
    return right;
}

Rational operator-(Rational right)
{
    return {-right.Numerator(), right.Denominator()};
}

Rational operator+(Rational left, Rational right)
{
    return left += right;
}

Rational operator-(Rational left, Rational right)
{
    return left -= right;
}

Rational operator*(Rational left, Rational right)
{
    return left *= right;
}

Rational operator/(Rational left, Rational right)
{
    return left /= right;
}

bool operator==(Rational left, Rational right)
{
    return (left.Numerator() == right.Numerator()) && (left.Denominator() == right.Denominator());
}

bool operator!=(Rational left, Rational right)
{
    return !(left == right);
}

bool operator<(Rational left, Rational right)
{
    return (left.Numerator() * right.Denominator()) < (right.Numerator() * left.Denominator());
}

bool operator>(Rational left, Rational right)
{
    return (left.Numerator() * right.Denominator()) > (right.Numerator() * left.Denominator());
}

bool operator<=(Rational left, Rational right)
{
    return (left < right) || (left == right);
}

bool operator>=(Rational left, Rational right)
{
    return (left > right) || (left == right);
}

int main() 
{
    try 
    {
        const Rational three_fifth{3, 5};
        const Rational zero;
        cout << three_fifth << " / " << zero << " = " << (three_fifth / zero) << endl;
    } 
    catch (const invalid_argument& e) 
    {
        cout << "Ошибка: "s << e.what() << endl;
    }
    try 
    {
        Rational value{3, 5};
        value /= Rational();
        // Следующая строка не должна выполниться
        cout << value << endl;
    } 
    catch (const invalid_argument& e) 
    {
        cout << "Ошибка: "s << e.what() << endl;
    }
}