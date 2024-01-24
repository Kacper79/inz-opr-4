#include "CLI.h"

constexpr auto RozmiarSTDIN = std::numeric_limits<std::streamsize>::max();

CLI::~CLI()
{
	
}

void CLI::WybierzOperacjeUI()
{
	int nrOperacji = -1;
	std::cout << "Operacje do wybrania:\n";
	std::cout << "\t1. Modyfikuj zbiory biblioteczne\n";
	std::cout << "\t2. Wykonaj operacje dla czytelnika\n";
	std::cout << "\t3. Wyjdz z programu\n";
	std::cout << "Twoj wybor: ";
	while (wprowadzZmienna(nrOperacji)) {
		if (nrOperacji == 1) {
			obecnaFunckjaUI = &CLI::ModyfikujZbioryUI;
			break;
		}
		else if (nrOperacji == 2) {
			obecnaFunckjaUI = &CLI::PodajDaneCzytelnikaUI;
			break;
		}
		else if (nrOperacji == 3) {
			exit(0);
		}
		else {
			std::cout << "Bledna opcja, sprobuj ponownie\n";
			return;
		}
	}
}

void CLI::WybierzOperacjeCzytelnikaUI()
{
	SprawdzWiadomosci();
	int oper;
	std::cout << "Wybierz operacje:\n";
	std::cout << "\t1. Sprawdz dostepnosc tytulu\n";
	std::cout << "\t2. Wypozycz egzemplarz ksiazki\n";
	std::cout << "\t3. Zwroc egzemplarz\n";
	std::cout << "\t4. Zakoncz obsluge tego czytelnika\n";
	std::cout << "Twoj wybor: ";
	wprowadzZmienna(oper);
	if (oper == 1) {
		obecnaFunckjaUI = &CLI::SprawdzDostepnoscTytuluUI;
	}
	else if (oper == 2) {
		obecnaFunckjaUI = &CLI::WypozyczEgzemplarzUI;
	}
	else if (oper == 3) {
		obecnaFunckjaUI = &CLI::ZwrocEgzemplarzUI;
	}
	else if (oper == 4) {
		ObecneIDCzytelnika = -1;
		ObecnyCzytelnik = nullptr;
		obecnaFunckjaUI = &CLI::WybierzOperacjeUI;
	}
	else {
		std::cout << "To nie jest prawidlowa opcja, wybierz ponownie: ";
	}
}

void CLI::PodajDaneCzytelnikaUI()
{
	CzyscBuforWejscia();
	std::string iin = "";
	std::cout << "Podaj imie i nazwisko czytelnika oddzielone spacja: ";
	wprowadzTekst(iin);
	while (!sprPoprImINaz(iin)) {
		iin = "";
		std::cout << "To nie jest poprawne imie i nazwisko, podaj ponownie: ";
		CzyscBuforWejscia();
		wprowadzTekst(iin);
	}
	ObecnyCzytelnik = konCzytelnika->SzukajCzytelnikaPoImieniu(iin);
	//CzyscBuforWejscia();
	if (ObecnyCzytelnik == nullptr) {
		char zgoda;
		std::cout << "Nie ma takiego czytelnika, czy stworzyc nowego z tymi danymi (t/n)? ";
		wprowadzZmienna(zgoda);
		if (zgoda == 't') {
			ObecnyCzytelnik = konCzytelnika->StworzNowegoCzytelnika(iin);
		}
		else if (zgoda == 'n') {
			std::cout << "Nieprawidlowy uzytkownik, wracam do menu\n";
			obecnaFunckjaUI = &CLI::WybierzOperacjeUI;
			return;
		}
		else {
			std::cout << "Nie podano decyzji, wracam do menu\n";
			obecnaFunckjaUI = &CLI::WybierzOperacjeUI;
			return;
		}
	}
	ObecneIDCzytelnika = ObecnyCzytelnik->zwrocIDCzytelnika();
	obecnaFunckjaUI = &CLI::WybierzOperacjeCzytelnikaUI;
}

