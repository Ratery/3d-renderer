#include "View.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdexcept>

namespace renderer {

View::View(Width width, Height height, const std::string& title)
    : window_(sf::VideoMode(sf::Vector2u(width, height)), title),
      texture_(window_.getSize()),
      sprite_(texture_),
      fps_text_(font_) {
    if (!font_.openFromFile("assets/fonts/Roboto-Regular.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
    fps_text_.setCharacterSize(20);
    fps_text_.setFillColor(sf::Color::Green);
    fps_text_.setPosition({10, 10});
}

void View::show(const Frame& frame) {
    assert(texture_.getSize().x == frame.width() && texture_.getSize().y == frame.height());

    texture_.update(frame.get_pixels().data());
    window_.clear();
    sprite_.setTexture(texture_);
    window_.draw(sprite_);
    window_.draw(fps_text_);
    window_.display();
}

sf::RenderWindow& View::window() {
    return window_;
}

void View::set_fps(float fps) {
    fps_text_.setString("FPS: " + std::to_string(static_cast<int>(fps)));
}

}  // namespace renderer
