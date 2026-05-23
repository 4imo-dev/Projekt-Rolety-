#ifndef ROLETA_H
#define ROLETA_H

#include <string>

class Roleta {
    protected:
        int id;
        std::string nazwa;
        std::string pokoj;
        int pozycja;
        bool awaria;

    public:
        Roleta(int id, const std::string& nazwa, const std::string& pokoj);
        virtual ~Roleta();

        virtual void Podnies();
        virtual void Opusc();
        virtual void UstawPoziom(int poziom);

        int PobierzID() const;
        std::string PobierzNazwe() const;
        std::string PobierzPokoj() const;
        int PobierzPoziom() const;

        void ZglosAwaria();
        void Napraw();
        bool CzyAwaria() const;

        virtual std::string TypRolet() const = 0;
        std::string Stan() const;
};

#endif