#ifndef SYSTEMROLET_H
#define SYSTEMROLET_H

#include <vector>
#include "../Rolety/Roleta.h"
#include "Logger.h"

class SystemRolet {
    private:
        std::vector<Roleta*> rolety;
        Logger logger;

    public:
        void DodajRoleta(Roleta* roleta);

        void PokazRolety() const;

        void PodniesRoleta(int id);
        void OpuscRoleta(int id);

        void WyswietlLogi() const;
};

#endif