#define _CRT_SECURE_NO_WARNINGS	
#include <iostream>
#include <string>

using namespace std;

enum Gen { FICTIUNE = 1, NONFICTIUNE = 2, SF = 3 };

class Carte {
private:
	const int cod;
	string titlu;
	Gen gen;
	int nrCapitole;
	int* nrPaginiCapitole; // vector dinamic pentru nr pagini capitole
public:
	static int nrCarti;
// constructor fara parametri
	Carte() :cod(++nrCarti) {
		this->titlu = "Fara titlu";
		this->gen = FICTIUNE;
		this->nrCapitole = 0; 
		this->nrPaginiCapitole = nullptr; 
	}
// constructor cu parametri 
	Carte(int cod, string titlu, Gen gen, int nrCapitole, int* nrPaginiCapitole) :cod(cod) {
		nrCarti++;
		this->titlu = titlu;
		this->gen = gen;
		this->nrCapitole = nrCapitole;
		this->nrPaginiCapitole = new int[nrCapitole]; 
		for (int i = 0; i < this->nrCapitole; i++)
		{
			this->nrPaginiCapitole[i] = nrPaginiCapitole[i];
		}
	}
// destructor
	~Carte(){
		if (this->nrPaginiCapitole != nullptr) {
			delete[] this->nrPaginiCapitole;
			this->nrPaginiCapitole = nullptr;
		}
	}
// get si set pt TITLU
	string getTitlu() {
		return this->titlu;
	}

	void setTitlu(string TitluNou) { 
		if (TitluNou.length() != 0) {
			this->titlu = TitluNou;
		}
		else {
			throw exception();
		}
	}
// get si set pt vector dinamic nrPaginiCapitole
	int* getNrPaginiCapitole() {
		return this->nrPaginiCapitole;
	}

	void setNrPaginiCapitole(int* vectorNou, int nrNou) {
		if (this->nrPaginiCapitole != nullptr) {
			delete[] this->nrPaginiCapitole;
			this->nrPaginiCapitole = nullptr;
		}
		this->nrCapitole = nrNou;
		if (vectorNou != nullptr) {
			this->nrPaginiCapitole = new int[this->nrCapitole];
			for (int i = 0; i < this->nrCapitole; i++)
			{
				this->nrPaginiCapitole[i] = vectorNou[i];
			}
		}
		else {
			this->nrPaginiCapitole = nullptr;
		}
	}
// operator de afisare << pt clasa Carte
	friend void operator<<(ostream& out, const Carte& c) {
		out << endl << "Cod: " << c.cod;
		out << endl << "Titlu: " << c.titlu;
		out << endl << "Gen: ";
		if (c.gen == FICTIUNE) out << "FICTIUNE";
		if (c.gen == NONFICTIUNE) out << "NONFICTIUNE";
		if (c.gen == SF) out << "SF";
		out << endl << "Nr capitole: " << c.nrCapitole;
		if (c.nrPaginiCapitole != nullptr) {
			out << endl << "Nr pagini capitole: ";
			for (int i = 0; i < c.nrCapitole - 1; i++) {
				out << c.nrPaginiCapitole[i] << ", ";
			}
			out << c.nrPaginiCapitole[c.nrCapitole - 1];
		}
		out << endl;
	}
};
int Carte::nrCarti = 0;

int main() {
	// 1. Cream obiectele
	Carte carte1; // constructor fara parametri
	int* nrPaginiCapitole = new int[3] {10, 20, 30}; // dam valori pentru vectorul dinamic
	Carte carte2(1, "Povesti", SF, 3, nrPaginiCapitole); // constructor cu parametri
	Carte carte3(2, "Povesti 2", NONFICTIUNE, 3, nrPaginiCapitole); // constructor cu parametri
	cout << "Carti create: " << Carte::nrCarti << endl;

	// 2. Afisam carte1 NESCHIMBATA (valorile din constructorul implicit)
	cout << endl << "--- Carte 1 initiala ---";
	cout << carte1;

	// 3. Afisam celalalte carti create cu constructorul cu parametri
	cout << endl << "--- Carte 2 ---";
	cout << carte2;

	cout << endl << "--- Carte 3 ---";
	cout << carte3;

	// 4. Modificam datele lui carte1 folosind setterii
	carte1.setTitlu("Basme");
	int* paginiNoi = new int[2] {15, 25};
	carte1.setNrPaginiCapitole(paginiNoi, 2);
	delete[] paginiNoi;

	// 5. Afisam carte1 SCHIMBATA (valorile noi setate)
	cout << endl << "--- Carte 1 dupa modificari ---";
	cout << carte1;

	delete[] nrPaginiCapitole; // eliberam memoria alocata in main
	return 0;
	
}

