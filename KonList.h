#pragma once
#include "Obserwator.h"
#include "ObslugaIO.h"
#include "ListaOczekujacych.h"

class KontrolerList{
public:
	KontrolerList(ObslugaIO& oio);
	~KontrolerList();

	ListaOczekujacych* StworzNowaListe(int KID);
	ListaOczekujacych* SzukajListyPoKID(int KID);
	ListaOczekujacych* SzukajListyPoOID(int OID);
	void WyczyscListe(ListaOczekujacych*& lista);
	void DodajDoListy(ListaOczekujacych*& lista,int CID);
	
	int ZwrocLiczbeList();
private:
	std::vector<ListaOczekujacych*> stworzoneListy;
	int licznikOID;
	ObslugaIO& oio;
};