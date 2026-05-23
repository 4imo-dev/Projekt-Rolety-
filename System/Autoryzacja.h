#ifndef AUTORYZACJA_H
#define AUTORYZACJA_H

#include "../Uzytkownicy/Uzytkownik.h"

class Autoryzacja {
    public:
        static bool CzyAdmin(Uzytkownik* uzytkownik);
        static bool CzyPracownik(Uzytkownik* uzytkownik);
        static bool CzyDomownik(Uzytkownik* uzytkownik);
};

#endif