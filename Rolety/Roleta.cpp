#include "Roleta.h"
#include <iostream>

Roleta::Roleta(int id, const std::string& nazwa, const std::string& pokoj)
    : id(id), nazwa(nazwa), pokoj(pokoj), pozycja(0), awaria(false) {}

Roleta::~Roleta() {}

void Roleta::Podnies() {
    if (!awaria) {
        pozycja = 0;
    }
}

void Roleta::Opusc() {
    if (!awaria) {
        pozycja = 100;
    }
}

void Roleta::UstawPoziom(int poziom) {
    if (!awaria && poziom >= 0 && poziom <= 100) {
        this->pozycja = poziom;
    }
}

int Roleta::PobierzID() const {
    return id;
}

std::string Roleta::PobierzNazwe() const {
    return nazwa;
}

std::string Roleta::PobierzPokoj() const {
    return pokoj;
}

int Roleta::PobierzPoziom() const {
    return pozycja;
}

void Roleta::ZglosAwaria() {
    awaria = true;
}

void Roleta::Napraw() {
    awaria = false;
}

bool Roleta::CzyAwaria() const {
    return awaria;
}

std::string Roleta::Stan() const {
    if (awaria) {
        return "Awaria";
    } else if (pozycja == 0) {
        return "Podniesiona";
    } else if (pozycja == 100) {
        return "Opuszczona";
    } else {
        return "Poziom: " + std::to_string(pozycja) + "%";
    }
}