#pragma once
#include "common.h"

class Texture {
public:
    explicit Texture(Image image)
        : image_(std::move(image)) {
    }

    Size GetSize() const {
        // Заглушка. Реализуйте метод самостоятельно
        return {0, 0};
    }

    char GetPixelColor(Point p) const {
        (void) p;
        // Заглушка. Реализуйте метод самостоятельно
        return ' ';
    }

private:
    Image image_;
};