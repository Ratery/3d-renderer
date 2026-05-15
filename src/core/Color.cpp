#include "core/Color.h"

namespace renderer {

Color::Color(float r, float g, float b, float a) : data_(r, g, b, a) {
    data_ = data_.cwiseMax(0.0f).cwiseMin(1.0f);
}

Color Color::from_RGBA8(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return {static_cast<float>(r) / 255.0f, static_cast<float>(g) / 255.0f,
            static_cast<float>(b) / 255.0f, static_cast<float>(a) / 255.0f};
}

float Color::r() const {
    return data_(0);
}

float Color::g() const {
    return data_(1);
}

float Color::b() const {
    return data_(2);
}

float Color::a() const {
    return data_(3);
}

Color& Color::operator+=(const Color& other) {
    data_ = (data_ + other.data_).cwiseMin(1.0f);
    return *this;
}

Color Color::operator+(const Color& other) const {
    Color result = *this;
    result += other;
    return result;
}

Color& Color::operator*=(float scalar) {
    data_ = (data_ * scalar).cwiseMax(0.0f).cwiseMin(1.0f);
    return *this;
}

Color& Color::operator*=(const Color& other) {
    data_ = data_.cwiseProduct(other.data_).cwiseMin(1.0f);
    return *this;
}

Color Color::operator*(float scalar) const {
    Color result = *this;
    result *= scalar;
    return result;
}

Color Color::operator*(const Color& other) const {
    Color result = *this;
    result *= other;
    return result;
}

Color operator*(float scalar, const Color& color) {
    return color * scalar;
}

}  // namespace renderer
