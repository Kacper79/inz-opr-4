#include "Ksiazka.h"
#include <algorithm>

std::string zapiszEgzemplarze(std::vector<Egzemplarz> egz)
{
    std::string rekord = "";
    for (unsigned i = 0; i < egz.size(); i++) {
        Egzemplarz eg = egz[i];
        rekord += std::to_string(eg.EID);
        rekord += "|";
        rekord += eg.wypozyczonyPrzez;
        rekord += "|";
        rekord += std::to_string(eg.nrWydania);
        if (i != egz.size() - 1) rekord += ";";
    }   
    return rekord;
}

std::vector<Egzemplarz> odczytajEgzemplarze(std::string rekord)
{
    //Na poczatku rozdziel na wektor egzemplarzy
    std::vector<std::string> rekCzescWek(0);
    std::istringstream iss1(rekord);
    std::string elWek;
    while (std::getline(iss1, elWek, ';')) {
        rekCzescWek.push_back(elWek);
    }
    std::vector<Egzemplarz> egzempl(0);

    //Potem podziel kazda czesc rekordu na pojedynczy egzemplarz
    for (std::string czescRek : rekCzescWek) {
        std::vector<std::string> rekCzescEgz(0);
        std::istringstream iss2(czescRek);
        std::string pole;
        while (std::getline(iss2, pole, '|')) {
            rekCzescEgz.push_back(pole);
        }
       // for (int i = 0; i < rekCzescEgz.size(); i++) {
            Egzemplarz eg;
            eg.EID = atoi(rekCzescEgz[0].c_str());
            eg.wypozyczonyPrzez = rekCzescEgz[1];
            eg.nrWydania = atoi(rekCzescEgz[2].c_str());
            egzempl.push_back(eg);
        //}
    }

    return egzempl;
}

Ksiazka::Ksiazka() : Serializowalne(), KID(-1), tytul("Lorem ipsum"), autor("Anonim"), egzemplarze(std::vector<Egzemplarz>(0)) {}

Ksiazka::Ksiazka(int KID, std::string tytul, std::string autor, int liczbaEgzemplarzy) : Serializowalne(),KID(KID), tytul(tytul), autor(autor), egzemplarze(std::vector<Egzemplarz>(0)) {
    for (int i = 0; i < liczbaEgzemplarzy; i++) {
        egzemplarze.push_back({ i,"",1});
    }
}

const int Ksiazka::UzyskajIDKsiazki() const
{
    return KID;
}

const std::string Ksiazka::UzyskajTytul() const
{
    return tytul;
}

void Ksiazka::dodajEgzemplarz(int EID, int nrWydania)
{
    egzemplarze.push_back(Egzemplarz{EID, "", nrWydania});
}

void Ksiazka::usunEgzemplarz(int EID)
{
    /*for (auto it = egzemplarze.begin(); it != egzemplarze.end(); ++it) {
        if (it->EID == EID) egzemplarze.erase(it);
    }*/
    egzemplarze.erase(std::remove_if(egzemplarze.begin(), egzemplarze.end(), [EID](const auto& egz)
    {
            return egz.EID == EID;
    }), egzemplarze.end());
}

const std::vector<Egzemplarz> Ksiazka::wszystkieEgzemplarze() const
{
    return egzemplarze;
}

void Ksiazka::zwrocEgzemplarz(int EID)
{
    for (auto it = egzemplarze.begin(); it != egzemplarze.end(); it++) {
        if (it->EID == EID) {
            it->wypozyczonyPrzez = "";
        }
    }
}

void Ksiazka::wypozyczEgzemplarz(int EID, std::string wypozczonyPrzez)
{
    for (auto it = egzemplarze.begin(); it != egzemplarze.end(); it++) {
        if (it->EID == EID) {
            it->wypozyczonyPrzez = wypozczonyPrzez;
        }
    }
}
