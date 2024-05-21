#pragma once

#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace svg
{
struct Point
{
    Point() = default;
    Point(double x, double y) : x(x), y(y)
    {
    }
    double x = 0;
    double y = 0;
};

struct RenderContext
{
    RenderContext(std::ostream& out) : out(out){}

    RenderContext(std::ostream& out, int indent_step, int indent = 0) : out(out), indent_step(indent_step), indent(indent){}

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

class Circle final : public Object
{
  public:
    Circle& SetCenter(Point center);
    Circle& SetRadius(double radius);

  private:
    Point center_;
    double radius_ = 1.0;

    void RenderObject(const RenderContext& context) const override;
};

class Polyline final : public Object
{
  public:
    Polyline& AddPoint(Point point);

  private:
    std::vector<Point> points_;
    void RenderObject(const RenderContext& context) const override;
};

class Text final : public Object
{
  public:
    Text& SetPosition(Point pos);
    Text& SetOffset(Point offset);
    Text& SetFontSize(uint32_t size);
    Text& SetFontFamily(std::string font_family);
    Text& SetFontWeight(std::string font_weight);
    Text& SetData(std::string data);

  private:
    Point anchor_;
    Point offset_;
    std::string font_family_;
    std::string font_weight_;
    uint32_t font_size_ = 1;
    std::string data_;

    static std::string DeleteSpaces(const std::string& str);
    static std::string EscapeCharacters(const std::string& str);

    void RenderObject(const RenderContext& context) const override;
};

class Document
{
  public:
    template <typename Obj> void Add(Obj obj)
    {
        objects_.emplace_back(std::make_unique<Obj>(std::move(obj)));
    }

    void AddPtr(std::unique_ptr<Object>&& obj);
    void Render(std::ostream& out) const;

  private:
    std::vector<std::unique_ptr<Object>> objects_;
};
}  // end namespace svg