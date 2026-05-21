#pragma once

#include <atomic>
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

    bool is_depth_visible(Index x, Index y, float depth) const;

    void set_pixel(Index x, Index y, float depth, const Color& color);

    void reset();

    void get_pixel(Index x, Index y) const;
    const std::vector<std::uint8_t>& get_pixels() const;

    Width width() const;
    Height height() const;

    float aspect_ratio() const;

   private:
    Index width_;
    Index height_;
    std::vector<std::uint8_t> pixels_;
    std::vector<std::atomic<std::uint32_t>> z_buffer_;

    static constexpr float max_depth_ = 1.0f;

    std::uint8_t& pixels(Index x, Index y);
    std::atomic<std::uint32_t>& z_buffer(Index x, Index y);
    const std::atomic<std::uint32_t>& z_buffer(Index x, Index y) const;

    static std::uint32_t depth_to_uint(float depth);
    static float uint_to_depth(std::uint32_t value);

    static sf::Color make_sf_color(const Color& color);
};

}  // namespace renderer
