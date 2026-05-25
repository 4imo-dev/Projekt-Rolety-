#ifndef GUI_ROLETACARD_H
#define GUI_ROLETACARD_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Colors.h"
#include "Button.h"
#include "../Rolety/Roleta.h"

enum class RoletaAnim { Idle, Opening, Closing };

struct RoletaState {
    float currentPos = 0.f;
    float targetPos  = 0.f;
    RoletaAnim anim  = RoletaAnim::Idle;
    float speed      = 25.f;
};

struct RoletaCard {
    float cx, cy, cw, ch;

    sf::RectangleShape bg, bgAwaria, barBG, barFill, awariaBar;
    sf::Text txtNazwa, txtPokoj, txtTyp, txtStan, txtProc, txtAwaria;
    Button btnPodnies, btnOpusc, btnStop, btnAwariaBtn, btnNapraw;

    void build(float x, float y, float w, Roleta* r,
               sf::Font& font, bool canRepair)
    {
        cx = x; cy = y; cw = w; ch = 152.f;

        bg       = makeRect(x, y, w, ch, Colors::Card);
        bgAwaria = makeRect(x, y, w, ch, {60, 10, 10});
        awariaBar= makeRect(x, y, 5,  ch, Colors::Red);

        float barX = x + w - 90;
        barBG   = makeRect(barX, y + 14, 40, 118, Colors::BarBG);
        barFill = makeRect(barX, y + 14, 40, 0,   Colors::BarFill);

        txtNazwa  = makeText(r->PobierzNazwe(), font, 16, Colors::Accent,  x+18, y+10);
        txtPokoj  = makeText(r->PobierzPokoj(), font, 12, Colors::TextDim, x+18, y+32);
        txtTyp    = makeText(r->TypRolet(),     font, 11, Colors::TextDim, x+18, y+50);
        txtStan   = makeText(r->Stan(),         font, 13, Colors::Text,    x+18, y+70);
        txtProc   = makeText("0%",              font, 18, Colors::White,   barX, y+136);
        txtAwaria = makeText("!! AWARIA - ROLETA NIE DZIALA !!", font, 15, Colors::Red, x+18, y+88);

        float bw = 86.f, bh = 28.f;
        float row1y = y + 94, row2y = y + 122;

        btnPodnies .init(x+18,          row1y, bw, bh, "Podnies", font, Colors::Accent,    Colors::AccentDim);
        btnOpusc   .init(x+18+bw+8,     row1y, bw, bh, "Opusc",   font, Colors::AccentDim, Colors::Accent);
        btnStop    .init(x+18+2*(bw+8), row1y, bw, bh, "Stop",    font, {100,100,140},      {130,130,180});
        btnAwariaBtn.init(x+18,         row2y, bw, bh, "Awaria",  font, Colors::Red,        {160,40,40});
        btnNapraw  .init(x+18+bw+8,     row2y, bw, bh, "Napraw",  font, Colors::Green,      {30,140,60});
        btnNapraw.visible = canRepair;
    }

    void refresh(Roleta* r, float animPos) {
        bool awaria = r->CzyAwaria();
        txtStan.setString(r->Stan());
        txtNazwa.setFillColor(awaria ? Colors::Red : Colors::Accent);

        float fillH = 118.f * animPos / 100.f;
        barFill.setSize({40.f, fillH});
        barFill.setPosition(cx + cw - 90, cy + 14);
        barFill.setFillColor(awaria ? Colors::Red : Colors::BarFill);

        txtProc.setString(std::to_string((int)animPos) + "%");
        sf::FloatRect tb = txtProc.getLocalBounds();
        txtProc.setOrigin(tb.left + tb.width / 2.f, 0);
        txtProc.setPosition(cx + cw - 70, cy + 136);
    }

    // Przyciski dla detekcji klikniêæ
    Button& getPodnies()  { return btnPodnies; }
    Button& getOpusc()    { return btnOpusc; }
    Button& getStop()     { return btnStop; }
    Button& getAwaria()   { return btnAwariaBtn; }
    Button& getNapraw()   { return btnNapraw; }

    void updateHover(sf::Vector2i mp) {
        btnPodnies  .update(mp);
        btnOpusc    .update(mp);
        btnStop     .update(mp);
        btnAwariaBtn.update(mp);
        btnNapraw   .update(mp);
    }

    void draw(sf::RenderWindow& win, Roleta* r) {
        bool awaria = r->CzyAwaria();
        if (awaria) { win.draw(bgAwaria); win.draw(awariaBar); }
        else          win.draw(bg);

        win.draw(barBG); win.draw(barFill);
        win.draw(txtNazwa); win.draw(txtPokoj); win.draw(txtTyp);

        if (awaria) {
            win.draw(txtAwaria);
        } else {
            win.draw(txtStan);
            btnPodnies.draw(win); btnOpusc.draw(win); btnStop.draw(win);
        }
        win.draw(txtProc);
        btnAwariaBtn.draw(win);
        btnNapraw   .draw(win);
    }

    void draw(sf::RenderTexture& tex, Roleta* r) {
        bool awaria = r->CzyAwaria();
        if (awaria) { tex.draw(bgAwaria); tex.draw(awariaBar); }
        else          tex.draw(bg);

        tex.draw(barBG); tex.draw(barFill);
        tex.draw(txtNazwa); tex.draw(txtPokoj); tex.draw(txtTyp);

        if (awaria) {
            tex.draw(txtAwaria);
        } else {
            tex.draw(txtStan);
            btnPodnies.draw(tex); btnOpusc.draw(tex); btnStop.draw(tex);
        }
        tex.draw(txtProc);
        btnAwariaBtn.draw(tex);
        btnNapraw   .draw(tex);
    }
};

#endif
