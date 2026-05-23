#include "Domownik.h"

Domownik::Domownik(const std::string& login, const std::string& haslo)
    : Uzytkownik(login, haslo) {}

void Domownik::DodajPokoj(const std::string& pokoj) {
    pokoje.push_back(pokoj);
}

bool Domownik::CzyMaDostep(const std::string& pokoj) const {
    for (const auto& p : pokoje) {
        if (p == pokoj) {
            return true;
        }
    }

    return false;
}

std::string Domownik::Rola() const {
    return "Domownik";
}