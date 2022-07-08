#include "Repo.h"


double to_d(string str) {
    int ip, fp, l;
    ip = fp = 0;
    l = 1;
    bool point = false;
    for (auto ch : str) {
        if (ch == '.') {
            point = true;
        }
        else if ('0' <= ch && ch <= '9') {
            if (!point) {
                ip = ip * 10 + (ch - '0');
            }
            else {
                fp = fp * 10 + (ch - '0');
                l = l * 10;
            }
        }
    }
    return (double)ip + (double)fp / l;
}


int to_nr(string s) {
    int rez = 0;
    int sign = 1;
    if (s[0] == '-') {
        sign = -1;
        s.erase(s.begin());
    }
    for (auto& ch : s) {
        if (!('0' <= ch && ch <= '9')) {
            throw ValidationException("Id-ul trebuie sa fie intreg");
        }
        rez = rez * 10 + (ch - '0');
    }
    return rez * sign;
}


void Repo::save_to_file()
{
    ofstream fout(filename);
    for (auto& produs: p) {
        fout << produs.getid() << " " << produs.getnume() << " " << produs.gettip() << " " << produs.getpret() << "\n";
    }

}

void Repo::load_to_file()
{
    ifstream fin(filename);
    string line;

    while (getline(fin,line))
    {
        if (line.empty()) {
            continue;
        }
        auto ss = stringstream(line);
        vector<string> elems;
        string elem;
        while (getline(ss, elem, ' ')) {
            elems.push_back(elem);
        }
        auto p = Produs(to_nr(elems[0]), elems[1], elems[2], to_d(elems[3]));
        add(p);

    }

}

vector<Produs>& Repo::getall()
{
    return p;
}

void Repo::add(Produs pr)
{

    p.push_back(pr);
    save_to_file();
}

void Repo::validate_id(int id)
{
    bool found = false;
    for (auto& pro : p) {
        if (pro.getid() == id) {
            found = true;
            break;
        }
    }
    if (found) {
        throw DuplicatIdException("NU sunt permise doua produse cu acelasi id");
    }
}

int Repo::getnumberofproduct(const string& tip)
{
    
        int count = 0;
        for (const auto& p : this->getall()) {
            if (p.gettip() == tip)
            {
                count++;
            }
        }
        return count;
    
}
