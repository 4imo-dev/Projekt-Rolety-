#include <SFML/Graphics.hpp>
#include <vector>
#include <tuple>
#include <string>

#include "GUI/Colors.h"
#include "GUI/Button.h"
#include "GUI/RoletaCard.h"
#include "GUI/LoginScreen.h"
#include "GUI/LogPanel.h"
#include "GUI/AddRoletaPanel.h"

#include "Rolety/RoletaWewnatrz.h"
#include "Rolety/RoletaZewnatrz.h"
#include "System/SystemRolet.h"

enum class Screen { Login, Main };
enum class Rola   { Admin, Pracownik, Domownik };

const float W       = 960;
const float H       = 680;
const float HEADER  = 58;   // wysokość paska górnego
const float LOGAREA = 100;  // wysokość panelu logów
const float CARDH   = 160;  // wysokość jednej karty + margines
const float SCROLLAREA = H - HEADER - LOGAREA; // obszar kart

void rebuildKarty(std::vector<RoletaCard>& karty,
                  std::vector<RoletaState>& stany,
                  const std::vector<Roleta*>& rolety,
                  sf::Font& font, Rola rola)
{
    karty.clear();
    bool canRepair = (rola != Rola::Domownik);
    for (int i = 0; i < (int)rolety.size(); i++) {
        RoletaCard card;
        // Y pozycja w przestrzeni "wirtualnej" (przed scrollem)
        float x = 14;
        float y = 8 + i * CARDH;
        card.build(x, y, W - 28, rolety[i], font, canRepair);
        karty.push_back(card);
    }
    while (stany.size() < rolety.size())
        stany.push_back(RoletaState{});
}

