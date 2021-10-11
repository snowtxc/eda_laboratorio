#include <iostream>

using namespace std;

#define MAX_CANT_PALABRAS  3;
struct nodoPalabra{
    string palabra;
    nodoPalabra * sigPalabra;
};


struct nodoLinea{
    nodoLinea * sig;
    nodoPalabra * sigPalabra;
};

typedef nodoPalabra * ListaPalabra;
typedef nodoLinea * ListaLinea;

ListaLinea L = new nodoLinea;


void inicializarDummy(){
    L->sig = NULL;
    L->sigPalabra = NULL;
}


//Insertar linea al final
string insertar_linea_al_final () {
    ListaLinea newline = new nodoLinea;
    if (L->sig == NULL) {
        newline->sig = NULL;
        newline->sigPalabra = NULL;
        L->sig = newline;
        return "Bien";
    }
    else {
        ListaLinea aux = L;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }  
        newline->sig = NULL;
        newline->sigPalabra = NULL;
        aux->sig = newline;
    }
    return "OK OK";
}

//Insertar nueva linea en posicion n
//UTILIZA NODO DUMMY;
string InsertarLineaEnPosicion(int posicionLinea){
    ListaLinea aux = L;
    int countList = 0;
    while(aux->sig != NULL){
        countList ++;
        aux = aux->sig;
    }
    aux = L;
    if(!(posicionLinea >=1 && posicionLinea <= countList + 1)){  return "ERROR.POSICION INVALIDA";  }

    ListaLinea newLine = new nodoLinea;
    newLine->sigPalabra = NULL;
    for(int i=1; i < posicionLinea; i++){  
        aux = aux->sig; 
    }

    if(aux->sig == NULL){
        newLine->sig = NULL;
        aux->sig = newLine;
    }else{
        newLine->sig = aux->sig;
        aux->sig = newLine;
    }
    return "OK.TODO CORRECTO";
}



int main()
{
    inicializarDummy();

    cout << L->sig;

    cout << insertar_linea_al_final() << endl;
    cout << InsertarLineaEnPosicion(1) << endl;
    cout << InsertarLineaEnPosicion(2) << endl;
    cout << InsertarLineaEnPosicion(0) << endl;
    cout << insertar_linea_al_final() << endl;
    cout << insertar_linea_al_final() << endl;
    cout << InsertarLineaEnPosicion(2) << endl;
}
