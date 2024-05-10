#pragma once
#include <array>
#include <cassert>
#include <vector>

#include "geom.h"

class Tile {
public:
    // Размер тайла 8*8 пикселей.
    constexpr static int SIZE = 8;

    // Конструктор по умолчанию. Заполняет тайл указанным цветом.
    Tile(char color = ' ') noexcept {
        /* Реализуйте недостающий код самостоятельно. */
        pixels_ = std::vector<std::vector<char>>(SIZE, std::vector<char>(SIZE, color)); 

        // -------------- не удалять ------------
        assert(instance_count_ >= 0);
        ++instance_count_;  // Увеличиваем счётчик тайлов (для целей тестирования).
        // -------------- не удалять ------------
    }

    Tile(const Tile& other) {
        /* Реализуйте недостающий код самостоятельно. */
        pixels_ = other.pixels_;

        // -------------- не удалять ------------
        assert(instance_count_ >= 0);
        ++instance_count_;  // Увеличиваем счётчик тайлов (для целей тестирования).
        // -------------- не удалять ------------
    }

    ~Tile() {
        // -------------- Не удалять ------------
        --instance_count_;  // Уменьшаем счётчик тайлов.
        assert(instance_count_ >= 0);
        // -------------- не удалять ------------
    }

    /**
     * Изменяет цвет пикселя тайла.
     * Если координаты выходят за пределы тайла, метод ничего не делает.
     */
    void SetPixel(Point p, char color) noexcept {
        /* Реализуйте недостающий код самостоятельно. */
        if(p.y >= 0 && p.y <= SIZE && p.x >= 0 && p.x <= SIZE)
        {
            pixels_[p.y][p.x] = color;
        } 
    }

    /**
     * Возвращает цвет пикселя. Если координаты выходят за пределы тайла, возвращается пробел.
     */
    char GetPixel(Point p) const noexcept {
        /* Реализуйте недостающий функционал самостоятельно. */
        if (IsPointInSize(p, {SIZE, SIZE}))
        {
            return pixels_[p.y][p.x];
        }
        return ' ';
    }

    // Возвращает количество экземпляра класса Tile в программе.
    static int GetInstanceCount() noexcept {
        // -------------- не удалять ------------
        return instance_count_;
        // -------------- не удалять ------------
    }

private:
    // -------------- не удалять ------------
    inline static int instance_count_ = 0;
    // -------------- не удалять ------------

    /* Разместите здесь поля для хранения пикселей тайла. */
    std::vector<std::vector<char>> pixels_;
};