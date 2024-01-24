#include "KonCzytelnika.h"

constexpr NAZWA_TABEL typTabeli = NAZWA_TABEL::CZYTELNICY;

KontrolerCzytelnika::KontrolerCzytelnika(ObslugaIO& oio) : oio(oio)
{
	licznikCID = oio.znajdzNajwyzszeID(typTabeli) + 1;
	stworzeniCzytelnicy = std::vector<Czytelnik*>(0);
}

KontrolerCzytelnika::~KontrolerCzytelnika()
{
	for (unsigned i = 0; i < stworzeniCzytelnicy.size(); i++) {
		delete stworzeniCzytelnicy[i];
	}
}

Czytelnik* KontrolerCzytelnika::StworzNowegoCzytelnika(std::string imieINazwisko)
{
	Czytelnik* nowyCzytelnik = new Czytelnik(licznikCID, imieINazwisko);
	stworzeniCzytelnicy.push_back(nowyCzytelnik);
	std::string nowyRekord = nowyCzytelnik->zapisz(nowyCzytelnik);
	oio.dodajNowyRekord(typTabeli, nowyRekord, licznikCID);
	licznikCID++;
	return nowyCzytelnik;
}

Czytelnik* KontrolerCzytelnika::SzukajCzytelnikaPoImieniu(std::string imieINazwisko)
{
	std::string znalezionyRekord = oio.szukajRekorduPoPolu(typTabeli, 1, imieINazwisko);
	if (znalezionyRekord == "") return nullptr;
	Czytelnik* nowyCzytelnik = new Czytelnik();
	nowyCzytelnik->odczytaj<Czytelnik>(znalezionyRekord);
	stworzeniCzytelnicy.push_back(nowyCzytelnik);
	return nowyCzytelnik;
}

Czytelnik* KontrolerCzytelnika::SzukajCzytelnikaPoCID(int CID)
{
	std::string znalezionyRekord = oio.szukajRekordu(typTabeli, CID);
	if (znalezionyRekord == "") return nullptr;
	Czytelnik* nowyCzytelnik = new Czytelnik();
	nowyCzytelnik->odczytaj<Czytelnik>(znalezionyRekord);
	stworzeniCzytelnicy.push_back(nowyCzytelnik);
	return nowyCzytelnik;
}

void KontrolerCzytelnika::UsunCzytelnika(Czytelnik*& czytelnik)
{
	oio.usunRekord(typTabeli, czytelnik->zwrocIDCzytelnika());
	//czytelnik = nullptr;
}
