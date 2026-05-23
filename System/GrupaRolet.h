#ifndef GRUPAROLET_H
#define GRUPAROLET_H

#include <vector>
#include <string>
#include "../Rolety/Roleta.h"

class GrupaRolet {
    private:
        std::vector<Roleta*> rolety;
        std::string nazwa;

    public:
        GrupaRolet(const std::string& nazwa);

        void DodajRoleta(Roleta* roleta);

        void PodniesWszystkie();
        void OpuscWszystkie();
};

#endif