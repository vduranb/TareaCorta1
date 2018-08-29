#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;
class nodo{
private:
    string dato;
    int dentro;
    int fuera;
    nodo *siguiente;

public:
    nodo(string s){  //nodo de strings
        dato = s;
        siguiente = NULL;
    }
    nodo(string v, nodo *signodo){
        dato = v;
        siguiente =signodo;
    }
    nodo(string s, int pdp, int pfp){  // nodo de prioridades
        dato = s;                      // formato (simbolo,PDP,PFP)
        dentro = pdp;
        fuera = pfp;
        siguiente = NULL;

    }
    nodo(string s, int pdp, int pfp, nodo *signodo){
        dato = s;
        dentro = pdp;
        fuera = pfp;
        siguiente = signodo;

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
    void InsertarPrio(string v, int pdp, int pfp);
    void cola();
    void InsertarFinalP(int v, int i);
    void MostrarN();
    int BuscarDentro(string operandor);
    int BuscarFuera(string operandor);

};

//void lista::InsertarFinalP(int v, int i)
//{
  //  if (ListaVacia())
    //    primero = new nodo(v);
   // else{
     //   pnodo aux = primero;
       // while ( aux->siguiente != NULL)
         //   aux= aux->siguiente;
           // aux->siguiente=new nodo(v);
     // }
//}


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

void lista::InsertarPrio(string v, int pdp, int pfp)
{
    if (ListaVacia())
        primero = new nodo(v,pdp,pfp);
    else
    { pnodo aux = primero;
        while ( aux->siguiente != NULL)
            aux= aux->siguiente;
        aux->siguiente=new nodo(v,pdp,pfp);
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

void lista::MostrarN()
{
   nodo *aux;

   aux = primero;
   while(aux) {
      cout << aux->dato << "-> ";
      aux = aux->siguiente;
   }
   cout << endl;
}

int lista::BuscarDentro(string operandor){
    pnodo aux = primero;
    while(aux!=NULL){
        if (operandor==aux->dato) {
            int d =aux->dentro;
            return d;
        }aux=aux->siguiente;
    }
}

int lista::BuscarFuera(string operandor){
    pnodo aux = primero;
    while(aux!=NULL){
        if (operandor==aux->dato) {
            int f =aux->fuera;
            return f;
        }aux=aux->siguiente;
    }
}




int main()
{   lista lista0, lista1, lista2, lista3, lista4;
    string file0 = "operaciones.txt";
    string file1 = "operaciones1.txt";
    string file2 = "operaciones2.txt";
    string file3 = "operaciones3.txt";
    string file4 = "operaciones4.txt";

    lista0.lectura(file0,0);
    lista1.lectura(file1,1);
    lista2.lectura(file2,2);
    lista3.lectura(file3,3);
    lista4.lectura(file4,4);


    lista Prioridades;
    Prioridades.InsertarPrio("^",3,4);
    Prioridades.InsertarPrio("*",2,2);
    Prioridades.InsertarPrio("/",2,2);
    Prioridades.InsertarPrio("+",1,1);
    Prioridades.InsertarPrio("-",1,1);
    Prioridades.InsertarPrio("(",0,5);
    Prioridades.MostrarN();
    
    
    //Prueba
    int a = Prioridades.BuscarDentro("^");
    int b = Prioridades.BuscarFuera("^");

    cout << a << endl;
    cout << b << endl;


    //lista Pila;
    //lista ExpresionPosfija;





}
