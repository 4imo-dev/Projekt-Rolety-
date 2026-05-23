#include "SystemRolet.h"
#include <iostream>

void SystemRolet::DodajRoleta(Roleta* roleta) {
    rolety.push_back(roleta);
    logger.DodajLog("Dodano rolete: " + roleta->PobierzNazwe());
}

void SystemRolet::PokazRolety() const {
    for (const auto& roleta : rolety) {
        std::cout << "ID: " << roleta->PobierzID() 
                  << ", Nazwa: " << roleta->PobierzNazwe() 
                  << ", Pokój: " << roleta->PobierzPokoj() 
                  << ", Stan: " << roleta->Stan() << std::endl;
    }
}

void SystemRolet::PodniesRoleta(int id) {
    for (auto& roleta : rolety) {
        if (roleta->PobierzID() == id) {
            roleta->Podnies();
            logger.DodajLog("Podniesiono rolete: " + roleta->PobierzNazwe());
            return;
        }
    }
    std::cout << "Nie znaleziono rolety o ID: " << id << std::endl;
}

void SystemRolet::OpuscRoleta(int id) {
    for (auto& roleta : rolety) {
        if (roleta->PobierzID() == id) {
            roleta->Opusc();
            logger.DodajLog("Opuszczono rolete: " + roleta->PobierzNazwe());
            return;
        }
    }
    std::cout << "Nie znaleziono rolety o ID: " << id << std::endl;
}

void SystemRolet::WyswietlLogi() const {
    logger.WyswietlLogi();
}