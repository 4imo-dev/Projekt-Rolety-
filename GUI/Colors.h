#ifndef GUI_COLORS_H
#define GUI_COLORS_H

#include <SFML/Graphics.hpp>
#include <string>

namespace Colors {
    const sf::Color BG        {15,  17,  23};
    const sf::Color Panel     {24,  27,  38};
    const sf::Color Card      {32,  36,  52};
    const sf::Color Accent    {255, 180,  40};
    const sf::Color AccentDim {180, 120,  20};
    const sf::Color Text      {220, 225, 240};
    const sf::Color TextDim   {120, 128, 150};
    const sf::Color Green     { 60, 200, 100};
    const sf::Color Red       {220,  70,  70};
    const sf::Color BarBG     { 45,  50,  68};
    const sf::Color BarFill   { 80, 140, 255};
    const sf::Color White     {255, 255, 255};
}

// --- Pomocnicze funkcje ---

inline sf::RectangleShape makeRect(float x, float y, float w, float h, sf::Color color) {
    sf::RectangleShape r({w, h});
    r.setPosition(x, y);
    r.setFillColor(color);
    return r;
}

inline sf::Text makeText(const std::string& s, sf::Font& font,
                         unsigned sz, sf::Color col, float x, float y) {
    sf::Text t;
    t.setFont(font);
    t.setString(s);
    t.setCharacterSize(sz);
    t.setFillColor(col);
    t.setPosition(x, y);
    return t;
}

#endif
