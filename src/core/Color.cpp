#include "Color.h"

namespace renderer {

Color::Color(float r, float g, float b, float a) : data_(r, g, b, a) {}

Color Color::from_SFML(const sf::Color& sfColor) {
    return {static_cast<float>(sfColor.r) / 255.0f, static_cast<float>(sfColor.g) / 255.0f,
            static_cast<float>(sfColor.b) / 255.0f, static_cast<float>(sfColor.a) / 255.0f};
}

sf::Color Color::to_SFML() const {
    return {
        static_cast<std::uint8_t>(data_(0) * 255.0f), static_cast<std::uint8_t>(data_(1) * 255.0f),
        static_cast<std::uint8_t>(data_(2) * 255.0f), static_cast<std::uint8_t>(data_(3) * 255.0f)};
}

Color& Color::operator+=(const Color& other) {
    data_ = (data_ + other.data_).cwiseMin(1.0f);
    return *this;
}

Color& Color::operator*=(float scalar) {
    data_ = (data_ * scalar).cwiseMax(0.0f).cwiseMin(1.0f);
    return *this;
}

Color& Color::operator*=(const Color& other) {
    data_ = data_.cwiseProduct(other.data_).cwiseMin(1.0f);
    return *this;
}

Color Color::operator+(const Color& other) const {
    Color new_color = *this;
    return new_color += other;
}

Color Color::operator*(float scalar) const {
    Color new_color = *this;
    return new_color *= scalar;
}

Color Color::operator*(const Color& other) const {
    Color new_color = *this;
    return new_color *= other;
}

Color operator*(float scalar, const Color& color) {
    return color * scalar;
}

}  // namespace renderer
