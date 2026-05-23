#include "RoletaZewnatrz.h"

RoletaZewnatrz::RoletaZewnatrz(int id, const std::string& nazwa, const std::string& pokoj)
    : Roleta(id, nazwa, pokoj), blokadaAntywlamaniowa(false) {}

void RoletaZewnatrz::AktywujBlokade() {
    blokadaAntywlamaniowa = true;
}

void RoletaZewnatrz::DezaktywujBlokade() {
    blokadaAntywlamaniowa = false;
}

std::string RoletaZewnatrz::TypRolet() const {
    return "Roleta Zewnętrzna"; 
}