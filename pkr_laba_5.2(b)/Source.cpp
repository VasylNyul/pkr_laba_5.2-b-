#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> 
#include<fstream>
#include <sstream>
#include <iostream>

using namespace std;

enum Specialty { ��, ��, ��, ��, �� };
string strSpecialty[] = { "��","��","��","��","��" };
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
	cout << "������ ��'� �����:";
	cin.getline(FileName, sizeof(FileName));

	Create(FileName);
	Print(FileName);
	BestMedium(FileName);

	double perc = Percent(FileName);
	cout << "������� ��������, �� ������� �� ������: " << perc << "%" << endl;

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
		cout << "������� " << i + 1 << ":" << endl;
		++i;
		cin.sync();
		cout << "  �������: ";  cin >> s.prizv;
		cout << "  ����: "; cin >> s.kurs;
		do
		{
			cout << " ������������ (0 - ��, 1 - ��, 2 - ��, 3 - ��, 4 - ��): "; cin >> specialty;
		} while (specialty != 0 && specialty != 1 && specialty != 2 && specialty != 3 && specialty != 4);
		s.specialty = (Specialty)specialty;
		cout << "  ������ � ������: "; cin >> s.physic;
		cout << "  ������ � ����������: "; cin >> s.math;
		switch (specialty)
		{
		case 0:
			cout << "  ������ � �������������: "; cin >> s.programing;
			break;
		case 3:
			cout << "  ������ � ��������� ������: "; cin >> s.metods;
			break;
		case 1:
		case 2:
		case 4:
			cout << "  ������ � ���������: "; cin >> s.pedagogika;
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
	cout << "| � | ������� | ���� | ������������ | Գ���� | ���������� | �������������| ������� ������|���������|"
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
	cout << "������� ��������, � ����� ��������� ������� ���: " << prizv1 << endl;

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