#pragma once

#include <vector>

#include "core/Color.h"
#include "core/Linalg.h"

namespace renderer {

class Texture {
   public:
    Texture(Index width, Index height, std::vector<Color> pixels);

    const Color& at(Index x, Index y) const;
    const Color& sample(const Vector2& uv) const;

   private:
    Index width_;
    Index height_;
    std::vector<Color> pixels_;
};

}  // namespace renderer
