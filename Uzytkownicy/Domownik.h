#ifndef DOMOWNIK_H
#define DOMOWNIK_H

#include "Uzytkownik.h"
#include <vector>

class Domownik : public Uzytkownik {
    private:
        std::vector<std::string> pokoje;

    public:
        Domownik(const std::string& login, const std::string& haslo);
        
        void DodajPokoj(const std::string& pokoj);

        bool CzyMaDostep(const std::string& pokoj) const;

        std::string Rola() const override;
};

#endif