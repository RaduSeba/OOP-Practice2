#pragma once

#include "Produse.h"
#include <vector>
#include <fstream>
#include <sstream>


class Repo {

private:
	vector<Produs>p;
	string filename;

	void save_to_file();
	void load_to_file();

public:
	Repo(string f) :filename{ f } {
		load_to_file();

	};

	

	vector<Produs>&getall();

	void add(Produs pr);

	void validate_id(int id);


	int getnumberofproduct(const string& tip);
	

};


class DuplicatIdException {

private:
	string mesaj;

public:
	DuplicatIdException(string mes) :mesaj{ mes } {};
	

	string getmesajid() {
		return mesaj;
	}

	

};


double to_d(string str);
int to_nr(string s);