#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

enum CategorieProdus { ELECTRONICE = 1, IMBRACAMINTE = 2, ALIMENTE = 3 };

class Produs {
private:
	const int codProdus;
	string denumire;
	CategorieProdus categorie;
	int nrRecenzii;
	float* noteRecenzii;
public:
	static int nrProduse;

// constructor fara parametrii
	Produs() : codProdus(++nrProduse) {
		this->denumire = "Produs necunoscut";
		this->categorie = ELECTRONICE;
		this->nrRecenzii = 0;
		this->noteRecenzii = nullptr;
	}
//constuctor cu parametrii
	Produs(int codProdus, string denumire, CategorieProdus categorie, int nrRecenzii, float* noteRecenzii) : codProdus(codProdus) {
		nrProduse++;
		this->denumire = denumire;
		this->categorie = categorie;
		this->nrRecenzii = nrRecenzii;
		this->noteRecenzii = new float[nrRecenzii];
		for (int i = 0; i < this->nrRecenzii; i++)
		{ 
			this->noteRecenzii[i] = noteRecenzii[i];
		}
		delete[] noteRecenzii;
	}
//constructor de copiere
	Produs(const Produs& copie) :codProdus(++nrProduse) {
		this->denumire = copie.denumire;
		this->categorie = copie.categorie;
		this->nrRecenzii = copie.nrRecenzii;

		if (copie.noteRecenzii != nullptr) {
			this->noteRecenzii = new float[nrRecenzii];
			for (int i = 0; i < this->nrRecenzii; i++)
			{
				this->noteRecenzii[i] = copie.noteRecenzii[i];
			}
		}
		else {
			this->noteRecenzii = nullptr;
		}
	}
// operator =
	void operator=(const Produs& copie) {
		this->denumire = copie.denumire;
		this->categorie = copie.categorie;
		this->nrRecenzii = copie.nrRecenzii;

		if (this->noteRecenzii != nullptr) {
			delete[] this->noteRecenzii;
			this->noteRecenzii = nullptr;
		}
		if (copie.noteRecenzii != nullptr) {
			this->noteRecenzii = new float[nrRecenzii];
			for (int i = 0; i < this->nrRecenzii; i++)
			{
				this->noteRecenzii[i] = copie.noteRecenzii[i];
			}
		}
		else {
			this->noteRecenzii = nullptr;
		}
	}
//destructor
	~Produs() {
		cout << endl << "S-a apelat destructorul!";
		if (this->noteRecenzii != nullptr) {
			delete[] this->noteRecenzii;
		}
	}

//operator afisare <<
	friend void operator<<(ostream& out, Produs p) {
		out << endl << "Cod Produs: " << p.codProdus;
		out << endl << "Denumire: " << p.denumire;
		out << endl << "Categorie Produs: ";
		if (p.categorie == ELECTRONICE) out << "ELECTRONICE";
		if (p.categorie == IMBRACAMINTE) out << "IMBRACAMINTE";
		if (p.categorie == ALIMENTE) out << "ALIMENTE";
		out << endl << "Nr Recenzii: " << p.nrRecenzii;
		if(p.noteRecenzii != nullptr && p.nrRecenzii > 0) {
			out << endl << "Note recenzii: ";
			for (int i = 0; i < p.nrRecenzii - 1; i++) {
				out << p.noteRecenzii[i] << ", ";
			}
			out << p.noteRecenzii[p.nrRecenzii - 1];
		}
		out << endl;
	}
// get si set pt atribut simplu denumire
	string getDenumire() {
		return this->denumire;
	}
	void setDenumire(string denumireNoua) {
		if (denumireNoua.length() > 0) {
			this->denumire = denumireNoua;
		}
		else {
			throw exception();
		}

	 }
// get si set pt noteRecenzii - vector dinamic
	// get si set pt noteRecenzii - vector dinamic
	float* getnoteRecenzii() {
		if (this->noteRecenzii != nullptr && this->nrRecenzii > 0) {
			float* vnoteRecenzii = new float[this->nrRecenzii];
			for (int i = 0; i < this->nrRecenzii; i++) {
				vnoteRecenzii[i] = this->noteRecenzii[i];
			}
			return vnoteRecenzii;
		}
		return nullptr;
	}

	void setnoteRecenzii(float* vnoteRecenzii, int dim) {
		if (vnoteRecenzii != nullptr && dim > 0) {
			if (this->noteRecenzii != nullptr) {
				delete[] this->noteRecenzii;
			}
			this->nrRecenzii = dim;
			this->noteRecenzii = new float[this->nrRecenzii];
			for (int i = 0; i < this->nrRecenzii; i++) {
				this->noteRecenzii[i] = vnoteRecenzii[i];
			}
			delete[] vnoteRecenzii;
		}
		else {
			throw exception();
		}
	}
};
int Produs::nrProduse = 0;

void main(){
	// test constructor fara parametrii
	Produs produs1;
	Produs produs3;

	// test constructor cu parametrii
	Produs produs2(4, "Laptop", ELECTRONICE, 2, new float[2] {3, 5});

	//test constructor copiere
	Produs produs4 = produs2;

	//test operator =
	produs3 = produs2;

	cout << "Numar Produse: " << Produs::nrProduse << endl;
	
	// test op afisare
	cout << "\n--- produs1 ---";
	cout << produs1;
	cout << endl;

	cout << "\n--- produs2 ---";
	cout << produs2;
	cout << endl;

	cout << "\n--- produs3 ---";
	cout << produs3;
	cout << endl;

	cout << "\n--- produs4 ---";
	cout << produs4;
	cout << endl;

	// test getteri si setteri
	produs1.setDenumire("Telefon");
	produs1.setnoteRecenzii(new float[3] { 4, 5, 4.5 }, 3);
	cout << "\n--- produs1 modificat (" << produs1.getDenumire() << ") ---";
	cout << produs1;

	float* note = produs1.getnoteRecenzii();
	cout << "\nNote din getter: ";
	for (int i = 0; i < 3; i++) {
		cout << note[i] << " ";
	}
	cout << endl;
	delete[] note;
}