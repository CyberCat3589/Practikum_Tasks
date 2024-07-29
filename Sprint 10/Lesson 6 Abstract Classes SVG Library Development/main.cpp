#define _USE_MATH_DEFINES
#include "svg.h"

#include <cassert>
#include <cmath>

namespace shapes
{

class Triangle : public svg::Drawable
{
public:
  Triangle(svg::Point p1, svg::Point p2, svg::Point p3) : p1_(p1), p2_(p2), p3_(p3) {}
  void Draw(svg::ObjectContainer& container) const override
  {
    container.Add(svg::Polyline().AddPoint(p1_).AddPoint(p2_).AddPoint(p3_).AddPoint(p1_));
  }

private:
  svg::Point p1_, p2_, p3_;
};

class Star : public svg::Drawable
{
public:
  Star(svg::Point center, double outer_rad, double inner_rad, int num_rays)
  {
    polyline_ = CreateStar(center, outer_rad, inner_rad, num_rays);
    polyline_.SetFillColor("red").SetStrokeColor("black");
  }

  void Draw(svg::ObjectContainer& container) const override
  {
    container.Add(polyline_);
  }

private:
  svg::Polyline CreateStar(svg::Point center, double outer_rad, double inner_rad, int num_rays)
  {
    using namespace svg;
    Polyline polyline;
    for (int i = 0; i <= num_rays; ++i)
    {
      double angle = 2 * M_PI * (i % num_rays) / num_rays;
      polyline.AddPoint({center.x + outer_rad * sin(angle), center.y - outer_rad * cos(angle)});
      if (i == num_rays)
      {
        break;
      }
      angle += M_PI / num_rays;
      polyline.AddPoint({center.x + inner_rad * sin(angle), center.y - inner_rad * cos(angle)});
    }
    return polyline;
  }
  svg::Polyline polyline_;
};

class Snowman : public svg::Drawable
{
public:
  Snowman(svg::Point center, double radius) : head_center_(center), radius_(radius) {}

  void Draw(svg::ObjectContainer& container) const override
  {
    svg::Circle head, middle, down;

    svg::Point middle_center = {head_center_.x, head_center_.y + (2 * radius_)};
    svg::Point down_center = {head_center_.x, head_center_.y + (5 * radius_)};

    head.SetCenter(head_center_).SetRadius(radius_).SetFillColor("rgb(240,240,240)").SetStrokeColor("black");
    middle.SetCenter(middle_center).SetRadius(radius_ * 1.5).SetFillColor("rgb(240,240,240)").SetStrokeColor("black");
    down.SetCenter(down_center).SetRadius(radius_ * 2).SetFillColor("rgb(240,240,240)").SetStrokeColor("black");

    container.Add(down);
    container.Add(middle);
    container.Add(head);
  }

private:
  svg::Point head_center_;
  double radius_;
};

}  // namespace shapes

template <typename DrawableIterator>
void DrawPicture(DrawableIterator begin, DrawableIterator end, svg::ObjectContainer& target)
{
  for (auto it = begin; it != end; ++it)
  {
    (*it)->Draw(target);
  }
}

template <typename Container>
void DrawPicture(const Container& container, svg::ObjectContainer& target)
{
  DrawPicture(begin(container), end(container), target);
}

// Выполняет линейную интерполяцию значения от from до to в зависимости от параметра t
uint8_t Lerp(uint8_t from, uint8_t to, double t)
{
  return static_cast<uint8_t>(std::round((to - from) * t + from));
}

// Выполняет линейную интерполяцию Rgb цвета от from до to в зависимости от параметра t
svg::Rgb Lerp(svg::Rgb from, svg::Rgb to, double t)
{
  return {Lerp(from.red, to.red, t), Lerp(from.green, to.green, t), Lerp(from.blue, to.blue, t)};
}

int main()
{
  using namespace svg;
  using namespace shapes;
  using namespace std;

  // vector<unique_ptr<svg::Drawable>> picture;
  // picture.emplace_back(make_unique<Triangle>(Point{100, 20}, Point{120, 50}, Point{80, 40}));
  // picture.emplace_back(make_unique<Star>(Point{50.0, 20.0}, 10.0, 4.0, 5));
  // picture.emplace_back(make_unique<Snowman>(Point{30, 20}, 10.0));

  // svg::Document doc;
  // DrawPicture(picture, doc);

  // const Text base_text =  //
  //     Text().SetFontFamily("Verdana"s).SetFontSize(12).SetPosition({10, 100}).SetData("Happy New Year!"s);
  // doc.Add(Text{base_text}
  //             .SetStrokeColor("yellow"s)
  //             .SetFillColor("yellow"s)
  //             .SetStrokeLineJoin(StrokeLineJoin::ROUND)
  //             .SetStrokeLineCap(StrokeLineCap::ROUND)
  //             .SetStrokeWidth(3));
  // doc.Add(Text{base_text}.SetFillColor("red"s));

  // doc.Render(cout);

  // Задаёт цвет по умолчанию: red=0, green=0, blue=0
  // svg::Rgb color;
  // assert(color.red == 0 && color.green == 0 && color.blue == 0);

  // Rgb start_color{0, 255, 30};
  // Rgb end_color{20, 20, 150};

  // const int num_circles = 10;
  // Document doc;
  // for (int i = 0; i < num_circles; ++i)
  // {
  //   const double t = double(i) / (num_circles - 1);

  //   const Rgb fill_color = Lerp(start_color, end_color, t);

  //   doc.Add(Circle().SetFillColor(fill_color).SetStrokeColor("black"s).SetCenter({i * 20.0 + 40, 40.0}).SetRadius(15));
  // }
  // doc.Render(cout);

  Color none_color;
  cout << none_color << endl;  // none

  Color purple{"purple"s};
  cout << purple << endl;  // purple

  Color rgb = Rgb{100, 200, 255};
  cout << rgb << endl;  // rgb(100,200,255)

  Color rgba = Rgba{100, 200, 255, 0.5};
  cout << rgba << endl;  // rgba(100,200,255,0.5)

  Circle c;
  c.SetRadius(3.5).SetCenter({1.0, 2.0});
  c.SetFillColor(rgba);
  c.SetStrokeColor(purple);

  Document doc;
  doc.Add(std::move(c));
  doc.Render(cout);
}