#ifndef GUI_ADDROLETAPANEL_H
#define GUI_ADDROLETAPANEL_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Colors.h"
#include "Button.h"

struct AddRoletaPanel {
    sf::RectangleShape bg, boxNazwa, boxPokoj;
    sf::Text lblTitle, lblNazwa, lblPokoj, lblTyp;
    Button   btnWewnatrz, btnZewnatrz, btnDodaj;

    std::string inputNazwa, inputPokoj;
    bool focusNazwa = true;
    int  typWybor   = 0;   // 0 = wewnętrzna, 1 = zewnętrzna
    bool visible    = false;

    void build(sf::Font& font, float W, float H) {
        float pw = 360, ph = 260;
        float px = W/2 - pw/2, py = H/2 - ph/2;

        bg = makeRect(px, py, pw, ph, {28, 32, 48});
        bg.setOutlineThickness(2);
        bg.setOutlineColor(Colors::Accent);

        lblTitle    = makeText("Dodaj nowa rolete", font, 16, Colors::Accent,  px+12, py+10);
        lblNazwa    = makeText("Nazwa:",            font, 12, Colors::TextDim, px+12, py+44);
        lblPokoj    = makeText("Pokoj:",            font, 12, Colors::TextDim, px+12, py+94);
        lblTyp      = makeText("Typ:",              font, 12, Colors::TextDim, px+12, py+144);

        boxNazwa = makeRect(px+12, py+58,  336, 32, Colors::Panel);
        boxPokoj = makeRect(px+12, py+108, 336, 32, Colors::Panel);

        btnWewnatrz.init(px+12,  py+160, 160, 30, "Wewnetrzna", font, Colors::AccentDim, Colors::Accent);
        btnZewnatrz.init(px+188, py+160, 160, 30, "Zewnetrzna", font, Colors::Panel,     Colors::Card);
        btnDodaj   .init(px+12,  py+210, 336, 36, "DODAJ ROLETE", font, Colors::Green,   {30,140,60}, 14);
    }

    // Zwraca true jeśli kliknięto poza panelem
    bool handleClick(sf::Vector2i mp, float W, float H) {
        float pw = 360, px = W/2 - pw/2, py = H/2 - 130;

        if (sf::FloatRect(px+12, py+58,  336, 32).contains((float)mp.x, (float)mp.y)) focusNazwa = true;
        if (sf::FloatRect(px+12, py+108, 336, 32).contains((float)mp.x, (float)mp.y)) focusNazwa = false;

        if (btnWewnatrz.contains(mp)) {
            typWybor = 0;
            btnWewnatrz.normalColor = Colors::AccentDim;
            btnZewnatrz.normalColor = Colors::Panel;
        }
        if (btnZewnatrz.contains(mp)) {
            typWybor = 1;
            btnZewnatrz.normalColor = Colors::AccentDim;
            btnWewnatrz.normalColor = Colors::Panel;
        }

        // klik poza panelem -> zamknij
        return !sf::FloatRect(px, py, 360, 260).contains((float)mp.x, (float)mp.y);
    }

    void handleText(sf::Uint32 c) {
        std::string& s = focusNazwa ? inputNazwa : inputPokoj;
        if (c == 8 && !s.empty()) s.pop_back();
        else if (c >= 32 && c < 127) s += (char)c;
    }

    bool readyToAdd() const {
        return !inputNazwa.empty() && !inputPokoj.empty();
    }

    void reset() {
        inputNazwa.clear();
        inputPokoj.clear();
        visible = false;
    }

    void update(sf::Vector2i mp) {
        if (!visible) return;
        btnWewnatrz.update(mp);
        btnZewnatrz.update(mp);
        btnDodaj   .update(mp);
    }

    void draw(sf::RenderWindow& win, sf::Font& font, float W, float H) {
        if (!visible) return;
        float pw = 360, px = W/2 - pw/2, py = H/2 - 130;

        win.draw(bg);
        win.draw(lblTitle); win.draw(lblNazwa);
        win.draw(lblPokoj); win.draw(lblTyp);
        win.draw(boxNazwa); win.draw(boxPokoj);

        auto tn = makeText(inputNazwa, font, 14, Colors::Text, px+18, py+64);
        auto tp = makeText(inputPokoj, font, 14, Colors::Text, px+18, py+114);
        win.draw(tn); win.draw(tp);

        btnWewnatrz.draw(win);
        btnZewnatrz.draw(win);
        btnDodaj   .draw(win);
    }
};

#endif
