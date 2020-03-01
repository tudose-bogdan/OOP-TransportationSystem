// Tudose Bogdan Grupa 131 (compilator de pe Visual Studio 2019 C++)
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <string.h>
using namespace std;

class statie
{
protected:
	static int numar_de_statii;
	string strada;
	int nr, sector;
	int cod;
	vector<int> transp;

public:
	statie(string st = "0", int n = 0, int sec = 0) :strada(st), nr(n), sector(sec) {};
	virtual bool tip() = 0;
	int get_cod() { return cod; }
	void adauga_autobuz(int x)
	{
		transp.push_back(x);
	}
	bool contine_autobuz(int cod)
	{
		for (size_t i = 0; i < transp.size(); i++)
			if (transp[i] == cod)
				return 1;
		return 0;

	}

	friend class pctinformare;
};
int statie::numar_de_statii = 0;





class statie_urbana :virtual public statie
{
	bool punct_achizitionare;
public:
	statie_urbana(string st = "0", int n = 0, int sec = 0, bool ach = 0) :statie(st, n, sec)
	{
		cod = ++numar_de_statii;
		punct_achizitionare = ach;
	}

	bool operator==(statie_urbana& a)
	{
		//am suprascris operatorul pentru functia care calculeaza pretul, la fel si pentru cealalta clasa
		bool ok = 0;
		for (size_t i = 0; i < transp.size(); i++)
			for (size_t j = 0; j < a.transp.size(); j++)
				if (transp[i] == a.transp[j])
					return 1;
		return 0;

	}
	bool tip() { return 1; };

	friend ostream& operator<<(ostream& out, statie_urbana *a);

};


class statie_extra :virtual public statie
{
public:
	statie_extra(string st = "0", int n = 0, int sec = 0):statie(st, n, sec)
	{
		cod = ++numar_de_statii;
	}
	bool tip() { return 0; };

	bool operator==(statie_extra& a)
	{
		bool ok = 0;
		for (size_t i = 0; i < transp.size(); i++)
			for (size_t j = 0; j < a.transp.size(); j++)
				if (transp[i] == a.transp[j])
					return 1;
		return 0;

	}

	friend ostream& operator<<(ostream& out, statie_extra* a);
};


class pctinformare
{
	vector<statie*> V;

public:
	void adaugastatie(statie* s)
	{
		V.push_back(s);
	}

	void afiseaza_dupa_autobuz(int cod)
	{
		for (size_t i = 0; i < V.size(); i++)
		{
			if (V[i]->contine_autobuz(cod) == 1)
			{
				statie_urbana* u = dynamic_cast<statie_urbana*>(V[i]);
				if (u)
					cout << u;

				statie_extra* e = dynamic_cast<statie_extra*>(V[i]);
				if (e)
					cout << e;

			}
		}
	}

	void afiseaza_string(string f)
	{
		for (size_t i = 0; i < V.size(); i++)
			if (V[i]->strada == f)
			{
				statie_urbana* u = dynamic_cast<statie_urbana*>(V[i]);
				if (u)
					cout << u;

				statie_extra* e = dynamic_cast<statie_extra*>(V[i]);
				if (e)
					cout << e;
			}
	}
	void afiseaza_int(int x)
	{
		for (int i = 0; i < V.size(); i++)
		{
			if (V[i]->cod == x)
				cout << V[i]->strada << " " << V[i]->sector << "\n";

		}
	}

	double estimeazapret(string a, string b)
	{
		int cod1 = 0, cod2 = 0;
		double pret = 2;
		int procent = 0;

		for (size_t i = 3; i < a.length(); i++)
			cod1 = cod1 * 10 + (a[i] - '0');

		for (size_t i = 3; i < b.length(); i++)
			cod2 = cod2 * 10 + (b[i] - '0');

		statie * s1=NULL, *s2=NULL;
		for (size_t i = 0; i < V.size(); i++)
		{
			if (V[i]->cod == cod1)
				s1 = V[i];
			if (V[i]->cod == cod2)
				s2 = V[i];
	    }
		if (s1 != NULL && s2 != NULL)
		{
			statie_urbana* u1, * u2;
			statie_extra* e1, * e2;
			u1 = dynamic_cast<statie_urbana*>(s1);
			u2 = dynamic_cast<statie_urbana*>(s2);
			e1 = dynamic_cast<statie_extra*>(s1);
			e2 = dynamic_cast<statie_extra*>(s1);
			if (u1 && u2)
			{
				if (u1 == u2)
					return pret;
				else
					procent += 15;
			}
			else
				if (e1 && e2)
				{

					if (e1 == e2)
					{
						return pret;
					}
					else
						procent += 20;

				}
				else
				{
					procent += 35;
				}

			pret += (procent / 100.0) * pret + pret;
			return pret;
		}


	}

