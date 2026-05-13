#include "resources/mesh/ObjLoader.h"

#include <fstream>
#include <iostream>
#include <utility>

#include "core/Linalg.h"
#include "core/Triangle.h"

namespace renderer {

namespace {

int parse_index(const std::string& s, size_t size) {
    int idx = std::stoi(s);
    if (idx < 0) {
        idx = static_cast<int>(size) + idx;
    } else {
        idx = idx - 1;
    }
    return idx;
}

template <typename T>
bool is_in_bounds(int index, const std::vector<T>& vec) {
    return index >= 0 && static_cast<size_t>(index) < vec.size();
}

}  // namespace

ObjLoader::ObjLoader(const std::string& filename) {
    std::ifstream ifs(filename);
    std::string line;
    while (std::getline(ifs, line)) {
        std::istringstream stream(line);
        std::string type;
        stream >> type;
        if (type == "v") {
            positions_.emplace_back(parse_vertex(line));
        } else if (type == "vn") {
            normals_.emplace_back(parse_normal(line));
        } else if (type == "f") {
            auto face = parse_face(line);
            process_face(face);
        }
    }
}
Object ObjLoader::release_object() {
    return std::move(object_);
}

Object ObjLoader::load_from_file(const std::string& filename) {
    ObjLoader loader(filename);
    return loader.release_object();
}

Vector3 ObjLoader::parse_vertex(const std::string& line) {
    std::istringstream stream(line);
    std::string type;
    stream >> type;
    float x, y, z;
    if (!(stream >> x >> y >> z)) {
        std::cerr << "[ERROR]: Could not parse vertex coordinates from \"" << line << "\""
                  << std::endl;
        return Vector3::Zero();
    }
    return {x, y, z};
}

Vector3 ObjLoader::parse_normal(const std::string& line) {
    std::istringstream stream(line);
    std::string type;
    stream >> type;
    float x, y, z;
    if (!(stream >> x >> y >> z)) {
        std::cerr << "[ERROR]: Could not parse normal vector from \"" << line << "\"" << std::endl;
        return Vector3::Zero();
    }
    return {x, y, z};
}

std::vector<FaceVertex> ObjLoader::parse_face(const std::string& line) const {
    std::vector<FaceVertex> face;
    std::string tuple;
    std::istringstream stream(line);
    std::string type;
    stream >> type;
    while (stream >> tuple) {
        std::istringstream ss(tuple);
        std::string v_str, vt_str, vn_str;
        std::getline(ss, v_str, '/');
        std::getline(ss, vt_str, '/');
        std::getline(ss, vn_str, '/');

        if (v_str.empty()) {
            std::cerr << "[ERROR]: Missing vertex index in face token: \"" << tuple << "\""
                      << std::endl;
            return face;
        }
        int v = parse_index(v_str, positions_.size());
        if (!is_in_bounds(v, positions_)) {
            std::cerr << "[ERROR]: Vertex index " << v_str << " out of range" << std::endl;
            return face;
        }

        int vn = -1;
        if (!vn_str.empty()) {
            vn = parse_index(vn_str, normals_.size());
            if (!is_in_bounds(vn, normals_)) {
                std::cerr << "[ERROR]: Normal index " << vn_str << " out of range" << std::endl;
                return face;
            }
        }
        face.emplace_back(v, vn);
    }
    return face;
}

void ObjLoader::process_face(const std::vector<FaceVertex>& face) {
    std::vector<Triangle> triangles;
    if (face.size() < 3) {
        std::cerr << "[ERROR]: Face has less than 3 vertices" << std::endl;
    }

    for (size_t i = 1; i + 1 < face.size(); i++) {
        object_.add_triangle(make_triangle(face[0], face[i], face[i + 1]));
    }
}

Triangle ObjLoader::make_triangle(const FaceVertex& v0, const FaceVertex& v1,
                                  const FaceVertex& v2) const {
    auto& p0 = positions_[v0.position_idx];
    auto& p1 = positions_[v1.position_idx];
    auto& p2 = positions_[v2.position_idx];
    if (v0.normal_idx != -1 && v1.normal_idx != -1 && v2.normal_idx != -1) {
        return {
            p0, p1, p2, normals_[v0.normal_idx], normals_[v1.normal_idx], normals_[v2.normal_idx]};
    }

    Vector3 face_normal = (p1 - p0).cross(p2 - p0).normalized();
    return {p0, p1, p2, face_normal};
}

}  // namespace renderer
