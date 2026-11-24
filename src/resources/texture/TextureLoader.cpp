#include "resources/texture/TextureLoader.h"

#include <SFML/Graphics/Image.hpp>
#include <cstdint>
#include <stdexcept>
#include <utility>
#include <vector>

#include "core/Color.h"
#include "resources/texture/Texture.h"

namespace renderer {

Texture TextureLoader::load_from_file(const std::string& filename) {
    sf::Image image;
    if (!image.loadFromFile(filename)) {
        throw std::runtime_error("Failed to load texture: " + filename);
    }
    image.flipVertically();

    Index width = image.getSize().x;
    Index height = image.getSize().y;
    const uint8_t* data = image.getPixelsPtr();

    std::vector<Color> pixels(width * height, {0, 0, 0});

    for (int i = 0; i < width * height; i++) {
        uint8_t r = data[i * 4 + 0];
        uint8_t g = data[i * 4 + 1];
        uint8_t b = data[i * 4 + 2];
        uint8_t a = data[i * 4 + 3];
        pixels[i] = Color::from_RGBA8(r, g, b, a);
    }

    return {width, height, std::move(pixels)};
}

}  // namespace renderer
