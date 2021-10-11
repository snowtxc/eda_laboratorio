#include <iostream>

using namespace std;

#define MAX_CANT_PALABRAS  3;

struct nodoPalabra{
    string palabra;
    nodoPalabra * sigPalabra;
};

struct nodoLinea{
    unsigned cant_pal = 0;
    nodoLinea * sig;
    nodoPalabra * sigPalabra;
};

typedef nodoPalabra * ListaPalabra;
typedef nodoLinea * ListaLinea;

ListaLinea L = new nodoLinea;
//ListaLinea L = NULL;

void inicializarDummy(){
    L->sig = NULL;
    L->sigPalabra = NULL;
}

//Insertar linea al final
string insertar_linea_al_final () {
    ListaLinea newline = new nodoLinea;
    newline->sig = NULL;
    newline->sigPalabra = new nodoPalabra;
    newline->sigPalabra->sigPalabra = NULL;
    if (L->sig == NULL) {
        
        L->sig = newline;
        return "Bien";
    }
    else {
        ListaLinea aux = L;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }  
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
    newLine->sigPalabra = new nodoPalabra;
    newLine->sigPalabra->sigPalabra = NULL;
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

//Imprimir texto
void imprimir () {
    int num_linea = 1;
    ListaLinea aux = L;
    while (aux->sig != NULL) {
        cout << num_linea << ":";
        if (aux->sigPalabra != NULL){
            ListaPalabra auxp = aux->sigPalabra;
            while (auxp->sigPalabra != NULL){
                cout << auxp->sigPalabra->palabra << " ";
                auxp = auxp->sigPalabra;
            }
        }
        cout << endl;
        num_linea ++;
        aux = aux->sig;
    }
}

int main()
{
    inicializarDummy();

    insertar_linea_al_final() ;
    InsertarLineaEnPosicion(1);
    InsertarLineaEnPosicion(2) ;
    //InsertarLineaEnPosicion(0) ;
    insertar_linea_al_final() ;
    insertar_linea_al_final() ;
    InsertarLineaEnPosicion(2) ;

    imprimir();
    //cout << L->sig->cant_pal;
}
