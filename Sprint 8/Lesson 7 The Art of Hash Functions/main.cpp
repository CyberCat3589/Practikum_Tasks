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
    size_t operator()(const Dumbbell& dumbbell)
    {
        size_t h_c1_x = double_hasher(dumbbell.circle1.x);
        size_t h_c1_y = double_hasher(dumbbell.circle1.y);
        size_t h_c1_r = double_hasher(dumbbell.circle1.r);

        size_t h_c1 = h_c1_x + h_c1_y * 22 + h_c1_r * 22 * 22;

        size_t h_c2_x = double_hasher(dumbbell.circle2.x);
        size_t h_c2_y = double_hasher(dumbbell.circle2.y);
        size_t h_c2_r = double_hasher(dumbbell.circle2.r);

        size_t h_c2 = h_c2_x + h_c2_y * 22 + h_c2_r * 22 * 22;

        return (h_c1 + h_c2 * (22*22*22) + str_hasher(dumbbell.text));
    }

  private:
    hash<string> str_hasher;
    hash<double> double_hasher;
};

int main()
{
    DumbbellHash hash;
    Dumbbell dumbbell{{10, 11.5, 2.3}, {3.14, 15, -8}, "abc"s};
    cout << "Dumbbell hash "s << hash(dumbbell);
}