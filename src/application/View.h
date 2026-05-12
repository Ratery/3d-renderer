#pragma once

#include <SFML/Graphics.hpp>
#include "render/Frame.h"

namespace renderer {

class View {
   public:
    View(Width width, Height height, const std::string& title);

    void show(const Frame& frame);
    sf::RenderWindow& window();
    void set_fps(float fps);

   private:
    sf::RenderWindow window_;
    sf::Texture texture_;
    sf::Sprite sprite_;
    sf::Font font_;
    sf::Text fps_text_;
};

}  // namespace renderer
