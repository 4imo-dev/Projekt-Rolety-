#include "Harmonogram.h"
#include <iostream>

void Harmonogram::DodajRegule(const RegulaCzasowa& regula) {
    reguly.push_back(regula);
}

void Harmonogram::PokazReguly() const {
    for (const auto& regula : reguly) {
        std::cout << "Godzina: " << regula.godzina 
                  << ", ID Rolety: " << regula.idRolet 
                  << ", Poziom: " << regula.poziom << std::endl;
    }
}