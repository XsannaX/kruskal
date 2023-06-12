#include "ClassHeaders.h"
#include <iostream>
#include <iomanip>
#include<fstream>
#include<sstream>

using namespace std;

//Lista s¹siedztwa
ListaSasiedztwa::ListaSasiedztwa(int wierzcho³ek)
{
    tabL = new LNode * [wierzcho³ek];
    for (int i = 0;i < wierzcho³ek;i++)
    {
        tabL[i] = NULL;
    }
    int waga=0;
    int usun = wierzcho³ek - 1;
}
ListaSasiedztwa::~ListaSasiedztwa()
{
    LNode* p;
    LNode* r;
    for (int i = 0;i < usun;i++)
    {
        p = tabL[i];
        while (p)
        {
            r = p;
            p = p->next;
            delete r;
        }
    }
    delete[] tabL;
}

void ListaSasiedztwa::addEdgeL(Edge w)
{
    LNode* p;
    p = new LNode;
    p->v = w.wk;
    p->weight = w.waga;
    p->next = tabL[w.ws];
    tabL[w.ws] = p;
    waga = waga + p->weight;


    //graf nieskierowany
    p = new LNode;
    p->v = w.ws;
    p->weight = w.waga;
    p->next = tabL[w.wk];
    tabL[w.wk] = p;
}
LNode* ListaSasiedztwa::first(int wierzcho³ki)
{
    return tabL[wierzcho³ki];
}
void ListaSasiedztwa::printL(int wierzcho³ek,int krawêdz)
{
    LNode* p;
    /*int n = 0;
    cout << endl << "Lista sasiedztwa" << endl;
    cout << wierzcho³ek << " " << krawêdz << endl;
    for (int i = 0;i<wierzcho³ek; i++)
    {
        p = tabL[i];
        while (p)
        {
            cout << "L[" << n << "]->" << i << " " << p->v << " " << p->weight;
            p = p->next;
            n++;
            cout << endl;
        }
    }*/
    
    for (int i = 0;i < wierzcho³ek; i++)
    {

        cout << "Wierzcholek[" << i << "]= ";
        for (p = tabL[i];p;p = p->next)
        {
            cout << p->v << " " << p->weight << " | ";
        }
        cout << endl;
    }

    cout << "waga to " << waga;
}

//Macierz s¹siedztwa
MacierzSasiedztwa::MacierzSasiedztwa(int wierzcho³ek)
{
    tabM = new int* [wierzcho³ek];

    for (int i = 0; i < wierzcho³ek; i++)
    {
        tabM[i] = new int[wierzcho³ek];
    }

    for (int i = 0; i < wierzcho³ek;i++)
    {
        for (int j = 0; j < wierzcho³ek;j++)
        {
            tabM[i][j] = 0;
        }
    }
}
MacierzSasiedztwa::~MacierzSasiedztwa()
{
    delete[] tabM;
}
void MacierzSasiedztwa::addEdgeM(Edge w)
{
    tabM[w.ws][w.wk] = w.waga; 
    waga = waga + w.waga;

    //dla grafu nie skierowanego
    tabM[w.wk][w.ws] = w.waga;

}
void MacierzSasiedztwa::printM(int wierzcho³ek, int krawêdz)
{
    cout << "Macierz sasiedztwa" << endl;
    for (int k = 0;k < wierzcho³ek;k++)
    {
        if (k == 0) cout << "  ";
        cout << k << " ";
    }
    for (int i = 0; i < wierzcho³ek;i++)
    {
        cout << endl;
        for (int j = 0; j < wierzcho³ek;j++)
        {
            if (j == 0) cout << i << " ";
            cout << tabM[i][j] << " ";
        }
    }cout << endl;
    cout << "waga " << waga;
}

//algorytm kruskala
DSU::DSU(int w)
{
    SingleNode = new Node[w];
}

DSU::~DSU()
{
    delete[] SingleNode;
}

void DSU::make_set(int w)
{
    //SingleNode->parent = w;
    //SingleNode->size = 1;

    SingleNode[w].parent = w;
    SingleNode[w].size = 1;
}
int DSU::find_set(int w)
{
    /*if (w == SingleNode->parent)
    {
        return w;
    }
    return SingleNode->parent = find_set(SingleNode->parent);*/
   
    if (w!=SingleNode[w].parent)
    {
        SingleNode[w].parent = find_set(SingleNode[w].parent);
    }
    return SingleNode[w].parent;
}

void DSU::union_set(Edge w)
{
    int temp;
    int a = find_set(w.ws);
    int b = find_set(w.wk);
    if (a != b)
    {
        if (SingleNode[a].size < SingleNode[b].size)
        {
            
            a = find_set(w.wk);
            b = find_set(w.ws);
            

        }
        SingleNode[b].parent = a;
        SingleNode[a].size += SingleNode[b].size;
    }
}

