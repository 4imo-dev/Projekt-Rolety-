#ifndef GUI_LOGINSCREEN_H
#define GUI_LOGINSCREEN_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Colors.h"
#include "Button.h"

struct LoginScreen {
    sf::RectangleShape bg, loginBox, passBox, loginBorder, passBorder;
    sf::Text lblTitle, lblLogin, lblPass, lblError;
    Button   btnZaloguj;

    std::string inputLogin, inputPass;
    bool focusLogin = true;
    bool error      = false;

    void build(sf::Font& font, float W, float H) {
        bg = makeRect(0, 0, W, H, Colors::BG);
        float bw = 340, cx = W/2 - bw/2, cy = H/2 - 80;

        loginBorder = makeRect(cx-2, cy-2,    bw+4, 46, Colors::Accent);
        passBorder  = makeRect(cx-2, cy+62,   bw+4, 46, Colors::Accent);
        loginBox    = makeRect(cx,   cy,       bw,   42, Colors::Panel);
        passBox     = makeRect(cx,   cy+64,    bw,   42, Colors::Panel);

        lblTitle = makeText("System Rolet", font, 28, Colors::Accent,  W/2-100, cy-75);
        lblLogin = makeText("Login:",       font, 13, Colors::TextDim, cx,      cy-18);
        lblPass  = makeText("Haslo:",       font, 13, Colors::TextDim, cx,      cy+46);
        lblError = makeText("Nieprawidlowy login lub haslo!", font, 13, Colors::Red, cx, cy+120);

        btnZaloguj.init(cx, cy+145, bw, 40, "ZALOGUJ", font, Colors::Accent, Colors::AccentDim, 15);
    }

    void handleText(sf::Uint32 c) {
        std::string& s = focusLogin ? inputLogin : inputPass;
        if (c == 8 && !s.empty()) s.pop_back();
        else if (c >= 32 && c < 127) s += (char)c;
    }

    void handleClick(sf::Vector2i mp, float W, float H) {
        float bw = 340, cx = W/2 - bw/2, cy = H/2 - 80;
        if (sf::FloatRect(cx, cy,    bw, 42).contains((float)mp.x, (float)mp.y)) focusLogin = true;
        if (sf::FloatRect(cx, cy+64, bw, 42).contains((float)mp.x, (float)mp.y)) focusLogin = false;
    }

    void update(sf::Vector2i mp) {
        btnZaloguj.update(mp);
    }

    void draw(sf::RenderWindow& win, sf::Font& font, float W, float H) {
        float bw = 340, cx = W/2 - bw/2, cy = H/2 - 80;
        win.draw(bg);
        win.draw(lblTitle); win.draw(lblLogin); win.draw(lblPass);
        if (focusLogin) win.draw(loginBorder); else win.draw(passBorder);
        win.draw(loginBox); win.draw(passBox);

        auto lt = makeText(inputLogin, font, 16, Colors::Text, cx+8, cy+10);
        auto pt = makeText(std::string(inputPass.size(), '*'), font, 16, Colors::Text, cx+8, cy+74);
        win.draw(lt); win.draw(pt);

        if (error) win.draw(lblError);
        btnZaloguj.draw(win);
    }
};

#endif
