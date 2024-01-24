#pragma once
#include <vector>
#include <unordered_map>
#include <assert.h>
#include <algorithm>
#include "Serializowalne.h"

class ListaOczekujacych : public Serializowalne<ListaOczekujacych> {
public:
	ListaOczekujacych();
	ListaOczekujacych(int OID, int KID);
	ListaOczekujacych(ListaOczekujacych& inny) = delete;

	const int ZwrocIDListy() const;
	const int ZwrocIDKsiazki() const;
	std::vector<int> ZwrocSubskrybentow() const;

	void DodajNaListe(int CID);
	void WyczyscListe();

	template<typename T>
	void odczytaj(std::string zapisWLinii) {
		std::vector<std::string> pola = odczytajWartosciCSV(zapisWLinii);
		assert(pola.size() == 3);
		this->OID = atoi(pola[0].c_str());
		this->KID = atoi(pola[1].c_str());
		std::vector<std::string> czytWek = odczytajWektorJakoSCSV(pola[2].c_str());
		std::vector<int>& czytelnicy = ListaOczekujacych::CIDs;
		for_each(czytWek.begin(), czytWek.end(), [&czytelnicy](std::string& el) {
			czytelnicy.push_back(atoi(el.c_str()));
		});
	}

	template<typename T>
	std::string zapisz(T* obiektDoZapisania) {
		std::vector<int>& czytelnicy = obiektDoZapisania->CIDs;
		std::vector<std::string> CIDy;
		for_each(czytelnicy.begin(), czytelnicy.end(), [&CIDy](int& el) {
			CIDy.push_back(std::to_string(el));
		});
		std::vector<std::string> pola = { std::to_string(obiektDoZapisania->OID), std::to_string(obiektDoZapisania->KID), zapiszWektorJakoSCSV(CIDy) };
		return zapiszWartosciCSV(pola);
	}

private:
	int OID;
	int KID;
	std::vector<int> CIDs;
};