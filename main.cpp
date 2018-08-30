#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

using namespace std;

class nodo {
private:
    string dato;
    int dentro;
    int fuera;
    nodo *siguiente;

public:

    nodo(string s) { //nodo de strings
        dato = s;
        siguiente = NULL;
    }

    nodo(string v, nodo *signodo) {
        dato = v;
        siguiente = signodo;
    }

    nodo(string s, int pdp, int pfp) { // nodo de prioridades
        dato = s; // formato (simbolo,PDP,PFP)
        dentro = pdp;
        fuera = pfp;
        siguiente = NULL;

    }

    nodo(string s, int pdp, int pfp, nodo *signodo) {
        dato = s;
        dentro = pdp;
        fuera = pfp;
        siguiente = signodo;

    }
    friend class lista;

};

typedef nodo *pnodo; //pnodo = puntero a un nodo

class lista {
private:
    pnodo primero;
    pnodo actual;
    pnodo Cola[5]; //Cola de punteros a nodos}



public:

    lista() {
        primero = actual = NULL;
    }
    void InsertarFinal(string v, int i);
    void Mostrar(int i);
    void lectura(string arch, int i);

    bool ListaVacia() {
        return primero == NULL;
    }
    void InsertarPrio(string v, int pdp, int pfp);
    void cola();
    void InsertarFinalP(int v, int i);
    void MostrarN();
    int BuscarDentro(string operandor);
    int BuscarFuera(string operandor);
    lista crearExpPostFijo();
    bool isOperando(string info);
    void push(string v);
    void pop();
    string verTopePila();
    void evaluarPostFijo(lista postFijo);
    string calculadora(string operando, string num1, string num2);
    lista convertirNumeros(lista postFijo);
    void BorrarFinal();

};


void lista::InsertarFinal(string v, int i) {
    if (ListaVacia())
        Cola[i] = primero = new nodo(v); // enlaza el primer nodo que se crea en el puntero de la cola
    else {
        pnodo aux = primero;
        while (aux->siguiente != NULL)
            aux = aux->siguiente;
        aux->siguiente = new nodo(v);
    }
}

void lista::InsertarPrio(string v, int pdp, int pfp) {
    if (ListaVacia())
        primero = new nodo(v, pdp, pfp);
    else {
        pnodo aux = primero;
        while (aux->siguiente != NULL)
            aux = aux->siguiente;
        aux->siguiente = new nodo(v, pdp, pfp);
    }
}

void lista::push(string dato) {
    if (ListaVacia())
        primero = new nodo(dato);
    else {
        pnodo aux = primero;
        while (aux->siguiente != NULL) {
            aux = aux->siguiente;
        }
        aux->siguiente = new nodo(dato);

    }

}

void lista::Mostrar(int i) {
    nodo *aux;

    aux = Cola[i];
    while (aux) {
        cout << aux->dato << "-> ";
        aux = aux->siguiente;
    }
    cout << endl;
}

void lista::lectura(string arch, int i) {
    ifstream archivo;
    string texto;
    archivo.open(arch);
    if (archivo.fail())
        cout << "Lectura del archivo " << i << " fallida" << endl;
    while (!archivo.eof()) {
        getline(archivo, texto);
        InsertarFinal(texto, i);
        //cout << texto << endl;
    }
    Mostrar(i);
    archivo.close();
}

void lista::MostrarN() {
    nodo *aux;

    aux = primero;
    while (aux) {
        cout << aux->dato << "-> ";
        aux = aux->siguiente;
    }
    cout << endl;
}

int lista::BuscarDentro(string operandor) { //Retorna la prioridad del operador dentro de la pila
    pnodo aux = primero;
    while (aux->siguiente != NULL) {
        if (operandor == aux->dato) {
            int d = aux->dentro;
            return d;
        }
        aux = aux->siguiente;
    }
}

int lista::BuscarFuera(string operandor) { //Retorna la prioridad del operador fuera de la pila
    pnodo aux = primero;
    while (aux != NULL) {
        if (operandor == aux->dato) {
            int f = aux->fuera;
            return f;
        }
        aux = aux->siguiente;
    }
}

void lista::pop() {
    if (primero==NULL){
        cout << "Lista Vacia " << endl;
    }
    if (primero->siguiente == NULL) {
        pnodo temp = primero;

        primero= NULL;
        delete temp;

    }
    else{
    pnodo aux = primero;
    while (aux->siguiente->siguiente != NULL) {
        aux = aux->siguiente;
    }

    pnodo temp = aux->siguiente;
    aux->siguiente = NULL;
    delete temp;
}}


string lista::verTopePila() {
    pnodo aux = primero;

    while (aux->siguiente != NULL) {
        aux = aux->siguiente;
    }
    return aux->dato;
}

