#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Colors.h"

struct Button {
    sf::RectangleShape shape;
    sf::Text           label;
    sf::Color          normalColor, hoverColor;
    bool               hovered = false;
    bool               visible = true;

    void init(float x, float y, float w, float h,
              const std::string& txt, sf::Font& font,
              sf::Color normal, sf::Color hover, unsigned charSize = 13)
    {
        normalColor = normal; hoverColor = hover;
        shape = makeRect(x, y, w, h, normal);
        label = makeText(txt, font, charSize, Colors::BG, 0, 0);
        sf::FloatRect tb = label.getLocalBounds();
        label.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f);
        label.setPosition(x + w / 2.f, y + h / 2.f);
    }

    bool contains(sf::Vector2i pos) const {
        if (!visible) return false;
        return shape.getGlobalBounds().contains((float)pos.x, (float)pos.y);
    }

    void update(sf::Vector2i mp) {
        if (!visible) return;
        hovered = contains(mp);
        shape.setFillColor(hovered ? hoverColor : normalColor);
    }

    void draw(sf::RenderWindow& w) {
        if (!visible) return;
        w.draw(shape); w.draw(label);
    }

    void draw(sf::RenderTexture& t) {
        if (!visible) return;
        t.draw(shape); t.draw(label);
    }
};

#endif
