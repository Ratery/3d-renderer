#pragma once

#include "core/Linalg.h"

namespace renderer {

class Color {
   public:
    Color();
    Color(float r, float g, float b, float a = 1.0f);

    static Color from_RGBA8(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    float r() const;
    float g() const;
    float b() const;
    float a() const;

    Color clamped() const;

    Color& operator+=(const Color& other);
    Color operator+(const Color& other) const;

    Color& operator*=(float scalar);
    Color& operator*=(const Color& other);

    Color operator*(float scalar) const;
    Color operator*(const Color& other) const;

    Color& operator/=(float scalar);
    Color operator/(float scalar) const;

    friend Color operator*(float scalar, const Color& color);

   private:
    Vector4 data_;

    Color(Vector4 data);
};

}  // namespace renderer
