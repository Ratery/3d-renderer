#pragma once

#include "core/Linalg.h"

namespace renderer {

class Color {
   public:
    Color(float r, float g, float b, float a = 1.0f);

    float r() const;
    float g() const;
    float b() const;
    float a() const;

    Color& operator+=(const Color& other);
    Color operator+(const Color& other) const;

    Color& operator*=(float scalar);
    Color& operator*=(const Color& other);

    Color operator*(float scalar) const;
    Color operator*(const Color& other) const;

    friend Color operator*(float scalar, const Color& color);

   private:
    Vector4 data_;
};

}  // namespace renderer
