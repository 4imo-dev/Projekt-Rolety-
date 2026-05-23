#ifndef ROLETA_WEWNATRZ_H
#define ROLETA_WEWNATRZ_H

#include "Roleta.h"

class RoletaWewnatrz : public Roleta {
    public:
        RoletaWewnatrz(int id, const std::string& nazwa, const std::string& pokoj);

        std::string TypRolet() const override;
};

#endif