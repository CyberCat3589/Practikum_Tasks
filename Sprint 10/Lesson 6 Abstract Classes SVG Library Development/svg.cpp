#include "svg.h"

namespace svg
{
using namespace std::literals;

void Object::Render(const RenderContext& context) const
{
    context.RenderIndent();

    //Делегируем вывод тега классам-потомкам
    RenderObject(context);

    context.out << std::endl;
}

//--------------------Circle------------------
Circle& Circle::SetCenter(Point center)
{
    center_ = center;
    return *this;
}

Circle& Circle::SetRadius(double rad)
{
    radius_ = rad;
    return *this;
}

void Circle::RenderObject(const RenderContext& context) const
{
    context.out << R"(<circle cx=")" << center_.x << R"(" )"
    << R"(cy=")" << center_.y << R"(" )"
    << R"(r=")" << radius_ << R"("/>)";
}

//--------------------Polyline------------------
Polyline& Polyline::AddPoint(Point point)
{
    points_.emplace_back(point);
    return *this;
}

void Polyline::RenderObject(const RenderContext& context) const
{
    std::ostream& out = context.out;
    out << R"(<polyline points=")";
    for(size_t i = 0; i < points_.size(); ++i)
    {
        out << points_[i].x << ","sv << points_[i].y;
        if(i + 1 != points_.size())
        {
            out << " "sv;
        }
    }
    out << R"("/>)";
}

//--------------------Text------------------
Text& Text::SetPosition(Point pos)
{
    position_ = pos;
    return *this;
}

Text& Text::SetOffset(Point offset)
{
    offset_ = offset;
    return *this;
}

Text& Text::SetFontFamily(std::string fnt_family)
{
    font_family_ = fnt_family;
    return *this;
}

Text& Text::SetData(std::string str)
{
    data_ = str;
    return *this;
}

Text& Text::SetFontSize(uint32_t fnt_size)
{
    font_size_ = fnt_size;
    return *this;
}

Text& Text::SetFontWeight(std::string fnt_weight)
{
    font_weight_ = fnt_weight;
    return *this;
}

std::string Text::DeleteSpaces(const std::string& str)
{
    if(str.empty()) return {};
    size_t left = str.find_first_not_of(' ');
    size_t right = str.find_last_not_of(' ');
    return str.substr(left, right - left + 1);
}

std::string Text::ScreenSymbols(const std::string& str)
{
    std::string out_str;
    for(char ch : str)
    {
        if(ch == '"')
        {
            out_str += "&quot;"sv;
            continue;
        }
        if(ch == '\'')
        {
            out_str += "&apos;"sv;
            continue;
        }
        if(ch == '<')
        {
            out_str += "&lt;"sv;
            continue;
        }
        if(ch == '>')
        {
            out_str += "&gt;"sv;
            continue;
        }
        if(ch == '&')
        {
            out_str += "&amp;"sv;
            continue;
        }
        out_str += ch;
    }
    return out_str;
}

void Text::RenderObject(const RenderContext& context) const
{
    std::ostream& out = context.out;
    out << R"(<text x=")" << position_.x << R"(" y=")" << position_.y << R"(" )"
    << R"(dx=")" << offset_.x << R"(" dy=")" << offset_.y << R"(" )"
    << R"(font-size=")" << font_size_ << R"(" )";

    if(!font_family_.empty())
    {
        out << R"(font-family=")" << font_family_ << R"(" )";
    }

    if(!font_weight_.empty())
    {
        out << R"(font-weight=")" << font_weight_ << R"(")";
    }
    
    out << ">"sv << DeleteSpaces(ScreenSymbols(data_)) << "</text>"sv;
}

//--------------------Document------------------
void Document::AddPtr(std::unique_ptr<Object>&& obj)
{
    objects_.emplace_back(std::move(obj));
}

void Document::Render(std::ostream& out) const
{
    std::string_view xml = R"(<?xml version="1.0" encoding="UTF-8" ?>)";
    std::string_view svg = R"(<svg xmlns="http://www.w3.org/2000/svg" version="1.1">)";

    int indent = 2;
    int indent_step = 2;

    RenderContext context(out, indent_step, indent);

    out << xml << '\n' << svg << '\n';

    for(const auto& obj : objects_)
    {
        obj->Render(context);
    }

    out << "</svg>";
}

}