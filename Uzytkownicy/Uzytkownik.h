#ifndef UZYTKOWNIK_H
#define UZYTKOWNIK_H

#include <string>

class Uzytkownik {
    protected:
        std::string login;
        std::string haslo;

    public:
        Uzytkownik(const std::string& login, const std::string& haslo);
        
        virtual ~Uzytkownik();

        std::string PobierzLogin() const;

        bool SprawdzHaslo(const std::string& haslo) const;

        virtual std::string Rola() const = 0;
};

#endif