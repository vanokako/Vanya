// ConsoleApplication7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#define NUMBER 16000
#define BORDER 24
using namespace std;
ofstream fout("res.txt");
void res_func1(int Xmin, int* ans1, int NumRanDat);
void res_func2(int Xmax, int* LeftBorderArray, int* RightBorderArray, int* ans, int NInt);
extern "C"
{
	void func1(int array[], int NumRanDat, int ans1[], int Xmin);
	void func2(int ans1[], int RightBorderArray[], int ans[], int NInt, int Xmin);
}
void generation(int* & ArrNumber, int len, int min, int max)
{
	random_device rd; // класс, кот. описывает результаты ,равномерно распределенные в замкнутом диапазоне [ 0, 2^32).
	mt19937 gen(rd());
	uniform_int_distribution<> distr(min, max); //формирует равномерное распределение целых чисел в заданном интервале
	for (int i = 0; i < len; i++) {
		ArrNumber[i] = distr(gen);
	}
}
int main()
{
	int NumRanDat;
	int* array;
	int *LeftBorderArray, *RightBorderArray;
	int Xmin, Xmax;
	int NInt;
	int MainRange;
	int *ans1;
	int *ans;
	cout << "Enter amount of random numbers: 0 < N <= " << NUMBER << endl;
	cin >> NumRanDat;
	if (NumRanDat >= NUMBER || NumRanDat <= 0)
	{
		cout << "Error" << endl;
		return 0;
	}
	cout << "Enter Xmin: ";
	cin >> Xmin;
	cout << "Enter Xmax: ";
	cin >> Xmax;
	if (Xmin >= Xmax)
	{
		cout << "Error" << endl;
		return 0;
	}
	array = new int[NumRanDat];
	for (int i = 0; i < NumRanDat; ++i)
		array[i] = 0;
	generation(array, NumRanDat, Xmin, Xmax);
	cout << "Enter amount of borders: 0 < NInt <= " << BORDER << endl;
	cin >> NInt;
	if (NInt >= BORDER || NInt <= 0)
	{
		cout << "Error" << endl;
		return 0;
	}
	LeftBorderArray = new int[NInt];
	RightBorderArray = new int[NInt];
	ans = new int[NInt];
	MainRange = Xmax - Xmin + 1;
	ans1 = new int[MainRange];
	for (int i = 0; i < MainRange; ++i)
		ans1[i] = 0;
	cout << "Enter left sides of borders. First bord = " << Xmin << endl;
	LeftBorderArray[0] = Xmin;
	for (int i = 1; i < NInt; i++)
	{
		cout << i + 1 << " border:";
		cin >> LeftBorderArray[i];
		if (LeftBorderArray[i] <= LeftBorderArray[i - 1] || LeftBorderArray[i] > Xmax)
		{
			cout << "Error" << endl;
			return 0;
		}
		RightBorderArray[i - 1] = LeftBorderArray[i] - 1;
	}
	RightBorderArray[NInt - 1] = Xmax;
	func1(array, NumRanDat, ans1, Xmin);
	func2(ans1, RightBorderArray, ans, NInt, Xmin);
	res_func1(Xmin, ans1, MainRange);
	res_func2(Xmax, LeftBorderArray, RightBorderArray, ans, NInt);
	delete[] array;
	delete[] ans;
	delete[] ans1;
	delete[] LeftBorderArray;
	delete[] RightBorderArray;
}

void res_func1(int Xmin, int* ans1, int NumRanDat)
{
	cout << "\n***Intervals of 1 lenght***\n";
	fout << "\n***Intervals of 1 lenght***\n";
	cout << "№\tAmount\n";
	fout << "№\tAmount\n";
	for (int i = 0; i < NumRanDat; i++) {
		cout << Xmin + i << '\t' << ans1[i] << '\n';
		fout << i + 1 << '\t' << Xmin + i << '\t' << ans1[i] << '\n';
	}
}


void res_func2(int Xmax, int* LeftBorderArray, int* RightBorderArray, int* ans, int NInt)
{

	cout << "\n***Specified length intervals***\n";
	fout << "\n***Specified length intervals***\n";
	cout << "№\t[Left; Right board]\tAmount\t\n";
	fout << "№\t[Left; Right board]\tAmount\t\n";
	for (int i = 0; i < NInt; i++)
	{
		cout << i + 1 << "\t" << LeftBorderArray[i] << "\t" << RightBorderArray[i] << "\t\t" << ans[i] << "\n";
		fout << i + 1 << "\t" << LeftBorderArray[i] << "\t" << RightBorderArray[i] << "\t\t" << ans[i] << "\n";
	}
}

