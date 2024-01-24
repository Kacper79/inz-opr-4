#include "ListaOczekujacych.h"

ListaOczekujacych::ListaOczekujacych() : Serializowalne(), OID(-1), KID(-1), CIDs(std::vector<int>(0)) {}

ListaOczekujacych::ListaOczekujacych(int OID, int KID) : Serializowalne(),OID(OID),KID(KID), CIDs(std::vector<int>(0)) {}

const int ListaOczekujacych::ZwrocIDListy() const
{
	return OID;
}

const int ListaOczekujacych::ZwrocIDKsiazki() const
{
	return KID;
}

std::vector<int> ListaOczekujacych::ZwrocSubskrybentow() const
{
	return CIDs;
}

void ListaOczekujacych::DodajNaListe(int CID)
{
	CIDs.push_back(CID);
}

void ListaOczekujacych::WyczyscListe()
{
	CIDs.clear();
}
