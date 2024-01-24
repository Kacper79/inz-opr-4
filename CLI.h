#pragma once
#include <iostream>
#include <functional>
#include <string>
#include <sstream>
#include <limits>
#include <unordered_map>
#define NOMINMAX
#include <Windows.h>

#include "KonCzytelnika.h"
#include "KonKsiazek.h"
#include "KonList.h"
//#include "Obserwator.h"

class CLI {
public:
	CLI() : oio(ObslugaIO()), ObecnyCzytelnik(nullptr), ObecnaKsiazka(nullptr) {
		konCzytelnika = new KontrolerCzytelnika(oio);
		konKsiazek = new KontrolerKsiazek(oio);
		ksiazkiObserwowane = std::unordered_map<int, Subject*>();
		obserwatorzy = std::vector<Observer*>(0);
		konList = new KontrolerList(oio);
		UzupelnijDwojkeObserwatorow();
		//skonstruuj obserwatorow
	}

	~CLI();
	void WybierzOperacjeUI();
	void WybierzOperacjeCzytelnikaUI();
	void PodajDaneCzytelnikaUI();
	void ModyfikujZbioryUI();
	void WypozyczEgzemplarzUI();
	void ZwrocEgzemplarzUI();
	void SprawdzDostepnoscTytuluUI();

	void CzyscEkran();
	void WykonajFunkcjeUI();

private:
	void CzyscBuforWejscia();
	void SprawdzWiadomosci();
	void UzupelnijDwojkeObserwatorow();
	void ZapiszNaListe();
	void WyczyscListe(int KID);

	template <typename T>
	inline bool wprowadzZmienna(T& zmienna) {
		std::cin >> zmienna;
		return std::cin.good();
	}

	template <typename T>
	inline bool wprowadzZmienna(std::istream& istr, T& zmienna) {
		istr >> zmienna;
		return std::cin.good();
	}

	inline void wprowadzTekst(std::string& zmienna) {
		std::getline(std::cin, zmienna);
	}

private:
	void (CLI::* obecnaFunckjaUI)() = &CLI::WybierzOperacjeUI;

	int ObecneIDCzytelnika = -1;
	Czytelnik* ObecnyCzytelnik;
	int ObecneIDKsiazki = -1;
	Ksiazka* ObecnaKsiazka;

	KontrolerCzytelnika* konCzytelnika;
	KontrolerKsiazek* konKsiazek;
	KontrolerList* konList;
	ObslugaIO oio;

	std::unordered_map<int,Subject*> ksiazkiObserwowane;
	std::vector<Observer*> obserwatorzy;
};