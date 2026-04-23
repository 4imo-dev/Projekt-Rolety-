#include "Rolety.h"
#include <iostream>
#include <string>

Roleta::Roleta(int id) : ID(id), poziom(0) {}

void Roleta::Podnies() {
    poziom = 0;
}

void Roleta::Opusc() {
    poziom = 100;
}

int Roleta::PobierzPoziom() const {
    return poziom;
}

std::string Roleta::Stan() const {
    if (poziom == 0)
        return "otwarta";
    else if (poziom == 100)
        return "zamknięta";
    else
        return "Niemożliwe na tym etapie";
}