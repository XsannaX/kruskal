#include "ClassHeaders.h"
#include <iostream>
#include <iomanip>
#include<fstream>
#include<sstream>
#include<chrono>
using namespace std;


void reset(ifstream& plik2)
{
	cout << endl;
	system("pause");
	system("cls");
	plik2.clear();
	plik2.seekg(0, ios::beg);
}




int main()
{
	//do wczytywania plików
	string plik_name = ("C:/Users/Lenovo/Desktop/grafM.txt");
	string plik_name2 = ("C:/Users/Lenovo/Desktop/grafL.txt");
	ifstream plik(plik_name);
	ifstream plik2(plik_name2);
	//do testów
	int number = 1;
	auto time = 0.0, time1 = 0.0, time2 = 0.0, time3 = 0.0;

	//for (int i = 0;i < number;i++) {   

		//ogolnie potrzebne
	int wierzcho³ek, krawêdz;
	Edge w, y, x, z;


	//opcja 1: Lista sasiedztwa i kolejka priorytetowa
	plik2 >> wierzcho³ek >> krawêdz;
	cout << "Lista sasiedztwa i kolejka priorytetowa dla " << wierzcho³ek << " wierzcholkow i " << krawêdz << " krawedzi" << endl;

	//tworzenie struktur i grafow
	DSU D(wierzcho³ek), D1(wierzcho³ek), D2(wierzcho³ek), D3(wierzcho³ek);
	ListaSasiedztwa lista(wierzcho³ek), lista1(wierzcho³ek);
	MacierzSasiedztwa macierz(wierzcho³ek), macierz1(wierzcho³ek);
	Lista l(wierzcho³ek), l1(wierzcho³ek);
	Kolejka k(krawêdz), k1(krawêdz);

	auto duration_start = chrono::high_resolution_clock::now();
	for (int i = 0;i < wierzcho³ek;i++)
	{
		D.make_set(i);
	}
	for (int i = 0;i < krawêdz;i++)
	{
		plik2 >> w.ws >> w.wk >> w.waga;
		k.addtokolejka(w);
	}
	for (int i = 1;i < wierzcho³ek;i++)
	{
		do {
			w = k.min();
			k.removefromkolejka(w);
		} while (D.find_set(w.ws) == D.find_set(w.wk));
		/*w = k.min();
		k.removefromkolejka(w);
		while (D.find_set(w.ws) == D.find_set(w.wk))
		{
			w = k.min();
			k.removefromkolejka(w);
		}*/
		lista.addEdgeL(w);
		D.union_set(w);

	}
	auto duration_end = chrono::high_resolution_clock::now();
	auto duration = chrono::duration<double, ::milli>(duration_end - duration_start).count();
	cout << "Czas trwania sortowania: " << duration << endl;
	time = time + duration;
	lista.printL(wierzcho³ek, krawêdz);
	reset(plik2);



	//opcja 2: macierz sasiedztwa i kolejka
	plik2 >> wierzcho³ek >> krawêdz;
	cout << "Macierz sasiedztwa i kolejka priorytetowa dla " << wierzcho³ek << " wierzcholkow i " << krawêdz << " krawedzi" << endl;
	auto duration_start1 = chrono::high_resolution_clock::now();
	for (int i = 0;i < wierzcho³ek;i++)
	{
		D1.make_set(i);
	}
	for (int i = 0;i < krawêdz;i++)
	{
		plik2 >> y.ws >> y.wk >> y.waga;
		k1.addtokolejka(y);
	}
	for (int i = 1;i < wierzcho³ek;i++)
	{
		do {
			y = k1.min();
			k1.removefromkolejka(y);
		} while (D1.find_set(y.ws) == D1.find_set(y.wk));
		/*y = k1.min();
		k1.removefromkolejka(y);
		while (D1.find_set(y.ws) == D1.find_set(y.wk))
		{
			y = k1.min();
			k1.removefromkolejka(y);
		}*/
		macierz.addEdgeM(y);
		D1.union_set(y);
	}
	auto duration_end1 = chrono::high_resolution_clock::now();
	auto duration1 = chrono::duration<double, ::milli>(duration_end1 - duration_start1).count();
	time1 += duration1;
	cout << "Czas trwania sortowania: " << duration1 << endl;
	macierz.printM(wierzcho³ek, krawêdz);
	reset(plik2);


	//opcja 3: lista sasiedztwa i lista
	plik2 >> wierzcho³ek;
	plik2 >> krawêdz;
	cout << "Lista sasiedztwa i lista z sortowaniem merge dla " << wierzcho³ek << " wierzcholkow i " << krawêdz << " krawedzi" << endl;
	auto duration_start2 = chrono::high_resolution_clock::now();
	for (int i = 0;i < wierzcho³ek;i++)
	{
		D2.make_set(i);
	}
	for (int i = 0;i < krawêdz;i++)
	{
		plik2 >> x.ws >> x.wk >> x.waga;
		l.addtolist(x);
	}
	l.sort();
	for (int i = 1;i < wierzcho³ek;i++)
	{
		do {
			x = l.min(l.FirstNode);
			l.removefromlist(x);
		} while (D2.find_set(x.ws) == D2.find_set(x.wk));

		/*x = l.min(l.FirstNode);
		l.removefromlist(x);
		while (D2.find_set(x.ws) == D2.find_set(x.wk))
		{
			x = l.min(l.FirstNode);
			l.removefromlist(x);
		}*/
		lista1.addEdgeL(x);
		D2.union_set(x);
	}
	auto duration_end2 = chrono::high_resolution_clock::now();
	auto duration2 = chrono::duration<double, ::milli>(duration_end2 - duration_start2).count();
	time2 += duration2;
	cout << "Czas trwania sortowania: " << duration2 << endl;
	//l.show();
	lista1.printL(wierzcho³ek, krawêdz);
	reset(plik2);


	//opcja 4: Macierz sasiedztwa i lista
	plik2 >> wierzcho³ek;
	plik2 >> krawêdz;
	cout << "Macierz sasiedztwa i lista z sortowaniem merge dla " << wierzcho³ek << " wierzcholkow i " << krawêdz << " krawedzi" << endl;
	auto duration_start3 = chrono::high_resolution_clock::now();
	for (int i = 0;i < wierzcho³ek;i++)
	{
		D3.make_set(i);
	}
	for (int i = 0;i < krawêdz;i++)
	{
		plik2 >> z.ws >> z.wk >> z.waga;
		l1.addtolist(z);
	}
	l1.sort();
	for (int i = 1;i < wierzcho³ek;i++)
	{
		do {
			z = l1.min(l1.FirstNode);
			l1.removefromlist(z);
		} while (D3.find_set(z.ws) == D3.find_set(z.wk));

		/*z = l1.min(l1.FirstNode);
		l1.removefromlist(z);
		while (D3.find_set(z.ws) == D3.find_set(z.wk))
		{
			z = l1.min(l1.FirstNode);
			l1.removefromlist(z);
		}*/
		macierz1.addEdgeM(z);
		D3.union_set(z);

	}
	auto duration_end3 = chrono::high_resolution_clock::now();
	auto duration3 = chrono::duration<double, ::milli>(duration_end3 - duration_start3).count();
	time3 += duration3;
	cout << "Czas trwania sortowania: " << duration3 << endl;
	macierz1.printM(wierzcho³ek, krawêdz);
	reset(plik2);

	//}

	plik2.close();
	cout << "podsumowanie" << endl;
	time = time / number;
	time1 = time1 / number;
	time2 = time2 / number;
	time3 = time3 / number;
	cout << "Lista sasiedztwa i kolejka priorytetowa" << time << endl << "Macierz sasiedztwa i kolejka priorytetowa" << time1 << endl << "Lista sasiedztwa i lista z sortowaniem" << time2 << endl << "Macierz sasiedztwa i lista" << time3;
	cout << endl;

}

