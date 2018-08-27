#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;
class nodo{
private:
    string dato;
    nodo *siguiente;

public:
    nodo(string v){
        dato = v;
        siguiente = NULL;
    }
    nodo(string v, nodo *signodo){
        dato = v;
        siguiente =signodo;
    }

friend class lista;

};

typedef nodo *pnodo; //pnodo = puntero a un nodo
class lista{
private:
    pnodo primero;
    pnodo actual;
    pnodo Cola[5];  //Cola de punteros a nodos

public:
    lista(){primero = actual = NULL;}
    void InsertarFinal(string v, int i);
    void Mostrar(int i);
    void lectura(string arch, int i);
    bool ListaVacia() { return primero == NULL; }
    void cola();

};

// El i refiere a la posicion de la cola
void lista::InsertarFinal(string v,int i)   
{
   if (ListaVacia())
     Cola[i] =primero = new nodo(v);     // enlaza el primer nodo que se crea en el puntero de la cola
   else
     { pnodo aux = primero;
        while ( aux->siguiente != NULL)
          aux= aux->siguiente;
        aux->siguiente=new nodo(v);
      }
}

void lista::Mostrar(int i)
{
   nodo *aux;

   aux = Cola[i];   
   while(aux) {
      cout << aux->dato << "-> ";
      aux = aux->siguiente;
   }
   cout << endl;
}

void lista::lectura(string arch, int i){

    ifstream archivo;
    string texto;

    archivo.open(arch);
    if (archivo.fail())
        cout << "Lectura del archivo " << i << " fallida" << endl;
    while (!archivo.eof()){
        getline(archivo,texto);
        InsertarFinal(texto, i);
        //cout << texto << endl;
    }
    Mostrar(i);
    archivo.close();
}



int main()
{   lista lista0, lista1, lista2, lista3, lista4;
    string file0 = "operaciones.txt";  //nombre del archivo
    string file1 = "operaciones1.txt";
    string file2 = "operaciones2.txt";
    string file3 = "operaciones3.txt";
    string file4 = "operaciones4.txt";

    lista0.lectura(file0,0);
    lista1.lectura(file1,1);
    lista2.lectura(file2,2);
    lista3.lectura(file3,3);
    lista4.lectura(file4,4);


}
