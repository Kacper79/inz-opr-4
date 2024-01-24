#include "KonList.h"

constexpr NAZWA_TABEL typTabeli = NAZWA_TABEL::OCZEKUJACY;

KontrolerList::KontrolerList(ObslugaIO& oio) : oio(oio)
{
	licznikOID = oio.znajdzNajwyzszeID(typTabeli) + 1;
	stworzoneListy = std::vector<ListaOczekujacych*>(0);
}

KontrolerList::~KontrolerList()
{
	for (unsigned i = 0; i < stworzoneListy.size(); i++) {
		delete stworzoneListy[i];
	}
}

ListaOczekujacych* KontrolerList::StworzNowaListe(int KID)
{
	ListaOczekujacych* nowaLista = new ListaOczekujacych(licznikOID, KID);
	stworzoneListy.push_back(nowaLista);
	std::string nowyRekord = nowaLista->zapisz(nowaLista);
	oio.dodajNowyRekord(typTabeli, nowyRekord, licznikOID);
	licznikOID++;
	return nowaLista;
}

ListaOczekujacych* KontrolerList::SzukajListyPoKID(int KID)
{
	std::string znalezionyRekord = oio.szukajRekorduPoPolu(typTabeli, 1, std::to_string(KID));
	if (znalezionyRekord == "") return nullptr;
	ListaOczekujacych* nowaLista= new ListaOczekujacych();
	nowaLista->odczytaj<ListaOczekujacych>(znalezionyRekord);
	stworzoneListy.push_back(nowaLista);
	return nowaLista;
}

ListaOczekujacych* KontrolerList::SzukajListyPoOID(int OID)
{
	std::string znalezionyRekord = oio.szukajRekordu(typTabeli, OID);
	if (znalezionyRekord == "") return nullptr;
	ListaOczekujacych* nowaLista = new ListaOczekujacych();
	nowaLista->odczytaj<ListaOczekujacych>(znalezionyRekord);
	stworzoneListy.push_back(nowaLista);
	return nowaLista;
}

void KontrolerList::WyczyscListe(ListaOczekujacych*& lista)
{
	lista->WyczyscListe();
	std::string zedytRekord = lista->zapisz(lista);
	oio.edytujRekord(typTabeli, zedytRekord, lista->ZwrocIDListy());
}

void KontrolerList::DodajDoListy(ListaOczekujacych*& lista,int CID)
{
	lista->DodajNaListe(CID);
	std::string zedytRekord = lista->zapisz(lista);
	oio.edytujRekord(typTabeli, zedytRekord, lista->ZwrocIDListy()); 
}

int KontrolerList::ZwrocLiczbeList()
{
	return licznikOID - 1;
}
