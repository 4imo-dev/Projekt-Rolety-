#include "Admin.h"

Admin::Admin(const std::string& login, const std::string& haslo)
    : Uzytkownik(login, haslo) {}

std::string Admin::Rola() const {
    return "Admin";
}