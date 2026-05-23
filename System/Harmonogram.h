#ifndef HARMONOGRAM_H
#define HARMONOGRAM_H

#include <string>
#include <vector>

struct RegulaCzasowa {
    std::string godzina;
    int idRolet;
    int poziom;
};

class Harmonogram {
    private:
        std::vector<RegulaCzasowa> reguly;

    public:
        void DodajRegule(const RegulaCzasowa& regula);
        void PokazReguly() const;
};

#endif