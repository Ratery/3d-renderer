#pragma once

#include <vector>

#include "SFML/Graphics/Color.hpp"
#include "core/Color.h"
#include "core/Linalg.h"

namespace renderer {

enum Width : Index;
enum Height : Index;

class Frame {
   public:
    Frame(Width width, Height height);

    void set_pixel(Index x, Index y, float depth, const Color& color);

    void reset_z_buffer();

    void get_pixel(Index x, Index y) const;
    const std::vector<std::uint8_t>& get_pixels() const;

    Width width() const;
    Height height() const;

   private:
    Index width_;
    Index height_;
    std::vector<std::uint8_t> pixels_;
    std::vector<float> z_buffer_;

    static constexpr float max_depth_ = 1.0f;

    std::uint8_t& pixels(Index x, Index y);
    float& z_buffer(Index x, Index y);

    static sf::Color make_sf_color(const Color& color);
};

}  // namespace renderer
