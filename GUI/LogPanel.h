#ifndef GUI_LOGPANEL_H
#define GUI_LOGPANEL_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Colors.h"

struct LogPanel {
    sf::RectangleShape bg;
    sf::Text           lblTitle;
    std::vector<std::string> logi;
    float px, py;

    void build(float x, float y, float w, float h, sf::Font& font) {
        px = x; py = y;
        bg       = makeRect(x, y, w, h, Colors::Panel);
        lblTitle = makeText("LOGI", font, 13, Colors::Accent, x+10, y+6);
    }

    void add(const std::string& log) {
        logi.push_back(log);
        if (logi.size() > 5) logi.erase(logi.begin());
    }

    void draw(sf::RenderWindow& win, sf::Font& font) {
        win.draw(bg);
        win.draw(lblTitle);
        for (int i = 0; i < (int)logi.size(); i++) {
            auto t = makeText(logi[i], font, 11, Colors::TextDim, px+10, py+24 + i*17);
            win.draw(t);
        }
    }
};

#endif
