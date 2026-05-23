#ifndef ROLETA_ZEWNATRZ_H
#define ROLETA_ZEWNATRZ_H

#include "Roleta.h"

class RoletaZewnatrz : public Roleta {
    private:
        bool blokadaAntywlamaniowa;
    public:
        RoletaZewnatrz(int id, const std::string& nazwa, const std::string& pokoj);

        void AktywujBlokade();
        void DezaktywujBlokade();

        std::string TypRolet() const override;
};

#endif