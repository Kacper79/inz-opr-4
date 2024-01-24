#include "Czytelnik.h"

Czytelnik::Czytelnik() : Serializowalne(), CID(-1), imieINazwisko("Gosc") {}
Czytelnik::Czytelnik(int CID, std::string imieINazwisko) : Serializowalne(), CID(CID), imieINazwisko(imieINazwisko) {}

const std::string Czytelnik::zwrocImieINazwisko() const
{
	return imieINazwisko;
}

const int Czytelnik::zwrocIDCzytelnika() const
{
	return CID;
}

bool sprPoprImINaz(std::string iin)
{
	std::stringstream iss(iin);
	std::string name;
	int nc = 0;
	while (std::getline(iss, name, ' ')) {
		for (unsigned i = 0; i < name.size(); i++) {
			if (!isalnum(name[i]) || isdigit(name[i])) {
				return false;
			}
		}
		nc++;
	}
	if (nc != 2) return false;
	return true;
}
