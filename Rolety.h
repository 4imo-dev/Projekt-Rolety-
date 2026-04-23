#ifndef ROLETY_H
#define ROLETY_H

#include <string>

class Roleta {
private:
    int ID;
    int poziom;

public:
    Roleta(int ID);

    void Podnies();
    void Opusc();

    int PobierzPoziom() const;
    std::string Stan() const;
};

#endif