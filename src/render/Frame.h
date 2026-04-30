#pragma once

#include <vector>

#include "SFML/Graphics/Color.hpp"

namespace renderer {

class Frame {
   public:
    Frame(int width, int height);
    void set_pixel(int x, int y, float depth, sf::Color color);

    void reset_z_buffer();

    void get_pixel(int x, int y) const;

    int get_width() const;
    int get_height() const;

    const std::vector<std::uint8_t>& get_pixels() const;

   private:
    int width_;
    int height_;
    std::vector<std::uint8_t> pixels_;
    std::vector<float> z_buffer_;  // logically this should probably be in Renderer
    // added here because indexing of plain vector is already implemented in Frame
};

}  // namespace renderer
