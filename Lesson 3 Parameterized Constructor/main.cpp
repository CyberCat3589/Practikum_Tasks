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
    char div;
    in >> n >> div >> d;
    rational = Rational(n, d);
    
    return in;
}

ostream& operator<<(ostream& out, const Rational& rational)
{
    out << rational.Numerator() << "/" << rational.Denominator();
    return out;
}

int main() 
{
    Rational rational1, rational2;
    cin >> rational1 >> rational2;
    cout << rational1 << " "s << rational2;
}