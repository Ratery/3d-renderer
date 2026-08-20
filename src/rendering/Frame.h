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

    bool is_depth_visible(Index x, Index y, Index sample_id, float depth) const;

    void set_color(Index x, Index y, Index sample_id, float depth, const Color& color);

    void reset();

    void resolve();

    const std::vector<std::uint8_t>& get_resolved_pixels() const;

    Width width() const;
    Height height() const;

    float aspect_ratio() const;

   private:
    Index width_;
    Index height_;
    std::vector<Color> sample_colors_;
    std::vector<std::uint8_t> resolved_pixels_;
    std::vector<std::atomic<std::uint32_t>> z_buffer_;

    static constexpr float max_depth_ = 1.0f;
    static constexpr Index msaa_samples_ = 4;

    Color& sample_colors(Index x, Index y, Index sample_id);
    std::atomic<std::uint32_t>& z_buffer(Index x, Index y, Index sample_id);
    const std::atomic<std::uint32_t>& z_buffer(Index x, Index y, Index sample_id) const;

    static std::uint32_t depth_to_uint(float depth);
    static float uint_to_depth(std::uint32_t value);

    static sf::Color make_sf_color(const Color& color);
};

}  // namespace renderer
