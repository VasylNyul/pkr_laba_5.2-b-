#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> 
#include<fstream>
#include <sstream>
#include <iostream>

using namespace std;

enum Specialty { КН, ІТ, ПЗ, ВП, СА };
string strSpecialty[] = { "КН","ІТ","ПЗ","ВП","СА" };
struct Student
{
	char prizv[64];
	Specialty specialty;
	short unsigned kurs;
	short unsigned physic;
	short unsigned math;
	union
	{
		short unsigned programing;
		short unsigned metods;
		short unsigned pedagogika;
	};
};
void Create(char* FileName);
void Print(char* FileName);
void BestMedium(char* FileName);
double Percent(char* FileName);
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char FileName[81];

	cin.get(); cin.sync();
	cout << "Введіть ім'я файлу:";
	cin.getline(FileName, sizeof(FileName));

	Create(FileName);
	Print(FileName);
	BestMedium(FileName);

	double perc = Percent(FileName);
	cout << "Процент студентів, які вчаться на відмінно: " << perc << "%" << endl;

	return 0;
}
void Create(char* FileName)
{
	ofstream f(FileName, ios::binary);
	if (!f)
	{
		cerr << "Error opening file '" << FileName << "'" << endl;
		exit(1);
	}

	Student s;
	int specialty;
	char ch;
	int i = 0;
	do {
		cout << endl;
		cout << "Студент№ " << i + 1 << ":" << endl;
		++i;
		cin.sync();
		cout << "  Прізвище: ";  cin >> s.prizv;
		cout << "  Курс: "; cin >> s.kurs;
		do
		{
			cout << " спеціальність (0 - КН, 1 - ІТ, 2 - ПЗ, 3 - ВП, 4 - СА): "; cin >> specialty;
		} while (specialty != 0 && specialty != 1 && specialty != 2 && specialty != 3 && specialty != 4);
		s.specialty = (Specialty)specialty;
		cout << "  оцінка з фізики: "; cin >> s.physic;
		cout << "  оцінка з математики: "; cin >> s.math;
		switch (specialty)
		{
		case 0:
			cout << "  оцінка з програмування: "; cin >> s.programing;
			break;
		case 3:
			cout << "  оцінка з чисельних методів: "; cin >> s.metods;
			break;
		case 1:
		case 2:
		case 4:
			cout << "  оцінка з педагогіки: "; cin >> s.pedagogika;
			break;
		}


		if (!f.write((char*)&s, sizeof(Student)))
		{
			cerr << "Write error" << endl;
			exit(1);
		}
		cout << "Continue? (Y / N): "; cin >> ch;

	} while (ch == 'Y' || ch == 'y');

}
void Print(char* FileName)
{
	ifstream f(FileName, ios::binary);
	if (!f)
	{
		cerr << "Error opening file" << endl;
		exit(1);
	}
	Student s;
	int i = 0;
	cout << "========================================================================================================================"
		<< endl;
	cout << "| № | Прізвище | Курс | Спеціальність | Фізика | Математика | Програмування| Чисельні методи|Педагогіка|"
		<< endl;
	cout << "-----------------------------------------------------------------------------------------------------------------------";
	while (f.read((char*)&s, sizeof(Student)))
	{
		cout << "| " << setw(2) << right << i + 1 << " "
			<< "| " << setw(13) << left << s.prizv
			<< "| " << setw(3) << right << s.kurs << "  "
			<< "| " << setw(8) << right << strSpecialty[s.specialty] << "      "
			<< "| " << setw(4) << right << s.physic << "   "
			<< "| " << setw(6) << right << s.math << "     ";
			switch (s.specialty)
			{
			case 0:
				cout << "| " << setw(7) << right << s.programing << "       |" << setw(18) << "|" << setw(13) << "|" << endl;
				break;
			case 3:
				cout << "| " << setw(15) << "|" << setw(10) << right << s.metods << "       |" << setw(13) << "|" << endl;
				break;
			case 1:
			case 2:
			case 4:
				cout << "| " << setw(15) << "|" << setw(18) << "|" << right << setw(7) << s.pedagogika << "     |" << endl;
				break;
			}

		++i;
	}
	cout << "==================================================================================================================" << endl;
}

void BestMedium(char* FileName)
{
	ifstream f(FileName, ios::binary);
	if (!f)
	{
		cerr << "Error opening file" << endl;
		exit(1);
	}
	Student s;
	int i = 0;
	string prizv1;
	double best = 0;
	double tmp;
	while (f.read((char*)&s, sizeof(Student)))
	{
		tmp = (s.physic + s.math + s.pedagogika) / 3;

		if (tmp > best)
		{
			prizv1 = s.prizv;
			best = tmp;
		}
		i++;
	}
	cout << "Прізвище студента, у якого найбільший середній бал: " << prizv1 << endl;

}


double Percent(char* FileName)
{
	ifstream f(FileName, ios::binary);
	if (!f)
	{
		cerr << "Error opening file" << endl;
		exit(1);
	}
	Student s;
	int i = 0;
	int k = 0, n = 0;
	while (f.read((char*)&s, sizeof(Student)))
	{
		n++;
		if (s.physic == 5)
			if (s.math == 5)
				if (s.pedagogika == 5)
				{
					k++;

				}
		i++;
	}
	return 100.0 * k / n;
}