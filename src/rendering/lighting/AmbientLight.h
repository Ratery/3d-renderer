#pragma once

#include "core/Color.h"

namespace renderer {

class AmbientLight {
public:
    static inline const Color default_intensity{0.2f, 0.2f, 0.2f};
    explicit AmbientLight(const Color& intensity = default_intensity);

    const Color& get_intensity() const;
    void set_intensity(const Color& intensity);

private:
    Color intensity_;
};

}  // namespace renderer
