#pragma once
#include "texture.h"

#include <memory>

// Поддерживаемые виды фигур: прямоугольник и эллипс
enum class ShapeType
{
    RECTANGLE,
    ELLIPSE
};

class Shape
{
  public:
    // Фигура после создания имеет нулевые координаты и размер,
    // а также не имеет текстуры
    explicit Shape(ShapeType type) : shape_type_(type)
    {
    }

    void SetPosition(Point pos)
    {
        position_ = pos;
    }

    void SetSize(Size size)
    {
        size_ = size;
    }

    void SetTexture(std::shared_ptr<Texture> texture)
    {
        texture_ = texture;
    }

    // Рисует фигуру на указанном изображении
    // В зависимости от типа фигуры должен рисоваться либо эллипс, либо прямоугольник
    // Пиксели фигуры, выходящие за пределы текстуры, а также в случае, когда текстура не задана,
    // должны отображаться с помощью символа точка '.'
    // Части фигуры, выходящие за границы объекта image, должны отбрасываться.
    void Draw(Image& image) const
    {
        const auto image_size = GetImageSize(image);
 
        int y_ = 0;
        int x_ = 0;
        char helper;
 
        for (int y = 0; y < size_.height; ++y) {
            for (int x = 0; x < size_.width; ++x) {
 
                y_ = position_.y + y;
                x_ = position_.x + x;
 
                if (y_ < 0 || 
                    x_ < 0 || 
                    y_ >= image_size.height || 
                    x_ >= image_size.width) {
 
                    continue;
                }
 
                if (!texture_) {
                    helper = '.';
                } else {
                    helper = texture_->GetPixelColor({x, y});
                }
 
                if ((shape_type_ == ShapeType::ELLIPSE 
                              && IsPointInEllipse({x, y}, size_)) 
                     || (shape_type_ == ShapeType::RECTANGLE)) {
 
                    image[y_][x_] = helper;
                }
            }
        }
    }

  private:
    ShapeType shape_type_ = ShapeType::RECTANGLE;
    Point position_ = {0, 0};
    Size size_ = {0, 0};
    std::shared_ptr<Texture> texture_ = nullptr;
};