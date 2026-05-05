#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "render/Frame.h"

namespace renderer {

class View {
   public:
    View(Width width, Height height, const std::string& title);

    void show(const Frame& frame);
    sf::RenderWindow& window();

   private:
    sf::RenderWindow window_;
    sf::Texture texture_;
    sf::Sprite sprite_;
};

}  // namespace renderer
