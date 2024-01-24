#pragma once
#include <string>
#include <vector>
#include <sstream>

template<typename T>
class Serializowalne {
public:
	template<typename P>
	void odczytaj(std::string zapisWLinii) {
		((T*)this)->odczytaj<P>(zapisWLinii);
	}
	template<typename P>
	std::string zapisz(T* obiektDoZapisania) {
		return ((T*)this)->zapisz<P>(obiektDoZapisania);
	}
};

std::vector<std::string> odczytajWartosciCSV(std::string liniaRekord);
std::string zapiszWartosciCSV(std::vector<std::string> pola);
std::string zapiszWektorJakoSCSV(std::vector<std::string> tablica);
std::vector<std::string> odczytajWektorJakoSCSV(std::string ciagElementow);