void CLI::ModyfikujZbioryUI()
{
	CzyscBuforWejscia();
	int oper;
	while (true) {
		std::cout << "Wybierz operacje:\n";
		std::cout << "\t1. Dodaj nowy tytul\n";
		std::cout << "\t2. Cenzuruj tytul\n";
		std::cout << "\t3. Zmien liczbe egzemplarzy danego tytulu\n";
		std::cout << "\t4. Wroc do menu\n";
		std::cout << "Twoj wybor: ";
		wprowadzZmienna(oper);
		CzyscBuforWejscia();
		if (oper == 1) {
			std::string tytul;
			std::cout << "Podaj tytul nowej ksiazki: ";
			wprowadzTekst(tytul);
			if (konKsiazek->SzukajKsiazkiPoTytule(tytul) != nullptr) {
				std::cout << "Ta ksiazka juz istnieje\n";
				break;
			}

			std::string autor;
			std::cout << "Podaj autora nowej ksiazki: ";
			wprowadzTekst(autor);
			int liczbaEgz;
			while (true) {
				int liczbEgz;
				std::cout << "Podaj poczatkowa liczbe egzemplarzy tego tytulu dostepna do wypozyczen: ";
				if(wprowadzZmienna(liczbaEgz)) break;
			}
			
			ObecnaKsiazka = konKsiazek->DodajNowaKsiazke(tytul, autor, liczbaEgz);
			ObecneIDKsiazki = ObecnaKsiazka->UzyskajIDKsiazki();
		}
		else if (oper == 2) {
			std::string tytul;
			std::cout << "Podaj tytul usuwanej ksiazki: ";
			wprowadzTekst(tytul);
			ObecnaKsiazka = konKsiazek->SzukajKsiazkiPoTytule(tytul);
			if (ObecnaKsiazka == nullptr) {
				std::cout << "Nie mozna usunac nieistniejacej ksiazki\n";
				break;
			}
			konKsiazek->UsunKsiazke(ObecnaKsiazka->UzyskajIDKsiazki());
			ObecneIDKsiazki = -1;
			ObecnaKsiazka = nullptr;
		}
		else if (oper == 3) {
			std::string tytul;
			std::cout << "Podaj tytul ksiazki: ";
			wprowadzTekst(tytul);
			ObecnaKsiazka = konKsiazek->SzukajKsiazkiPoTytule(tytul);
			if (ObecnaKsiazka == nullptr) {
				std::cout << "Ta ksiazka nie istnieje\n";
				break;
			}

			std::string zmianaKom;
			std::cout << "Zmiana egzemplarzy(obecna ilosc : " << konKsiazek->wszystkieEgzemplarze(ObecnaKsiazka).size() << ")\n";
			std::cout << "\t+N,w gdzie 'N' to liczba nowych egzemplarzy, a 'w' to nr wydania dla wszystkich egzemplarzy\n";
			std::cout << "\t-N gdzie 'N' to ID egzemplarza do usuniecia\n";
			std::cout << "Twoj wybor: ";
			wprowadzTekst(zmianaKom);
			if (zmianaKom.size() > 0 && (zmianaKom[0] == '+' || zmianaKom[0] == '-')) {
				if (zmianaKom[0] == '+') {
					std::istringstream iss(zmianaKom);
					std::string token;
					int ilToken;
					int liczbaEgz = -1;
					int wydanie = 1;
					for (ilToken = 0; std::getline(iss, token, ','); ilToken++) {
						if (ilToken == 0) liczbaEgz = atoi(token.c_str());
						else if (ilToken == 1) wydanie = atoi(token.c_str());
						else break;
					}
					if (ilToken > 2) {
						std::cout << "za duzo wyrazen z przecinkiem\n";
						return;
					}
					for (int i = 0; i < liczbaEgz; i++) {
						int ostatnieEID = ObecnaKsiazka->wszystkieEgzemplarze()[ObecnaKsiazka->wszystkieEgzemplarze().size() - 1].EID;
						konKsiazek->dodajEgzemplarz(ObecnaKsiazka, ostatnieEID + 1, wydanie);
					}
				}
				else {
					for (int i = 1; i < zmianaKom.size(); i++) {
						if (!isdigit(zmianaKom[i])) {
							std::cout << "To nie jest liczba po znaku -";
							return;
						}
					}
					int eid = abs(atoi(zmianaKom.c_str()));
					konKsiazek->usunEgzemplarz(ObecnaKsiazka, eid);
				}
			}
		}
		else if (oper == 4) {
			obecnaFunckjaUI = &CLI::WybierzOperacjeUI;
			break;
		}
		else {
			std::cout << "To nie jest poprawna opcja wybierz ponownie\n";
		}
	}
}

