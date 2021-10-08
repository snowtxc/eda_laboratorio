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




//UTILIZA NODO DUMMY;
string InsertarLineaEnPosicion(ListaLinea & L , int posicionLinea){
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
    ListaLinea lista = new nodoLinea;
    lista->sig = NULL;
    lista->sigPalabra = NULL;

     cout << InsertarLineaEnPosicion(lista, 1);
     cout << InsertarLineaEnPosicion(lista,2);
     cout << InsertarLineaEnPosicion(lista,0);
    
  


}
