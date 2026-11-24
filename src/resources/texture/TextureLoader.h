#pragma once

#include <string>

#include "resources/texture/Texture.h"

namespace renderer {

class TextureLoader {
   public:
    static Texture load_from_file(const std::string& filename);
};

}  // namespace renderer
