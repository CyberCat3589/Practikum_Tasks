#pragma once
#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <optional>

namespace svg
{

using namespace std::literals;

using Color = std::string;

inline const Color NoneColor{"none"};

enum class StrokeLineCap
{
  BUTT,
  ROUND,
  SQUARE
};

inline std::ostream& operator<<(std::ostream& out, const StrokeLineCap& line_cap)
{
  switch (line_cap)
  {
    case StrokeLineCap::BUTT:
    {
      out << "butt"sv;
      break;
    }
    case StrokeLineCap::ROUND:
    {
      out << "round"sv;
      break;
    }
    case StrokeLineCap::SQUARE:
    {
      out << "square"sv;
      break;
    }
  }
  return out;
}

enum class StrokeLineJoin
{
  MITER,
  MITER_CLIP,
  ROUND,
  BEVEL,
  ARCS
};

inline std::ostream& operator<<(std::ostream& out, const StrokeLineJoin& line_join)
{
  switch (line_join)
  {
    case StrokeLineJoin::ARCS:
    {
      out << "arcs"sv;
      break;
    }
    case StrokeLineJoin::BEVEL:
    {
      out << "bevel"sv;
      break;
    }
    case StrokeLineJoin::MITER:
    {
      out << "miter"sv;
      break;
    }
    case StrokeLineJoin::MITER_CLIP:
    {
      out << "miter-clip"sv;
      break;
    }
    case StrokeLineJoin::ROUND:
    {
      out << "round"sv;
      break;
    }
  }
  return out;
}

struct Point
{
  Point() = default;
  Point(double x, double y) : x(x), y(y) {}

  double x = 0;
  double y = 0;
};

struct RenderContext
{
  RenderContext(std::ostream& out) : out(out) {}
  RenderContext(std::ostream& out, int indent_step, int indent) : out(out), indent_step(indent_step), indent(indent) {}

  RenderContext Indented() const
  {
    return {out, indent_step, indent + indent_step};
  }

  void RenderIndent() const
  {
    for (int i = 0; i < indent; ++i)
    {
      out.put(' ');
    }
  }

  std::ostream& out;
  int indent_step = 0;
  int indent = 0;
};

class Object
{
public:
  void Render(const RenderContext& context) const;
  virtual ~Object() = default;

private:
  virtual void RenderObject(const RenderContext& context) const = 0;
};

template <typename Owner>
class PathProps
{
public:
  Owner& SetFillColor(Color color)
  {
    fill_color_ = color;
    return AsOwner();
  }

  Owner& SetStrokeColor(Color color)
  {
    stroke_color_ = color;
    return AsOwner();
  }

  Owner& SetStrokeWidth(double width)
  {
    width_ = width;
    return AsOwner();
  }

  Owner& SetStrokeLineCap(StrokeLineCap line_cap)
  {
    line_cap_ = line_cap;
    return AsOwner();
  }

  Owner& SetStrokeLineJoin(StrokeLineJoin line_join)
  {
    line_join_ = line_join;
    return AsOwner();
  }

protected:
  ~PathProps() = default;

  void RenderAttrs(std::ostream& out) const
  {
    if(fill_color_ != std::nullopt)
    {
      out << " fill=\""sv << *fill_color_ << "\""sv;
    }

    if(stroke_color_ != std::nullopt)
    {
      out << " stroke=\""sv << *stroke_color_ << "\""sv;
    }
    
    if(width_ != std::nullopt)
    {
      out << " stroke-width=\""sv << *width_ << "\""sv;
    }
    
    if(line_cap_ != std::nullopt)
    {
      out << " stroke-linecap=\""sv << *line_cap_ << "\""sv;
    }
    
    if(line_join_ != std::nullopt)
    {
      out << " stroke-linejoin=\""sv << *line_join_ << "\""sv;
    }
  }

private:
  Owner& AsOwner()
  {
    return static_cast<Owner&>(*this);
  }

  std::optional<Color> fill_color_;//цвет заливки
  std::optional<Color> stroke_color_;//цвет обводки
  std::optional<double> width_;//толщина обводки
  std::optional<StrokeLineCap> line_cap_;//тип формы конца линии
  std::optional<StrokeLineJoin> line_join_;//тип формы соединения линий
};

class Circle final : public Object, public PathProps<Circle>
{
public:
  Circle() = default;
  Circle& SetCenter(Point center);
  Circle& SetRadius(double radius);

private:
  void RenderObject(const RenderContext& context) const override;

  Point center_ = {0.0, 0.0};
  double radius_ = 1.0;
};

class Polyline final : public Object, public PathProps<Polyline>
{
public:
  Polyline() = default;
  Polyline& AddPoint(Point point);

private:
  void RenderObject(const RenderContext& context) const override;

  std::vector<Point> points_;
};

class Text final : public Object, public PathProps<Text>
{
public:
  Text() = default;

  Text& SetPosition(Point pos);
  Text& SetOffset(Point offset);
  Text& SetFontFamily(std::string fnt_family);
  Text& SetData(std::string data);
  Text& SetFontSize(uint32_t size);
  Text& SetFontWeight(std::string fnt_weight);

private:
  void RenderObject(const RenderContext& context) const override;

  static std::string DeleteSpaces(const std::string& str);
  static std::string ScreenSymbols(const std::string& str);

  Point position_ = {0.0, 0.0};
  Point offset_ = {0.0, 0.0};
  uint32_t font_size_ = 1;
  std::string font_family_;
  std::string data_;
  std::string font_weight_;
};

class ObjectContainer
{
public:
  virtual ~ObjectContainer() = default;
  template <typename Obj>
  void Add(Obj obj)
  {
    AddPtr(std::make_unique<Obj>(std::move(obj)));
  }

  virtual void AddPtr(std::unique_ptr<Object>&& ptr) = 0;
};

class Document : public ObjectContainer
{
public:
  Document() = default;

  void AddPtr(std::unique_ptr<Object>&& ptr) override;
  void Render(std::ostream& out) const;

private:
  std::vector<std::unique_ptr<Object>> objects_;
};

class Drawable
{
public:
  virtual ~Drawable() = default;
  virtual void Draw(ObjectContainer& container) const = 0;
};

}  // namespace svg