int main() {
    sf::RenderWindow window(sf::VideoMode((int)W, (int)H),
                            "System Rolet",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
        if (!font.loadFromFile("arial.ttf"))
            if (!font.loadFromFile("bin/Debug/arial.ttf"))
                return -1;

    SystemRolet system;
    std::vector<Roleta*>         rolety;
    std::vector<RoletaWewnatrz*> poolW;
    std::vector<RoletaZewnatrz*> poolZ;
    int nextID = 4;

    auto* r1 = new RoletaWewnatrz(1, "Roleta Salon",   "Salon");
    auto* r2 = new RoletaWewnatrz(2, "Roleta Kuchnia", "Kuchnia");
    auto* r3 = new RoletaZewnatrz(3, "Roleta Taras",   "Taras");
    poolW.push_back(r1); poolW.push_back(r2); poolZ.push_back(r3);
    system.DodajRoleta(r1); system.DodajRoleta(r2); system.DodajRoleta(r3);
    rolety = {r1, r2, r3};

    Screen screen = Screen::Login;
    Rola   rola   = Rola::Pracownik;

    std::vector<std::tuple<std::string,std::string,Rola>> uzytkownicy = {
        {"admin",    "admin123", Rola::Admin},
        {"domownik", "dom123",   Rola::Domownik},
        {"pracownik","prac123",  Rola::Pracownik}
    };

    LoginScreen    loginScreen; loginScreen.build(font, W, H);
    LogPanel       logPanel;    logPanel.build(14, H - LOGAREA + 8, W - 28, LOGAREA - 16, font);
    AddRoletaPanel addPanel;    addPanel.build(font, W, H);

    std::vector<RoletaCard>  karty;
    std::vector<RoletaState> stany;

    // Scrollowanie
    float scrollY    = 0.f;  // aktualne przesunięcie w px
    float scrollMax  = 0.f;  // maksymalne przesunięcie

    auto updateScrollMax = [&]() {
        float totalH = (float)rolety.size() * CARDH;
        scrollMax = std::max(0.f, totalH - SCROLLAREA + 16.f);
    };

    Button btnWyloguj, btnDodajBtn;
    btnWyloguj.init(W - 110, 14, 96, 30, "Wyloguj", font, Colors::Red, {160,40,40});
    btnDodajBtn.init(W - 220, 14, 100, 30, "+ Roleta", font, Colors::Green, {30,140,60});
    btnDodajBtn.visible = false;

    sf::Text lblTytul      = makeText("System Rolet", font, 16, Colors::Accent,  14, 12);
    sf::Text lblZalogowany = makeText("",             font, 12, Colors::TextDim, 14, 32);

    // Pasek scrollowania
    sf::RectangleShape scrollTrack = makeRect(W - 10, HEADER, 6, SCROLLAREA, {40,44,60});
    sf::RectangleShape scrollThumb = makeRect(W - 10, HEADER, 6, 30,         Colors::AccentDim);

    auto updateScrollThumb = [&]() {
        if (scrollMax <= 0) { scrollThumb.setSize({6, (float)SCROLLAREA}); return; }
        float ratio     = SCROLLAREA / ((float)rolety.size() * CARDH);
        float thumbH    = std::max(30.f, SCROLLAREA * ratio);
        float thumbY    = HEADER + (scrollY / scrollMax) * (SCROLLAREA - thumbH);
        scrollThumb.setSize({6, thumbH});
        scrollThumb.setPosition(W - 10, thumbY);
    };

    // Viewport — renderujemy karty na osobnej teksturze z przesunięciem
    sf::RenderTexture viewport;
    viewport.create((unsigned)W, (unsigned)SCROLLAREA);

    auto tryLogin = [&]() {
        for (auto& [l, h, r] : uzytkownicy) {
            if (l == loginScreen.inputLogin && h == loginScreen.inputPass) {
                rola = r;
                screen = Screen::Main;
                loginScreen.error = false;
                scrollY = 0;
                rebuildKarty(karty, stany, rolety, font, rola);
                updateScrollMax();
                updateScrollThumb();
                btnDodajBtn.visible = (rola == Rola::Admin);
                std::string rolaNapis = (r == Rola::Admin)    ? " [Admin]" :
                                        (r == Rola::Domownik) ? " [Domownik]" : " [Pracownik]";
                lblZalogowany.setString("Zalogowany: " + l + rolaNapis);
                logPanel.add("Zalogowano: " + l);
                return;
            }
        }
        loginScreen.error = true;
    };

    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        sf::Vector2i mp = sf::Mouse::getPosition(window);

        // Pozycja myszy w przestrzeni viewport (ze scrollem)
        sf::Vector2i mpScroll(mp.x, mp.y - (int)HEADER + (int)scrollY);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();

            // ---- LOGIN ----
            if (screen == Screen::Login) {
                if (event.type == sf::Event::TextEntered)
                    loginScreen.handleText(event.text.unicode);
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Tab)
                        loginScreen.focusLogin = !loginScreen.focusLogin;
                    if (event.key.code == sf::Keyboard::Enter)
                        tryLogin();
                }
                if (event.type == sf::Event::MouseButtonPressed &&
                    event.mouseButton.button == sf::Mouse::Left) {
                    loginScreen.handleClick(mp, W, H);
                    if (loginScreen.btnZaloguj.contains(mp)) tryLogin();
                }
            }

            // ---- MAIN ----
            if (screen == Screen::Main) {

                // Scroll kółkiem myszy
                if (event.type == sf::Event::MouseWheelScrolled) {
                    scrollY -= event.mouseWheelScroll.delta * 40.f;
                    scrollY = std::max(0.f, std::min(scrollY, scrollMax));
                    updateScrollThumb();
                }

                if (addPanel.visible) {
                    if (event.type == sf::Event::TextEntered)
                        addPanel.handleText(event.text.unicode);
                    if (event.type == sf::Event::MouseButtonPressed &&
                        event.mouseButton.button == sf::Mouse::Left) {
                        bool outside = addPanel.handleClick(mp, W, H);
                        if (outside) addPanel.visible = false;
                        if (addPanel.btnDodaj.contains(mp) && addPanel.readyToAdd()) {
                            if (addPanel.typWybor == 0) {
                                auto* nr = new RoletaWewnatrz(nextID++,
                                    addPanel.inputNazwa, addPanel.inputPokoj);
                                poolW.push_back(nr);
                                rolety.push_back(nr);
                                system.DodajRoleta(nr);
                            } else {
                                auto* nr = new RoletaZewnatrz(nextID++,
                                    addPanel.inputNazwa, addPanel.inputPokoj);
                                poolZ.push_back(nr);
                                rolety.push_back(nr);
                                system.DodajRoleta(nr);
                            }
                            logPanel.add("Dodano: " + addPanel.inputNazwa);
                            addPanel.reset();
                            rebuildKarty(karty, stany, rolety, font, rola);
                            updateScrollMax();
                            // przewiń na dół żeby zobaczyć nową roletę
                            scrollY = scrollMax;
                            updateScrollThumb();
                        }
                    }
                } else {
                    if (event.type == sf::Event::MouseButtonPressed &&
                        event.mouseButton.button == sf::Mouse::Left) {

                        if (btnWyloguj.contains(mp)) {
                            screen = Screen::Login;
                            loginScreen.inputLogin.clear();
                            loginScreen.inputPass.clear();
                            loginScreen.error = false;
                        }
                        if (btnDodajBtn.contains(mp) && rola == Rola::Admin)
                            addPanel.visible = true;

                        // kliknięcia kart (z uwzględnieniem scrollu)
                        for (int i = 0; i < (int)karty.size(); i++) {
                            auto& k  = karty[i];
                            auto* r  = rolety[i];
                            auto& st = stany[i];

                            if (k.btnPodnies.contains(mpScroll)) {
                                st.anim = RoletaAnim::Opening;
                                logPanel.add("Podnoszenie: " + r->PobierzNazwe());
                            }
                            if (k.btnOpusc.contains(mpScroll)) {
                                st.anim = RoletaAnim::Closing;
                                logPanel.add("Opuszczanie: " + r->PobierzNazwe());
                            }
                            if (k.btnStop.contains(mpScroll)) {
                                st.anim = RoletaAnim::Idle;
                                r->UstawPoziom((int)st.currentPos);
                                logPanel.add("Stop: " + r->PobierzNazwe() +
                                             " @ " + std::to_string((int)st.currentPos) + "%");
                            }
                            if (k.btnAwariaBtn.contains(mpScroll)) {
                                r->ZglosAwaria();
                                st.anim = RoletaAnim::Idle;
                                logPanel.add("AWARIA: " + r->PobierzNazwe());
                            }
                            if (k.btnNapraw.contains(mpScroll) && rola != Rola::Domownik) {
                                r->Napraw();
                                logPanel.add("Naprawiono: " + r->PobierzNazwe());
                            }
                        }
                    }
                }
            }
        }

        // ---- ANIMACJA ----
        if (screen == Screen::Main) {
            for (int i = 0; i < (int)rolety.size(); i++) {
                auto& st = stany[i];
                auto* r  = rolety[i];
                if (r->CzyAwaria()) { st.anim = RoletaAnim::Idle; continue; }

                if (st.anim == RoletaAnim::Closing) {
                    st.currentPos += st.speed * dt;
                    if (st.currentPos >= 100.f) {
                        st.currentPos = 100.f;
                        st.anim = RoletaAnim::Idle;
                        r->Opusc();
                    }
                } else if (st.anim == RoletaAnim::Opening) {
                    st.currentPos -= st.speed * dt;
                    if (st.currentPos <= 0.f) {
                        st.currentPos = 0.f;
                        st.anim = RoletaAnim::Idle;
                        r->Podnies();
                    }
                }
                if (i < (int)karty.size())
                    karty[i].refresh(r, st.currentPos);
            }
        }

        // ---- HOVER (z uwzględnieniem scrollu) ----
        if (screen == Screen::Login) loginScreen.update(mp);
        if (screen == Screen::Main) {
            btnWyloguj.update(mp);
            btnDodajBtn.update(mp);
            for (auto& k : karty) k.updateHover(mpScroll);
            addPanel.update(mp);
        }

        // ---- RYSOWANIE ----
        window.clear(Colors::BG);

        if (screen == Screen::Login) {
            loginScreen.draw(window, font, W, H);
        } else {
            // --- Render kart na viewport texture (scroll) ---
            viewport.clear(Colors::BG);
            sf::View view(sf::FloatRect(0, scrollY, W, SCROLLAREA));
            viewport.setView(view);
            for (int i = 0; i < (int)karty.size(); i++) karty[i].draw(viewport, rolety[i]);
            viewport.display();

            // Narysuj viewport na oknie
            sf::Sprite vpSprite(viewport.getTexture());
            vpSprite.setPosition(0, HEADER);
            window.draw(vpSprite);

            // Panel logów (na stałe na dole)
            window.draw(makeRect(0, H - LOGAREA, W, LOGAREA, Colors::Panel));
            logPanel.draw(window, font);

            // Górny pasek (na wierzchu)
            window.draw(makeRect(0, 0, W, HEADER, Colors::Panel));
            window.draw(lblTytul);
            window.draw(lblZalogowany);
            btnWyloguj .draw(window);
            btnDodajBtn.draw(window);

            // Pasek scrollowania
            if (scrollMax > 0) {
                window.draw(scrollTrack);
                window.draw(scrollThumb);
            }

            addPanel.draw(window, font, W, H);
        }

        window.display();
    }

    for (auto* r : poolW) delete r;
    for (auto* r : poolZ) delete r;
    return 0;
}
