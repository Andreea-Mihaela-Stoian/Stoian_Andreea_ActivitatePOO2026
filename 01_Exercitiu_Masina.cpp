#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

enum Combustibil { BENZINA = 1, MOTORINA = 2, Electric = 3 };

class Masina {
private:
	const int id;
	string marca;
	Combustibil combustibil;
	int nrRevizii;
	float* costRevizii;
public:
	static int NrMasini;
	// constructor fara parametri
	Masina() :id(++NrMasini) {
		this->marca = "Necunoscuta";
		this->combustibil = BENZINA;
		this->nrRevizii = 0;
		this->costRevizii = nullptr;
	}
	// constructor cu parametri
	Masina(int id, string marca, Combustibil combustibil, int nrRevizii, float* costRevizii) :id(id) {
		
		NrMasini++;
		this->marca = marca;
		this->combustibil = combustibil;
		this->nrRevizii = nrRevizii;
		this->costRevizii = new float[nrRevizii];
		for (int i = 0; i < this->nrRevizii; i++)
		{
			this->costRevizii[i] = costRevizii[i];
		}
	
	}
	// constructor de copiere
	Masina(const Masina& copie) :id(++NrMasini) {
		this->marca = copie.marca;
		this->combustibil = copie.combustibil;
		this->nrRevizii = copie.nrRevizii;
		if (copie.costRevizii != nullptr) {
			this->costRevizii = new float[this->nrRevizii];
			for (int i = 0; i < this->nrRevizii; i++)
			{
				this->costRevizii[i] = copie.costRevizii[i];
			}
		}
		else {
			this->costRevizii = nullptr;
		}
	}
	// operator = de atribuire
	void operator=(const Masina& copie) {
		if (this != &copie) {
			this->marca = copie.marca;
			this->combustibil = copie.combustibil;
			this->nrRevizii = copie.nrRevizii;
			if (this->costRevizii != nullptr) {
				delete[] this->costRevizii;
				this->costRevizii = nullptr;
			}
			if (copie.costRevizii != nullptr) {
				this->costRevizii = new float[this->nrRevizii];
				for (int i = 0; i < this->nrRevizii; i++)
				{
					this->costRevizii[i] = copie.costRevizii[i];
				}
			}
			else {
				this->costRevizii = nullptr;
			}
		}
	}
	// get si set pentru marca
	string getMarca() {
		return this->marca;
	}
	 
	void setMarca(string marcaNoua) {
		if(marcaNoua.length() != 0) {
			this->marca = marcaNoua;
		}
		else {
			throw exception();
		}
	}

	// get si set pt vector dinamic costRevizii
	float* getCostRevizii() {
		return this->costRevizii;
	}

	void setCostRevizii(float* vectorNou, int nrNou) {
		if (this->costRevizii != nullptr) {
			delete[] this->costRevizii;
			this->costRevizii = nullptr;
		}
		this->nrRevizii = nrNou;
		if (vectorNou != nullptr) {
			this->costRevizii = new float[this->nrRevizii];
			for (int i = 0; i < this->nrRevizii; i++)
			{
				this->costRevizii[i] = vectorNou[i];
			}
		}
		else {
			this->costRevizii = nullptr;
		}
	}
	// destructor
	~Masina() {
		if (this->costRevizii != nullptr) {
			delete[] this->costRevizii;
			this->costRevizii = nullptr;
		}
	}

	// operator de indexare [] pt costRevizii
	float& operator[](int index) {
		if (index >= 0 && index < this->nrRevizii) {
			return this->costRevizii[index];
		}
		else {
			throw exception();
		}
	}
	//operator preincrementare ++Masina
	Masina operator++() {
		if (this->nrRevizii > 0)
			this->costRevizii[0] += 50;
		return *this;
	}
	//operator postincrementare Masina++
	Masina operator++(int) {
		Masina copie = *this;
		if (this->nrRevizii++ > 0)
			this->costRevizii[0] += 50;;
		return copie;
	}
	//operator cast la float explict
	explicit operator float() {
		float suma = 0;
		for (int i = 0; i < this->nrRevizii; i++)
		{
			suma += this->costRevizii[i];
		}
		return suma;
	}
	//operator de afisare <<
	friend void operator<<(ostream& out, Masina m) {
		out << endl << "Operator de afisare ";
		out << endl << "Id: " << m.id;
		out << endl << "Marca: " << m.marca;
		out << endl << "Combustibil: ";
		if (m.combustibil == BENZINA) out << "BENZINA";
		if (m.combustibil == MOTORINA) out << "MOTORINA";
		if (m.combustibil == Electric) out << "Electric";
		out << endl << "Nr revizii: " << m.nrRevizii;
		if (m.costRevizii != nullptr) {
			out << endl << "Cost revizii: ";
			for (int i = 0; i < m.nrRevizii - 1; i++) {
				out << m.costRevizii[i] << ", ";
			}
			out << m.costRevizii[m.nrRevizii - 1];
		}
	}
};
// initializare variabila statica
int Masina::NrMasini = 0;

int main() {
	Masina masina1;
	float* costRevizii = new float[3] {100, 200, 300};
	Masina masina2(1, "Dacia", BENZINA, 3, costRevizii);
	Masina masina3 = masina2;

	masina1 = masina2;
	masina1.setMarca("Ford");

	masina2[0] = 150;
	++masina2;
	cout << endl << "Cost total revizii: " << (float)masina2 << " lei" << endl;
	cout << masina2;

	delete[] costRevizii;

	return 0;
}