#include <cassert>
#include <string>

using namespace std;

class House
{
    // Реализуйте самостоятельно
};

class Resources
{
    // Реализуйте самостоятельно
};

struct HouseSpecification
{
    int length = 0;
    int width = 0;
    int height = 0;
};

class Builder
{
    // Реализуйте самостоятельно
};

int main()
{
    Resources resources{10000};
    Builder builder1{resources};
    Builder builder2{resources};

    House house1 = builder1.BuildHouse(HouseSpecification{12, 9, 3});
    assert(house1.GetLength() == 12);
    assert(house1.GetWidth() == 9);
    assert(house1.GetHeight() == 3);
    cout << resources.GetBrickCount() << " bricks left"s << endl;

    House house2 = builder2.BuildHouse(HouseSpecification{8, 6, 3});
    assert(house2.GetLength() == 8);
    cout << resources.GetBrickCount() << " bricks left"s << endl;

    House banya = builder1.BuildHouse(HouseSpecification{4, 3, 2});
    assert(banya.GetHeight() == 2);
    cout << resources.GetBrickCount() << " bricks left"s << endl;
}