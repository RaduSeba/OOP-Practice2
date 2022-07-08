#pragma once

#include <iostream>
#include <string>

using namespace std;


class Produs {

private:
	int id;
	string nume;
	string tip;
	double pret;

public:

	Produs(int i, string n, string t, double p) :id{ i }, nume{ n }, tip{ t }, pret{ p }{};


	int getid() const {
		return id;
	}

	string getnume() const{
		return nume;
	}
	string gettip() const{
		return tip;
	}
	double getpret() const{
		return pret;
	}

	int getnrvocale(string nume) const;

	 static void validate(int i, string n, string t, double p);

};

class ValidationException {

private:
	string message;

public:
	
	ValidationException(string m) :message{ m } {};

	string getMesaj() {
		return message;
	}

};