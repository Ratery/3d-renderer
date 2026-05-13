#pragma once

#include "core/Color.h"

namespace renderer {

class Material {
   public:
    static inline const Color default_albedo{0.8f, 0.8f, 0.8f};
    static inline const Color default_specular{0.5f, 0.5f, 0.5f};
    static constexpr float default_shininess = 20.0f;
    Material(const Color& albedo = default_albedo, const Color& specular = default_specular,
             float shininess = default_shininess);

    const Color& get_albedo() const;
    const Color& get_specular() const;
    float get_shininess() const;

    void set_albedo(const Color& albedo);
    void set_specular(const Color& specular);
    void set_shininess(float shininess);

   private:
    Color albedo_;
    Color specular_;
    float shininess_;
};

}  // namespace renderer
