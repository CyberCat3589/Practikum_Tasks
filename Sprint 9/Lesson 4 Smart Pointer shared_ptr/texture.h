#pragma once
#include "common.h"
 
class Texture {
public:
    explicit Texture(Image image)
        : image_(std::move(image)) {
    }
 
    Size GetSize() const {
        if (image_.empty()) {
            return {0, 0};
        } 
        return {int(image_[0].size()), int(image_.size())};
    }
 
    char GetPixelColor(Point p) const {
        if (int(image_.size()) <= p.y || int(image_[0].size()) <= p.x || p.x < 0 || p.y < 0) {
            return '.';
        }
        return image_[p.y][p.x];
    }
 
private:
    Image image_;
};