#ifndef PRACOWNIK_H
#define PRACOWNIK_H

#include "Uzytkownik.h"

class Pracownik : public Uzytkownik {
    public:
        Pracownik(const std::string& login, const std::string& haslo);
        
        std::string Rola() const override;
};

#endif