lista lista::crearExpPostFijo() {
    lista Prioridades; // una lista auxiliar con la tabla de prioridades
    Prioridades.InsertarPrio("^", 3, 4);
    Prioridades.InsertarPrio("*", 2, 2);
    Prioridades.InsertarPrio("/", 2, 2);
    Prioridades.InsertarPrio("+", 1, 1);
    Prioridades.InsertarPrio("-", 1, 1);
    Prioridades.InsertarPrio("(", 0, 5);

    lista pila; //la pila para los opererandos
    lista expPostFijo; // la pila con el resultado
    pnodo aux = primero;

    while (aux != NULL) { //falta mover el aux
        bool tipoDato = isOperando(aux->dato);
        if (pila.ListaVacia()) { //SI la pila esta vacia empieza a rellenar
            if (tipoDato == false) {
                expPostFijo.push(aux->dato);
                aux = aux->siguiente;
                //expPostFijo.MostrarN();
            } else {
                pila.push(aux->dato);
                aux = aux->siguiente;
            }
        } else { //aqui va toda la magia
            if (tipoDato == false) {
                expPostFijo.push(aux->dato);
                aux = aux->siguiente;
            } else {

                if (aux->dato == ")") {
                    while (pila.verTopePila() != "(") {
                        string p = pila.verTopePila();   //Edite esto para tomar dato que estaba en el tope de la pila
                        pila.pop();   //elimina el dato de la pila, solo eso.
                        expPostFijo.push(p); //aqui ingresa el dato a la expresion postfija
                    } //lo de antes lo hice cada vez que aparecia un pop
                    pila.pop();
                    aux = aux->siguiente;
                } else {
                    string operador = pila.verTopePila();
                    int valorPDP = Prioridades.BuscarDentro(operador);
                    int valorFDP = Prioridades.BuscarFuera(aux->dato);

                    if (valorPDP < valorFDP) {
                        pila.push(aux->dato);
                        aux = aux->siguiente;
                    } else {
                        string operadora = pila.verTopePila();
                        pila.pop();
                        expPostFijo.push(operadora);
                        pila.push(aux->dato);
                        aux = aux->siguiente;
                    }
                }
            }

        }



    }
    /*aca estaba el problema, algunas veces se quedaban operandos
     * en la pila, pero el while saca todo hasta que la pila este vacia
     * y lo va metiendo a la expresion postfijo
     */

    while (!pila.ListaVacia()){
        string q = pila.verTopePila();
        pila.pop();
        expPostFijo.push(q);

    }
    expPostFijo.MostrarN();
    return expPostFijo;




}

bool lista::isOperando(string info) {
    if (info == "+" || info == "-" || info == "/" || info == "*" || info == "^" || info == "(" || info == ")") {
        return true;
    }
    return false;
}

void lista::evaluarPostFijo(lista postFijo) {
    string num1, num2, operador;

    pnodo aux = postFijo.primero;
    num1 = aux->dato; //hay que convertir de string a intiger

    aux = aux->siguiente;
    num2 = aux->dato; //hay que convertir de string a intiger
    aux = aux->siguiente;
    operador = aux->dato;

    num1 = calculadora(operador, num1, num2);

    aux = aux->siguiente;


    while (aux != NULL) { //Aqui hay que revisar con todos los casos no estoy seguro
        num2 = aux->dato;

        aux = aux->siguiente;
        num1 = calculadora(aux->dato, num1, num2);
        aux = aux->siguiente;
    }
    cout << num1 << endl;
}

string lista::calculadora(string operando, string dato1, string dato2) {
    int num1, num2;
    if (istringstream(dato1) >> num1 && istringstream(dato2) >> num2) {

        if (operando == "+") {//suma
            int temp = num1 + num2;
            num1 = temp;
        } else if (operando == "-") {//resta
            int temp = num1 - num2;
            num1 = temp;
        } else if (operando == "/") {//division
            int temp = num1 / num2;
            num1 = temp;
        } else if (operando == "*") {//multiplicacion
            int temp = num1*num2;
            num1 = temp;
        } else if (operando == "^") {//potencia
            int temp = pow(num1, num2);
            num1 = temp;
        }

    }
    stringstream ss;
    ss << num1;
    string str = ss.str();
    return str;
}

int main() {
    lista lista0, lista1, lista2, lista3, lista4, lista5, lista6, lista7, lista8, lista9;
    string file0 = "operaciones.txt";
    string file1 = "operaciones1.txt";
    string file2 = "operaciones2.txt";
    string file3 = "operaciones3.txt";
    string file4 = "operaciones4.txt";

    cout << "=============================" << endl;
    cout << "Lista 0: ";
    lista0.lectura(file0, 0); cout << endl;
    lista5 = lista0.crearExpPostFijo();
    lista5.evaluarPostFijo(lista5);
    cout << "=============================" << endl;
    cout << "Lista 1: ";
    lista1.lectura(file1, 1); cout << endl;
    lista6 = lista1.crearExpPostFijo();
    lista6.evaluarPostFijo(lista6);
    cout << "=============================" << endl;
    cout << "Lista 2: ";
    lista2.lectura(file2, 2); cout << endl;
    lista7 = lista2.crearExpPostFijo();
    lista7.evaluarPostFijo(lista7);
    cout << "=============================" << endl;
    cout << "Lista 3: ";
    lista3.lectura(file3, 3); cout << endl;
    lista8 = lista2.crearExpPostFijo();
    lista8.evaluarPostFijo(lista8);
    cout << "=============================" << endl;
    cout << "Lista 4: ";
    lista4.lectura(file4, 4); cout << endl;
    lista9 = lista4.crearExpPostFijo();
    lista9.evaluarPostFijo(lista9);
