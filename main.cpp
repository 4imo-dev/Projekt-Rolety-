// GŁÓWNY PROGRAM - SYSTEM ROLET

#include <iostream>
#include "Rolety.h"

int main() {
    Roleta r1(1);
    Roleta r2(2);

    r1.Opusc();
    r2.Podnies();

    std::cout << r1.Stan() << std::endl;
    std::cout << r2.Stan() << std::endl;

    r1.Podnies();
    r2.Opusc();

    std::cout << r1.Stan() << std::endl;
    std::cout << r2.Stan() << std::endl;

    return 0;
}