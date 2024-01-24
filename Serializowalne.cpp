#include "Serializowalne.h"

std::vector<std::string> odczytajWartosciCSV(std::string liniaRekord) {
	std::istringstream iss(liniaRekord);
	std::string token;
	std::vector<std::string> pola;
	while (std::getline(iss, token, ',')) {
		pola.push_back(token);
	}
	return pola;
}

std::string zapiszWartosciCSV(std::vector<std::string> pola) {
	std::string rekord = "";
	for (unsigned i = 0; i < pola.size(); i++) {
		rekord += pola[i];
		if (i != pola.size() - 1) rekord += ",";
	}
	return rekord;
}

std::string zapiszWektorJakoSCSV(std::vector<std::string> tablica)
{
	std::string rekord = "";
	for (unsigned i = 0; i < tablica.size(); i++) {
		rekord += tablica[i];
		if (i != tablica.size() - 1) rekord += ";";
	}
	return rekord;
}

std::vector<std::string> odczytajWektorJakoSCSV(std::string ciagElementow)
{
	std::istringstream iss(ciagElementow);
	std::string token;
	std::vector<std::string> pola;
	while (std::getline(iss, token, ';')) {
		pola.push_back(token);
	}
	return pola;
}