void CLI::WypozyczEgzemplarzUI()
{
	CzyscBuforWejscia();
	std::string tytul;
	std::cout << "Podaj tytul ksiazki: ";
	wprowadzTekst(tytul);
	ObecnaKsiazka = konKsiazek->SzukajKsiazkiPoTytule(tytul);
	if (ObecnaKsiazka == nullptr) {
		std::cout << "Nie ma takiej ksiazki w zbiorach bibliotecznych\n";
		obecnaFunckjaUI = &CLI::WybierzOperacjeCzytelnikaUI;
		return;
	}
	ObecneIDKsiazki = ObecnaKsiazka->UzyskajIDKsiazki();

	int EID = -1;
	std::vector<Egzemplarz> egzempl = ObecnaKsiazka->wszystkieEgzemplarze();
	for (auto it = egzempl.begin(); it != egzempl.end(); ++it) {
		if (it->wypozyczonyPrzez == "") {
			EID = it->EID;
		}
	}
	if (EID == -1) {
		char op;
		std::cout << "Nie mozna wypozyczyc juz wiecej egzemplarzy tej ksiazki\n";
		std::cout << "Czy zapisac cie na liste oczekujacych(t/n)? ";
		wprowadzZmienna(op);
		if (op == 't') {
			ZapiszNaListe();
			obecnaFunckjaUI = &CLI::WybierzOperacjeCzytelnikaUI;
			return;
		}
		else {
			std::cout << "Wracam do menu\n";
			obecnaFunckjaUI = &CLI::WybierzOperacjeCzytelnikaUI;
			return;
		}
	}
	konKsiazek->wypozyczEgzemplarz(ObecnaKsiazka, EID, ObecnyCzytelnik->zwrocImieINazwisko());
	std::cout << "Nr wypozyczonego egzemplarza wynosi " << EID << "\n";
	//czysc komunikaty po wypozyczeniu
	obecnaFunckjaUI = &CLI::WybierzOperacjeCzytelnikaUI;
}

void CLI::ZwrocEgzemplarzUI()
{
	CzyscBuforWejscia();
	std::string tytul;
	std::cout << "Podaj tytul ksiazki: ";
	wprowadzTekst(tytul);
	ObecnaKsiazka = konKsiazek->SzukajKsiazkiPoTytule(tytul);
	if (ObecnaKsiazka == nullptr) {
		std::cout << "Nie ma takiej ksiazki w zbiorach bibliotecznych\n";
		obecnaFunckjaUI = &CLI::WybierzOperacjeCzytelnikaUI;
		return;
	}
	ObecneIDKsiazki = ObecnaKsiazka->UzyskajIDKsiazki();

	int EID;
	std::cout << "Podaj nr egzemplarza zwracanej ksiazki: ";
	if (!wprowadzZmienna(EID)) {
		std::cout << "To nie jest poprawny nr egzemplarza\n";
		return;
	}

	bool czyMozna = false;
	std::vector<Egzemplarz> egzempl = ObecnaKsiazka->wszystkieEgzemplarze();
	for (auto it = egzempl.begin(); it != egzempl.end(); ++it) {
		if (it->wypozyczonyPrzez == ObecnyCzytelnik->zwrocImieINazwisko() && it->EID == EID) {
			czyMozna = true;
		}
	}

	if (!czyMozna) {
		std::cout << "Albo nie istnieje egzemplarz o takim numerze albo ten czytelnik go nie wypozyczyl\n";
		obecnaFunckjaUI = &CLI::WybierzOperacjeCzytelnikaUI;
		return;
	}
	if (ksiazkiObserwowane.find(ObecneIDKsiazki) != ksiazkiObserwowane.end()) {
		ksiazkiObserwowane[ObecneIDKsiazki]->Notify();
	}
	konKsiazek->zwrocEgzemplarz(ObecnaKsiazka, EID);
	obecnaFunckjaUI = &CLI::WybierzOperacjeCzytelnikaUI;
}

