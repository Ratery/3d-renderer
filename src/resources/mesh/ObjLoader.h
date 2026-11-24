#pragma once

#include <string>

#include "core/Linalg.h"
#include "scene/Object.h"

namespace renderer {

struct FaceVertex {
    int position_idx;
    int normal_idx;
    int uv_idx;
};

class ObjLoader {
   public:
    explicit ObjLoader(const std::string& filename);
    Object release_object();

    static Object load_from_file(const std::string& filename);

   private:
    std::vector<Vector3> positions_;
    std::vector<Vector3> normals_;
    std::vector<Vector2> uvs_;
    Object object_;

    static Vector3 parse_vertex(const std::string& line);
    static Vector3 parse_normal(const std::string& line);
    static Vector2 parse_uv(const std::string& line);
    std::vector<FaceVertex> parse_face(const std::string& line) const;
    void process_face(const std::vector<FaceVertex>& face);
    Triangle make_triangle(const FaceVertex& v0, const FaceVertex& v1, const FaceVertex& v2) const;
};

}  // namespace renderer
