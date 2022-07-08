#include "Service.h"

void Service::add(int id, string nume, string tip, double pret)
{
	rp.validate_id(id);

	Produs::validate(id, nume, tip, pret);

	auto p = Produs(id, nume, tip, pret);
	rp.add(p);
}

vector<Produs>& Service::get_all_prod()
{
	return rp.getall();
}

int Service::getNumberOfProducts(const string& tip)
{
	return rp.getnumberofproduct(tip);
}


