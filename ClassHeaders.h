#pragma once

struct Edge
{
    int ws, wk, waga;
};

struct Node
{
    int parent, size;
};

struct LNode
{
    LNode* next;
    int v, weight;
};

class MacierzSasiedztwa
{
public:

    MacierzSasiedztwa(int wierzchołek);
    ~MacierzSasiedztwa();
    void addEdgeM(Edge w);
    int** tabM;
    int waga;
    void printM(int wierzchołek, int krawędz);
};

class ListaSasiedztwa
{
public:
    ListaSasiedztwa(int wierzchołek);
    ~ListaSasiedztwa();
    void addEdgeL(Edge w);
    LNode **tabL;
    int v, weight,waga,usun;
    void printL(int wierzchołek, int krawędz);
    LNode* first(int wierzchołki);
};

class DSU
{
public:
    Node* SingleNode;
    DSU(int w); //konstruktor
    ~DSU(); //destruktor
    void make_set(int w);
    int find_set(int w);
    void union_set(Edge w);
};

class Kolejka
{
public:
    Kolejka(int krawędz);//konstruktor
    ~Kolejka();//destruktor
    void addtokolejka(Edge w);//dodawanie krawedzi
    void removefromkolejka(Edge w);//usuwanie pierwszej krawedzi
    void heapify(int i,Edge w);
    Edge min(); //najmniejszy element
    void showheap(int k);//pokazuje caly kopiec
    Edge* heap;
    int count;//wielkosc kolejki

};

struct l
{
    
    l* next;
    int ws;
    int wk;
    int weight;
};
class Lista
{
public:
    //Edge x; //krawdz, ktora dodajemy
    l* p;
    l* FirstNode;
    
    int counter;
    Lista(int krawędz); //konstruktor
    ~Lista(); //destruktor
   // Lista FirstNode; //wskazuje na pierwszy element
    //Lista* next;//wskazuje na nastepny element
    void addtolist(Edge w); //dodaje krawedz do listy
    void removefromlist(Edge w); //usuwa krawedz z listy
    void sort();
    void split(Lista &t1, Lista &t2);
    void merge(Lista& t1, Lista& t2);
    void show();
    void First();
    Edge min(l*FirstNode);
    
};