//struktura lista jednokierunkowa
Lista::Lista(int krawêdz)
{
    l*FirstNode = NULL;
    counter = 0;
}
Lista::~Lista()
{
   l* temp;
    while (FirstNode != NULL)
    {
        
        temp = FirstNode;
        FirstNode = FirstNode->next;
        delete temp;
    }
    delete FirstNode;
}
void Lista::addtolist(Edge w)
{
    l* p = new l;
    p->ws = w.ws;
    p->wk = w.wk;
    p->weight = w.waga;
    if (FirstNode == NULL) { p->next = NULL;FirstNode =p;  }
    else
    {
        //dodanie na koniec
        /*l* temp =FirstNode;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = p;
        p->next = NULL;*/

        //dodanie na poczatek
        p->next = FirstNode;
        FirstNode = p;
    }
    counter++;
    
    
}
void Lista::First()
{
    cout << FirstNode->ws << " "<< FirstNode->wk << " " << FirstNode->weight<<endl;
}
void Lista::removefromlist(Edge w)
{
    l* temp = FirstNode;
    FirstNode = temp->next;
    delete temp;
}
void Lista::split(Lista &t1, Lista &t2)
{
    l* current=FirstNode->next;
    l* temp1=FirstNode, * temp2=current;
    bool b = true;
    int licznik = 0;
    Edge w;
    while (FirstNode&&current)
    {
        if (b)
        {temp1 = FirstNode;
            w.ws = temp1->ws;
            w.wk = temp1->wk;
            w.waga = temp1->weight;
            t1.addtolist(w);
            licznik++;
            temp1 = temp1->next;
            FirstNode = current->next;
        }
        else
        {temp2 = current;
            w.ws = temp2->ws;
            w.wk = temp2->wk;
            w.waga = temp2->weight;
            t2.addtolist(w);
            licznik++;
            temp2 = temp2->next;
            current = FirstNode->next;
        }
        b = !b;
   }
    if (licznik % 2 == 0)
    {
        temp1 = FirstNode;
        w.ws = temp1->ws;
        w.wk = temp1->wk;
        w.waga = temp1->weight;
        t1.addtolist(w);
    }
    else
    {
        temp2 = current;
        w.ws = temp2->ws;
        w.wk = temp2->wk;
        w.waga = temp2->weight;
        t2.addtolist(w);
       
    } temp1->next = temp2->next = NULL;

   
}
void Lista::merge(Lista& t1, Lista& t2)
{
    l* s;
    Edge w;
    w.ws = 0;
    w.wk = 0;
    w.waga = 0;
    addtolist(w);
    s = FirstNode;

    while (t1.FirstNode && t2.FirstNode)
    {
        if (t1.FirstNode->weight <= t2.FirstNode->weight)
        {
            s->next = t1.FirstNode;
            t1.FirstNode = t1.FirstNode->next;
        }
        else
        {
            s->next = t2.FirstNode;
            t2.FirstNode = t2.FirstNode->next;
        }
        s = s->next;
    }
    while (t1.FirstNode)
    {
        s->next = t1.FirstNode;
        t1.FirstNode = t1.FirstNode->next;
        s = s->next;
    }
    while (t2.FirstNode)
    {
        s->next = t2.FirstNode;
        t2.FirstNode = t2.FirstNode->next;
        s = s->next;
    }
    removefromlist(w);
}
void Lista::sort()
{
    Lista t1(counter) ;Lista t2(counter);
    if (FirstNode != NULL && FirstNode->next != NULL)
    {
        split(t1, t2);
        t1.sort();
        t2.sort();
        merge(t1, t2);
    }
}
Edge Lista::min(l*FirstNode)
{
    Edge w;
    w.ws = FirstNode->ws;
    w.wk = FirstNode->wk;
    w.waga = FirstNode->weight;
    //cout <<"min"<< w.ws << " " << w.wk << " " << w.waga << endl;
    return w;
}
void Lista::show()
{
    int number = 0;
    l* temp = FirstNode;
    while (temp != NULL)
    {
        cout << temp->ws << " " << temp->wk << " " << temp->weight << endl;
        temp = temp->next;
        number += 1;
    }
    delete temp;
}

//struktura kolejka priorytetowa na kopcu

Kolejka::Kolejka(int krawêdz)
{
     heap = new Edge[krawêdz];
     count = 0;
}
Kolejka::~Kolejka()
{
    delete[] heap;
}
Edge Kolejka::min()
{
    //cout <<"min "<< heap->ws << " " << heap->wk << " " << heap->waga << endl;
    return heap[0];
}
int parent(int i)
{
   
    return ((i-1)/2 );
}
void Kolejka::heapify(int i,Edge w)
{
    while (i != 0 && heap[parent(i)].waga > heap[i].waga) {

       
        Edge temp;
        (temp) = heap[i];
        heap[i] = heap[parent(i)];
        heap[parent(i)] = temp;
        i = parent(i);
    }
    heap[i] = w;

    
    
}
void Kolejka::addtokolejka(Edge w)
{ 
    count++;
    int i = count-1 ;
    heap[i] = w;
    heapify(i,w);
    /*for (int i = 0;i < count;i++)
        {
            cout << i << " " << heap[i].ws << " " << heap[i].wk << " " << heap[i].waga << endl;
        }
        cout << "to jest count " << count << endl;*/
    
}
void Kolejka::removefromkolejka(Edge w)
{
    if (count)
    {
        w = heap[--count];

        int i = 0;
        int j = 1;

        while (j < count)
        {
            if ((j + 1 < count) && (heap[j + 1].waga < heap[j].waga)) j++;
            if (w.waga <= heap[j].waga) break;
            heap[i] = heap[j];
            i = j;
            j = j *2 + 1;
        }
        heap[i] = w;
    }
    
}

void Kolejka::showheap(int krawêdz)
{
    for (int i = 0;i < count;i++)
    {
        cout << heap[i].ws << " " << heap[i].wk << " " << heap[i].waga << " " << endl;
    }
}