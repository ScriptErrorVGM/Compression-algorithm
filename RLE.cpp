// RLE.cpp: ���������� ����� ����� ��� ����������� ����������.
//


#include "stdafx.h"
#include <fstream>
using namespace std;
int _tmain(int argc, _TCHAR* argv[])
{


	ifstream file("Input.txt");
	ofstream file_compr("Compressed.txt");

	char symbol; //������, ������� �� ����� ���������
	int sum = 1;// ���������� ������������� ��������

	while (file.good())
	{
		file.get(symbol);//��������� ������
		if (symbol != file.peek() || sum == 9)// ���� ������ �� ��������� �� ��������� �������� � �����
		{
			file_compr << sum << symbol;
			// ���������� ���������� � �������� ����
			sum = 0;
		}
		sum++;
	}

	file.close();
	file_compr.close();

	ifstream f1("Compressed.txt");
	ofstream file_decompr("Decompressed.txt");

	char symbol1, symbol2;// ���������� � ����������� �������
	const char zero = '0';
	while (f1.peek() != EOF)
	{

		f1.get(symbol1);
		f1.get(symbol2);
		for (int i = 0; i < symbol1 - zero; i++)
			file_decompr << symbol2;
		//if (EOF){ break; }
	}

	f1.close();
	file_decompr.close();

	//system("PAUSE");
	return 0;

}

