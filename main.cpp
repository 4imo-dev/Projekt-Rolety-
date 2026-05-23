#include <iostream>

#include "Rolety/RoletaWewnatrz.h"
#include "Rolety/RoletaZewnatrz.h"
#include "System/GrupaRolet.h"
#include "System/SystemRolet.h"

int main() {
    SystemRolet system;

    RoletaWewnatrz roleta1(1, "Roleta Salon", "Salon");
    RoletaWewnatrz roleta2(2, "Roleta Kuchnia", "Kuchnia");
    RoletaZewnatrz roleta3(3, "Roleta Taras", "Taras");

    system.DodajRoleta(&roleta1);
    system.DodajRoleta(&roleta2);
    system.DodajRoleta(&roleta3);

    system.PokazRolety();

    std::cout << std::endl;

    system.PodniesRoleta(1);
    system.OpuscRoleta(2);

    std::cout << "\n Po zmianach:\n";
    system.PokazRolety();

    std::cout << "\n Grupa parter:\n";
    GrupaRolet grupa("Parter");

    grupa.DodajRoleta(&roleta1);
    grupa.DodajRoleta(&roleta2);

    grupa.PodniesWszystkie();
    system.PokazRolety();

    std::cout << "\n Logi:\n";
    system.WyswietlLogi();

    return 0;
}