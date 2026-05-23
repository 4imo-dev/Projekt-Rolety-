#ifndef ADMIN_H
#define ADMIN_H

#include "Uzytkownik.h"

class Admin : public Uzytkownik {
    public:
        Admin(const std::string& login, const std::string& haslo);
        
        std::string Rola() const override;
};

#endif