#include "Uzytkownik.h"

Uzytkownik::Uzytkownik(const std::string& login, const std::string& haslo)
    : login(login), haslo(haslo) {}

Uzytkownik::~Uzytkownik() {}

std::string Uzytkownik::PobierzLogin() const {
    return login;
}

bool Uzytkownik::SprawdzHaslo(const std::string& haslo) const {
    return this->haslo == haslo;
}