#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class House
{
  public:
    // clang-format off
    House(int length, int width, int height) : length_(length), width_(width), height_(height){}
    // clang-format on

    int GetLength() const
    {
        return length_;
    }

    int GetWidth() const
    {
        return width_;
    }

    int GetHeight() const
    {
        return height_;
    }

  private:
    int length_;
    int width_;
    int height_;
};

class Resources
{
  public:
    // clang-format off
    Resources(int brick_count) : count_(brick_count){}
    // clang-format on

    void TakeBricks(int count)
    {
        if (count < 0 || count > count_)
        {
            throw out_of_range("Invalid count"s);
        }
        count_ -= count;
    }

    int GetBrickCount() const
    {
        return count_;
    }

  private:
    int count_;
};

struct HouseSpecification
{
    int length = 0;
    int width = 0;
    int height = 0;
};

class Builder
{
  public:
    // clang-format off
    Builder(Resources& resources) : resources_(resources){}
    // clang-format on

    House BuildHouse(HouseSpecification spec)
    {
        int bricks_count = (((spec.length + spec.width) * 2) * spec.height) * 32;
        if (resources_.GetBrickCount() < bricks_count)
        {
            throw runtime_error("There are not enough bricks"s);
        }
        resources_.TakeBricks(bricks_count);
        return House(spec.length, spec.width, spec.height);
    }

  private:
    Resources& resources_;
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