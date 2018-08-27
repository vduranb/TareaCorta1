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
    pnodo Cola[5];

public:
    lista(){primero = actual = NULL;}
    void InsertarFinal(string v);
    void Mostrar();
    void lectura(string arch);
    bool ListaVacia() { return primero == NULL; }

};

void lista::InsertarFinal(string v)
{
   if (ListaVacia())
     primero = new nodo(v);
   else
     { pnodo aux = primero;
        while ( aux->siguiente != NULL)
          aux= aux->siguiente;
        aux->siguiente=new nodo(v);
      }
}

void lista::Mostrar()
{
   nodo *aux;

   aux = primero;
   while(aux) {
      cout << aux->dato << "-> ";
      aux = aux->siguiente;
   }
   cout << endl;
}

void lista::lectura(string arch){

    ifstream archivo;
    string texto;

    archivo.open(arch);

    while (!archivo.eof()){  //mientras el archivo no acabe
        getline(archivo,texto);
        InsertarFinal(texto);
        Mostrar();
        cout << texto << endl;
    }
    archivo.close();
}

int main()
{   lista lista0, lista1, lista2, lista3, lista4;  //una lista para cada archivo
    string file0 = "operaciones.txt";              //nombre del archivo
    lista0.lectura(file0);

}
