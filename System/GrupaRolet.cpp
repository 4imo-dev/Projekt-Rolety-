#include "GrupaRolet.h"

GrupaRolet::GrupaRolet(const std::string& nazwa) : nazwa(nazwa) {}

void GrupaRolet::DodajRoleta(Roleta* roleta) {
    rolety.push_back(roleta);
}

void GrupaRolet::PodniesWszystkie() {
    for (auto& roleta : rolety) {
        roleta->Podnies();
    }
}

void GrupaRolet::OpuscWszystkie() {
    for (auto& roleta : rolety) {
        roleta->Opusc();
    }
}