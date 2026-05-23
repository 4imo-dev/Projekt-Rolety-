#include "Pracownik.h"

Pracownik::Pracownik(const std::string& login, const std::string& haslo)
    : Uzytkownik(login, haslo) {}

std::string Pracownik::Rola() const {
    return "Pracownik";
}