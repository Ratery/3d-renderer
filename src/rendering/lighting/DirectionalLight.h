#pragma once

#include "core/Color.h"
#include "core/Linalg.h"

namespace renderer {

class DirectionalLight {
   public:
    DirectionalLight(const Color& intensity, const Vector3& direction);

    const Color& get_intensity() const;
    void set_intensity(const Color& intensity);

    const Vector3& get_direction() const;
    void set_direction(const Vector3& direction);

    DirectionalLight make_transformed(const Matrix4& matrix) const;

   private:
    Color intensity_;
    Vector3 direction_;
};

}  // namespace renderer
