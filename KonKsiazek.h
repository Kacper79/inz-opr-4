#pragma once

#include "ObslugaIO.h"
#include "Ksiazka.h"

class KontrolerKsiazek {
public:
	KontrolerKsiazek(ObslugaIO& oio);
	~KontrolerKsiazek();

	Ksiazka* DodajNowaKsiazke(std::string tytul, std::string autor,int liczbaEgzemplarzy);
	Ksiazka* SzukajKsiazkiPoKID(int KID);
	Ksiazka* SzukajKsiazkiPoTytule(std::string tytul);
	void UsunKsiazke(int KID);

	void dodajEgzemplarz(Ksiazka*& ksiazka,int EID, int nrWydania);
	void usunEgzemplarz(Ksiazka*& ksiazka,int EID);
	const std::vector<Egzemplarz> wszystkieEgzemplarze(Ksiazka*& ksiazka) const;
	
	void zwrocEgzemplarz(Ksiazka*& ksiazka,int EID);
	void wypozyczEgzemplarz(Ksiazka*& ksiazka,int EID, std::string wypozczonyPrzez);

private:
	std::vector<Ksiazka*> stworzoneKsiazki;
	int licznikKID;
	ObslugaIO& oio;
};