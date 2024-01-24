#pragma once
#include <string>
#include <vector>
#include <algorithm>

class Observer;

class Subject {
public:
	Subject(std::string tytul, int KID) : observers(std::vector<Observer*>(0)), KID(KID) {
		message = "Nowe egzemlarze tytulu '" + tytul + "' wlasnie staly sie dostepne!\n";
	}
	void Subscribe(Observer* obs);
	void UnsubscribeAll();
	void Notify();
	int ZwrocIDKsiazki();
private:
	std::vector<Observer*> observers;
	std::string message;
	int KID;
};

class Observer {
public:
	Observer(int CID) : message(""), CID(CID) {}
	void Update(std::string message);
	std::string CheckMessage();
	void ClearMessage();
	int ZwrocIDCzytelnika();
private:
	std::string message;
	int CID;
};

