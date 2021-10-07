#include <iostream>

using namespace std;


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



string InsertarLineaEnPosicion(int posicionLinea){
    return "NO IMPLEMENTADA";
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


}
