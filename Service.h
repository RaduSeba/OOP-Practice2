#pragma once
#include "Repo.h"
#include"Observer.h"


class Service:public Observable {

private:
	Repo& rp;

public:

	Service(Repo& r) :rp{ r } {};


	void add(int id, string nume, string tip, double pret);

	vector<Produs>& get_all_prod();

	int getNumberOfProducts(const string& tip);

};