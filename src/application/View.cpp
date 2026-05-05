#include "View.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace renderer {

View::View(Width width, Height height, const std::string& title)
    : window_(sf::VideoMode(sf::Vector2u(width, height)), title),
      texture_(window_.getSize()),
      sprite_(texture_) {}

void View::show(const Frame& frame) {
    assert(texture_.getSize().x == frame.width() && texture_.getSize().y == frame.height());

    texture_.update(frame.get_pixels().data());
    window_.clear();
    sprite_.setTexture(texture_);
    window_.draw(sprite_);
    window_.display();
}

sf::RenderWindow& View::window() {
    return window_;
}

}  // namespace renderer
