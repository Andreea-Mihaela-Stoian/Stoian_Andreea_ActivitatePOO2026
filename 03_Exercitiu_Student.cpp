#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

class Student {
private:
	const int NrMatricol;
	string nume;
	int NrNote;
	int* note;
public:
	static int NrStudenti;

// constructor fara parametri
	Student() :NrMatricol(++NrStudenti) {
		this->nume = "Necunoscut";
		this->NrNote = 0;
		this->note = nullptr;
	}
// constructor cu parametri
	Student(int NrMatricol, string nume, int NrNote, int* note) :NrMatricol(NrMatricol) {
		NrStudenti++; 
		this->nume = nume;
		this->NrNote = NrNote;
		this->note = new int[NrNote];
		for (int i=0; i < this->NrNote; i++)
		{
			this->note[i] = note[i];
		}
	}
//destructor
	~Student() {
		if (this->note != nullptr) {
			delete[] this->note;
			this->note = nullptr;
		}
	}
// operator copiere
	Student(const Student& copie) :NrMatricol(++NrStudenti) {
		this->nume = copie.nume;
		this->NrNote = copie.NrNote;
		if (copie.note != nullptr) {
			this->note = new int[this->NrNote];
			for (int i = 0; i < this->NrNote; i++)
			{
				this->note[i] = copie.note[i];
			}
		}
		else {
			this->note = nullptr;
		}
	}
//operator afisare <<
	void friend operator<<(ostream& out, Student s) {
		out << endl << "Nr Matricol: " << s.NrMatricol;
		out << endl << "Nume: " << s.nume;
		out << endl << "Nr Note: " << s.NrNote;
		if (s.note != nullptr && s.NrNote > 0) {
			out << endl << "Note: ";
			for (int i = 0; i < s.NrNote - 1; i++){
				out << s.note[i] << " ";
			}
			out << s.note[s.NrNote - 1];
		}
		out << endl;
	}

};
int Student::NrStudenti = 0;

int main(){
 // 1. Cream obiectele
	Student student1; // cosntructor fara parametri
	int* note = new int[4] { 9, 10, 8, 5};
	Student student2(1, "Popescu Ion", 4, note); // constructor cu parametri
	Student student3 = student2; // constructor de copiere

	cout << "Numar Studenti: " << Student::NrStudenti << endl;
	// 2. Afisam obiectele
	cout << endl << "Student 1 ";
	cout << student1;

	cout << endl << "Student 2 ";
	cout << student2;

	cout << endl << "Student 3 ";
	cout << student3;

	delete[] note; // eliberam memoria alocata pentru vectorul de note
	
	return 0;
}