void CLI::SprawdzDostepnoscTytuluUI()
{
	CzyscBuforWejscia();
	std::string tytul;
	std::cout << "Podaj nazwe ksiazki: ";
	wprowadzTekst(tytul);
	ObecnaKsiazka = konKsiazek->SzukajKsiazkiPoTytule(tytul);
	if (ObecnaKsiazka == nullptr) {
		std::cout << "Nie ma takiej ksiazki w zbiorach bibliotecznych\n";
		obecnaFunckjaUI = &CLI::WybierzOperacjeCzytelnikaUI;
		return;
	}
	ObecneIDKsiazki = ObecnaKsiazka->UzyskajIDKsiazki();
	std::vector<Egzemplarz> egzempl = ObecnaKsiazka->wszystkieEgzemplarze();
	bool wolnyEgz = false;
	int ilWolnych = 0;
	int eid;
	std::cout << "Biblioteka posiada " << egzempl.size() << " egzemplarze tego tytulu:\n";
	for (auto it = egzempl.begin(); it != egzempl.end(); ++it) {
		if (it->wypozyczonyPrzez == "") {
			if (!wolnyEgz) {
				wolnyEgz = true;
				eid = it->EID;
			}
			ilWolnych++;
		}
		else {
			std::cout << "Egzemplarz nr." << it->EID << " wydanie " << it->nrWydania << ". jest wypozyczone obecnie przez " << it->wypozyczonyPrzez << "\n";
		}
	}
	if (wolnyEgz) {
		std::cout << "Obecnie na stanie sa " << ilWolnych << " wolne egzemplarze\n";
		std::cout << "Nastepny nr egzemplarza do wypozyczenia to " << eid << "\n";
		std::cout << "Wcisnij dowolny przycisk zeby kontynuowac\n";
		CzyscBuforWejscia();
	}
	else {
		char op;
		std::cout << "Nie ma obecnie wolnych egzemplarzy tego tytulu.\n";
		std::cout << "Czy zapisac cie na liste oczekujacych(t/n)? ";
		wprowadzZmienna(op);
		if (op == 't') {
			if (ksiazkiObserwowane.find(ObecneIDKsiazki) == ksiazkiObserwowane.end()) {
				ksiazkiObserwowane[ObecneIDKsiazki] = new Subject(tytul, ObecneIDKsiazki);
			}
			Observer* nowyObs = nullptr;
			for (auto it = obserwatorzy.begin(); it != obserwatorzy.end(); ++it) {
				if ((*(*it)).ZwrocIDCzytelnika() == ObecneIDCzytelnika) {
					nowyObs = *it;
				}
			}
			if (nowyObs == nullptr) {
				nowyObs = new Observer(ObecneIDCzytelnika);
				obserwatorzy.push_back(nowyObs);
			}
			ksiazkiObserwowane[ObecneIDKsiazki]->Subscribe(nowyObs);
		}
		else if(op == 'n') {
			std::cout << "Wracam do menu\n";
		}
		else {
			std::cout << "Nie poprawna opcja, wracam do menu\n";
		}
	}
	
	obecnaFunckjaUI = &CLI::WybierzOperacjeCzytelnikaUI;
}

void CLI::CzyscEkran()
{
	Sleep(1000);
	//CzyscBuforWejscia();
	std::system("cls");
}

void CLI::WykonajFunkcjeUI()
{
	(*this.*obecnaFunckjaUI)();
}

void CLI::CzyscBuforWejscia()
{
	std::cin.clear();
	std::cin.ignore(RozmiarSTDIN, '\n');
}

void CLI::SprawdzWiadomosci()
{
	for (auto it = obserwatorzy.begin(); it != obserwatorzy.end(); ++it) {
		if ((*(*it)).ZwrocIDCzytelnika() == ObecneIDCzytelnika) {
			if ((*(*it)).CheckMessage() != "") {
				std::cout << (*(*it)).CheckMessage();
				(*(*it)).ClearMessage();
			}
		}
	}
}

void CLI::UzupelnijDwojkeObserwatorow()
{
	for (int i = 0; i <= konList->ZwrocLiczbeList(); i++) {
		ListaOczekujacych* lista = konList->SzukajListyPoOID(i);
		if (lista != nullptr) {
			int KID = lista->ZwrocIDKsiazki();
			std::string tytul = konKsiazek->SzukajKsiazkiPoKID(KID)->UzyskajTytul();
			ksiazkiObserwowane[KID] = new Subject(tytul, KID);
			for (int j = 0; j < lista->ZwrocSubskrybentow().size(); j++) {
				int CID = lista->ZwrocSubskrybentow()[j];
				Observer* ob = new Observer(CID);
				obserwatorzy.push_back(ob);
				ksiazkiObserwowane[KID]->Subscribe(ob);
			}
		}
	}
}

void CLI::ZapiszNaListe()
{
	ListaOczekujacych* listaOcz = nullptr;
	if (ksiazkiObserwowane.find(ObecneIDKsiazki) == ksiazkiObserwowane.end()) {
		ksiazkiObserwowane[ObecneIDKsiazki] = new Subject(ObecnaKsiazka->UzyskajTytul(), ObecneIDKsiazki);
		listaOcz = konList->StworzNowaListe(ObecneIDKsiazki);
	}

	//Observer* nowyObs = nullptr;
	/*for (auto it = obserwatorzy.begin(); it != obserwatorzy.end(); ++it) {
		if ((*(*it)).ZwrocIDCzytelnika() == ObecneIDCzytelnika) {
			nowyObs = *it;
		}
	}*/
	//if (nowyObs == nullptr) {
	Observer* nowyObs = new Observer(ObecneIDCzytelnika);
	if (listaOcz == nullptr) {
		listaOcz = konList->SzukajListyPoKID(ObecneIDKsiazki);
	}
	konList->DodajDoListy(listaOcz,ObecneIDCzytelnika);
	obserwatorzy.push_back(nowyObs);
	//}
	ksiazkiObserwowane[ObecneIDKsiazki]->Subscribe(nowyObs);
}

void CLI::WyczyscListe(int KID)
{
	ListaOczekujacych* listaOczekujacych = konList->SzukajListyPoKID(KID);
	if (listaOczekujacych == nullptr) return;
	listaOczekujacych->WyczyscListe();
}
