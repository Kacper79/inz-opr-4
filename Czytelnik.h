#pragma once
#include "Serializowalne.h"
#include <assert.h>
#include <string>

bool sprPoprImINaz(std::string iin);

class Czytelnik : public Serializowalne<Czytelnik>{
public:
	Czytelnik();
	Czytelnik(int CID,std::string imieINazwisko);
	Czytelnik(Czytelnik& inny) = delete;

	const std::string zwrocImieINazwisko() const;
	const int zwrocIDCzytelnika() const;

	template<typename T>
	void odczytaj(std::string zapisWLinii) {
		std::vector<std::string> pola = odczytajWartosciCSV(zapisWLinii);
		assert(pola.size() == 2);
		this->CID = atoi(pola[0].c_str());
		this->imieINazwisko = pola[1];
	}

	template<typename T>
	std::string zapisz(T* obiektDoZapisania) {
		std::vector<std::string> pola = { std::to_string(obiektDoZapisania->CID), obiektDoZapisania->imieINazwisko };
		return zapiszWartosciCSV(pola);
	}

private:
	int CID;
	std::string imieINazwisko;
};