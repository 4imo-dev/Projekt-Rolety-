#include "RoletaWewnatrz.h"

RoletaWewnatrz::RoletaWewnatrz(int id, const std::string& nazwa, const std::string& pokoj)
    : Roleta(id, nazwa, pokoj) {}

std::string RoletaWewnatrz::TypRolet() const {
    return "Roleta Wewnętrzna"; 
}