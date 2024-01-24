#include "KonKsiazek.h"

constexpr NAZWA_TABEL typTabeli = NAZWA_TABEL::KSIAZKI;

KontrolerKsiazek::KontrolerKsiazek(ObslugaIO& oio) : oio(oio)
{
	licznikKID = oio.znajdzNajwyzszeID(typTabeli) + 1;
	stworzoneKsiazki = std::vector<Ksiazka*>(0);
}

KontrolerKsiazek::~KontrolerKsiazek()
{
	for (unsigned i = 0; i < stworzoneKsiazki.size(); i++) {
		delete stworzoneKsiazki[i];
	}
}

Ksiazka* KontrolerKsiazek::DodajNowaKsiazke(std::string tytul, std::string autor, int liczbaEgzemplarzy)
{
	Ksiazka* nowaKsiazka = new Ksiazka(licznikKID, tytul, autor, liczbaEgzemplarzy);
	stworzoneKsiazki.push_back(nowaKsiazka);
	std::string nowyRekord = nowaKsiazka->zapisz(nowaKsiazka);
	oio.dodajNowyRekord(typTabeli, nowyRekord, licznikKID);
	licznikKID++;
	return nowaKsiazka;
}

Ksiazka* KontrolerKsiazek::SzukajKsiazkiPoKID(int KID)
{
	std::string znalezionyRekord = oio.szukajRekordu(typTabeli, KID);
	if (znalezionyRekord == "") return nullptr;
	Ksiazka* nowaKsiazka = new Ksiazka();
	nowaKsiazka->odczytaj<Ksiazka>(znalezionyRekord);
	stworzoneKsiazki.push_back(nowaKsiazka);
	return nowaKsiazka;
}

Ksiazka* KontrolerKsiazek::SzukajKsiazkiPoTytule(std::string tytul)
{
	std::string znalezionyRekord = oio.szukajRekorduPoPolu(typTabeli, 1, tytul);
	if (znalezionyRekord == "") return nullptr;
	Ksiazka* nowaKsiazka = new Ksiazka();
	nowaKsiazka->odczytaj<Ksiazka>(znalezionyRekord);
	stworzoneKsiazki.push_back(nowaKsiazka);
	return nowaKsiazka;
}

void KontrolerKsiazek::UsunKsiazke(int KID)
{
	oio.usunRekord(typTabeli, KID);
}

void KontrolerKsiazek::dodajEgzemplarz(Ksiazka*& ksiazka, int EID, int nrWydania)
{
	ksiazka->dodajEgzemplarz(EID, nrWydania);
	std::string zedytRekord = ksiazka->zapisz(ksiazka);
	oio.edytujRekord(typTabeli, zedytRekord, ksiazka->UzyskajIDKsiazki()); 
}

void KontrolerKsiazek::usunEgzemplarz(Ksiazka*& ksiazka,int EID)
{
	ksiazka->usunEgzemplarz(EID);
	std::string zedytRekord = ksiazka->zapisz(ksiazka);
	oio.edytujRekord(typTabeli, zedytRekord, ksiazka->UzyskajIDKsiazki()); 
}

const std::vector<Egzemplarz> KontrolerKsiazek::wszystkieEgzemplarze(Ksiazka*& ksiazka) const
{
	return ksiazka->wszystkieEgzemplarze();
}

void KontrolerKsiazek::zwrocEgzemplarz(Ksiazka*& ksiazka,int EID)
{
	ksiazka->zwrocEgzemplarz(EID);
	std::string zedytRekord = ksiazka->zapisz(ksiazka);
	oio.edytujRekord(typTabeli, zedytRekord, ksiazka->UzyskajIDKsiazki()); 
}

void KontrolerKsiazek::wypozyczEgzemplarz(Ksiazka*& ksiazka,int EID, std::string wypozczonyPrzez)
{
	ksiazka->wypozyczEgzemplarz(EID, wypozczonyPrzez);
	std::string zedytRekord = ksiazka->zapisz(ksiazka);
	oio.edytujRekord(typTabeli, zedytRekord, ksiazka->UzyskajIDKsiazki()); 
}
