#include <iostream>
#include <string>

using namespace std;

struct Circle
{
    double x;
    double y;
    double r;
};

struct Dumbbell
{
    Circle circle1;
    Circle circle2;
    string text;
};

struct DumbbellHash
{
    // реализуйте хешер для Dumbbell
};

int main()
{
    DumbbellHash hash;
    Dumbbell dumbbell{{10, 11.5, 2.3}, {3.14, 15, -8}, "abc"s};
    cout << "Dumbbell hash "s << hash(dumbbell);
}