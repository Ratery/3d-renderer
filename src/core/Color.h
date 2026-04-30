#pragma once

#include <Eigen/Core>
#include <SFML/Graphics/Color.hpp>

namespace renderer {
class Color {
   public:
    Color(float r, float g, float b, float a = 1.0f);

    float r() const { return data_(0); }
    float g() const { return data_(1); }
    float b() const { return data_(2); }
    float a() const { return data_(3); }

    static Color from_SFML(const sf::Color& sfColor);

    sf::Color to_SFML() const;

    Color operator+(const Color& other) const;
    Color operator*(float scalar) const;
    Color operator*(const Color& other) const;

    Color& operator+=(const Color& other);
    Color& operator*=(float scalar);
    Color& operator*=(const Color& other);

    friend Color operator*(float scalar, const Color& color);

   private:
    Eigen::Vector4f data_;
};

}  // namespace renderer
