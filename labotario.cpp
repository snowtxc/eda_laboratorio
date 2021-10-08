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

ListaLinea lista = NULL;


//UTILIZO NODO DUMMY;
string InsertarLineaEnPosicion(int posicionLinea){
    ListaLinea aux = lista;
    int countList = 0;
    while(aux->sig != NULL){
        countList ++;
        aux = aux->sig;
    }
    if(!(posicionLinea >=1 && posicionLinea <= countList + 1)){  return "ERROR.POSICION INVALIDA";  }

    ListaLinea newLine = new nodoLinea;
    newLine->sigPalabra = NULL;
    for(int i=1; i < posicionLinea; i++){  aux = aux->sig;   }
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
   ListaLinea nodo1 = new nodoLinea;
   nodo1->sigPalabra = NULL;

   ListaPalabra palabra1 =  new nodoPalabra;
   palabra1->palabra = "Gato";

   nodo1->sigPalabra = palabra1;

   ListaPalabra palabra2 = new nodoPalabra;
   palabra2->palabra = "Perro";
   palabra2->sigPalabra = NULL;

   palabra1->sigPalabra = palabra2;

   cout << MAX_CANT_PALABRAS;
   
}
