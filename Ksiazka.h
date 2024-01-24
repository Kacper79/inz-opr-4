#pragma once
#include "Serializowalne.h"
#include <assert.h>
#include <string>

struct Egzemplarz {
	int EID;
	std::string wypozyczonyPrzez;
	int nrWydania;
};

std::string zapiszEgzemplarze(std::vector<Egzemplarz> egz);
std::vector<Egzemplarz> odczytajEgzemplarze(std::string rekord);

class Ksiazka : public Serializowalne<Ksiazka> {
public:
	Ksiazka();
	Ksiazka(int KID, std::string tytul, std::string autor, int liczbaEgzemplarzy);
	Ksiazka(Ksiazka& inny) = delete;

	const int UzyskajIDKsiazki() const;
	const std::string UzyskajTytul() const;

	void dodajEgzemplarz(int EID, int nrWydania);
	void usunEgzemplarz(int EID);
	
	const std::vector<Egzemplarz> wszystkieEgzemplarze() const;
	void zwrocEgzemplarz(int EID);
	void wypozyczEgzemplarz(int EID, std::string wypozczonyPrzez);

	template<typename T>
	void odczytaj(std::string zapisWLinii) {
		std::vector<std::string> pola = odczytajWartosciCSV(zapisWLinii);
		assert(pola.size() == 4);
		this->KID = atoi(pola[0].c_str());
		this->tytul = pola[1];
		this->autor = pola[2];
		this->egzemplarze = odczytajEgzemplarze(pola[3].c_str());
	}

	template<typename T>
	std::string zapisz(T* obiektDoZapisania) {
		std::vector<std::string> pola = {std::to_string(obiektDoZapisania->KID), obiektDoZapisania->tytul, obiektDoZapisania->autor, zapiszEgzemplarze(obiektDoZapisania->egzemplarze) };
		return zapiszWartosciCSV(pola);
	}

private:
	int KID;
	std::string tytul;
	std::string autor;
	std::vector<Egzemplarz> egzemplarze;
};