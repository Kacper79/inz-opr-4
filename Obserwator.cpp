#include "Obserwator.h"

void Observer::Update(std::string message)
{
	this->message = message;
}

std::string Observer::CheckMessage()
{
	return message;
}

void Observer::ClearMessage()
{
	message = "";
}

int Observer::ZwrocIDCzytelnika()
{
	return CID;
}

void Subject::Subscribe(Observer* obs)
{
	observers.push_back(obs);
}

void Subject::UnsubscribeAll()
{
	for_each(observers.begin(), observers.end(), [](auto& obs) {
		obs->ClearMessage();
	});
	observers.clear();
}

void Subject::Notify()
{
	for (auto it = observers.begin(); it != observers.end(); ++it) {
		(*(*it)).Update(message);
	}
}

int Subject::ZwrocIDKsiazki()
{
	return KID;
}
