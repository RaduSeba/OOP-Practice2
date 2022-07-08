#include "Produse.h"


int Produs::getnrvocale(string nume) const
{
    string s = "aeiouAEIOU";
    int k = 0;
    for (auto& c : nume) {
        if (s.find(c) != -1)
        {
            k++;
        }
    }
    return k;
}

void Produs::validate(int i, string n, string t, double p)
{
    string exc = "";

    if (i < 0) {
        exc += "id nu poate fi negativ";
    }
    if (n == "") {
        exc += "nuemele nu poate fi vid";

    }
    if (t == "") {
        exc += "tipul nu poate fi vid";
    }
    if (p < 0) {
        exc += "pretul nu poate fi negativ";
    }
    if (p < 1.0 || p>100.0) {
        exc += "pretul trebuie sa fie in intervalul 1.0-100";
    }

    if (exc != "") {
        throw ValidationException(exc);
    }
}
