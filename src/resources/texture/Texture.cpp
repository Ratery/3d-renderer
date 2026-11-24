#include "resources/texture/Texture.h"

#include <algorithm>
#include <cassert>
#include <utility>

namespace renderer {

namespace {

Index sample_uv(float uv, Index max_val) {
    assert(0.0f <= uv && uv <= 1.0f);
    float tex_coord = uv * static_cast<float>(max_val);
    Index sample_coord = static_cast<Index>(tex_coord);
    return std::min(sample_coord, max_val - 1);
}

}  // namespace

Texture::Texture(Index width, Index height, std::vector<Color> pixels)
    : width_(width), height_(height), pixels_(std::move(pixels)) {
    assert(static_cast<int>(pixels_.size()) == width_ * height_);
}

const Color& Texture::at(Index x, Index y) const {
    assert(x < width_ && y < height_);
    return pixels_[x + y * width_];
}

const Color& Texture::sample(const Vector2& uv) const {
    return at(sample_uv(uv.x(), width_), sample_uv(uv.y(), height_));
}

}  // namespace renderer
