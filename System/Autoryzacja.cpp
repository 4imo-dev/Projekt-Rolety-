#include "Autoryzacja.h"

bool Autoryzacja::CzyAdmin(Uzytkownik* uzytkownik) {
    return uzytkownik->Rola() == "Admin";
}

bool Autoryzacja::CzyPracownik(Uzytkownik* uzytkownik) {
    return uzytkownik->Rola() == "Pracownik";
}

bool Autoryzacja::CzyDomownik(Uzytkownik* uzytkownik) {
    return uzytkownik->Rola() == "Domownik";
}