	bool is_empty()
	{
		return V.empty();
	}
};
ostream& operator<<(ostream& out, statie_urbana *a)
{
	out << "SU-" << a->cod << "\n";
	return out;
}
ostream& operator<<(ostream& out, statie_extra* a)
{
	out << "SE-" << a->cod << "\n";
	return out;
}
int main()
{

	pctinformare P;

	short int option;

	do
	{
		cout << "1)Adauga statie\n2)Afiseaza detalii folosind nume,adresa,cod\n3)Afisarea tuturor statiilor prin care trece";
		cout << "un autobuz\n4)Afla pret\n5) Exit\n\n";
		try
		{
			cin >> option;
			if (option > 5 || option < 1)
				throw 1;
		}
		catch (int a)
		{
			if (a == 1)
				cout << "\nintorduceti o optiune valida\n";
			cin >> option;
		}
		short int op2;
		switch (option)
		{
		case 1:
		{
			cout << "\n1)Statie urbana\n2)Statie extra urbana\n";
			cin >> op2;
			switch (op2)
			{
			case 1:
			{
				cout << "\nIntroduceti strada, numar, sector si daca se pot achizitiona bilete(1/0)\n";
				string a;
				int b, c;
				int d;
				cin >> a >> b >> c >> d;
				statie_urbana* x = new statie_urbana(a, b, c, d);
				cout << "Cate autobuze doriti sa introduceti?\n";
				int f;
				cin >> f;
				cout << "Introduceti autobuzul/autobuzele\n";
				for (int i = 0; i < f; i++)
				{
					int g;
					cin >> g;
					x->adauga_autobuz(g);
				}
				P.adaugastatie(x);
				break;
			}

			case 2:
			{
				cout << "\n Introduceti strada, numar, sector\n";
				string a;
				int b, c;
				cin >> a >> b >> c;
				statie_extra* x = new statie_extra(a, b, c);
				cout << "Cate autobuze doriti sa introduceti?\n";
				int f;
				cin >> f;
				cout << "Introduceti autobuzul/autobuzele\n";
				for (int i = 0; i < f; i++)
				{
					int g;
					cin >> g;
					x->adauga_autobuz(g);
				}
				P.adaugastatie(x);
				break;
			}
			}
			break;
		}
		case 2:
		{
			short int op3;
			if (P.is_empty())
				cout << "Nu s-au introdus statii inca\n\n";
			else
			{
				cout << "1)Dupa strada\n2)Dupa cod(numeric)\n";
				cin >> op3;
				switch (op3)
				{
				case 1:
				{
					string num;
					cout << "Introduceti strada\n";
					cin >> num;
					P.afiseaza_string(num);
					break;
				}
				case 2:
				{

					int num;
					cout << "Introduceti cod(doar numar)\n";
					cin >> num;
					P.afiseaza_int(num);

					break;
				}
				}
			}
				break;

		}

		case 3:
		{
			if (P.is_empty())
				cout << "Nu s-au introdus statii inca\n\n";
			else
			{
				cout << "Ce mijloc de transport(introduceti cod)\n";
				int f;
				cin >> f;
				cout << "\n";
				P.afiseaza_dupa_autobuz(f);
				cout << "\n";
			}
			break;
		}
		case 4:
		{
			cout << "Introduceti doua coduri de tipul SX-(numar)\n";
			string a, b;
			cin >> a >> b;
			cout << P.estimeazapret(a, b);
			cout << "\n\n";

			break;
		}

		break;
		}

	} while (option != 5);



	return 0;
}
