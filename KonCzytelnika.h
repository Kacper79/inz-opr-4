#pragma once

#include "ObslugaIO.h"
#include "Czytelnik.h"

class KontrolerCzytelnika {
public:
	KontrolerCzytelnika(ObslugaIO& oio);
	~KontrolerCzytelnika();

	Czytelnik* StworzNowegoCzytelnika(std::string imieINazwisko);
	Czytelnik* SzukajCzytelnikaPoImieniu(std::string imieINazwisko);
	Czytelnik* SzukajCzytelnikaPoCID(int CID);
	void UsunCzytelnika(Czytelnik*& czytelnik);
private:
	std::vector<Czytelnik*> stworzeniCzytelnicy;
	int licznikCID;
	ObslugaIO& oio;
};