#include <iostream>

using namespace std;

const int MAX_CANT_PALABRAS =  3;

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
    L->cant_pal = 0;
    L->sig = NULL;
    L->sigPalabra = NULL;
}



int getCantNodoLinea(){
    ListaLinea aux = L;
    int countList = 0;
    while (aux->sig != NULL)
    {
        countList++;
        aux = aux->sig;
    }
    return countList;
}

int getCantNodoPalabra(ListaPalabra lp){
     int cantPal = 0;
     while (lp->sigPalabra != NULL){
        cantPal++;
        lp = lp->sigPalabra;
     }

     return cantPal;
     
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
    if(!(posicionLinea >=1 && posicionLinea <= getCantNodoLinea() + 1)){  return "ERROR.POSICION INVALIDA";  }

    ListaLinea aux = L;

    ListaLinea newLine = new nodoLinea;
    newLine->sigPalabra = new nodoPalabra;
    newLine->sigPalabra->sigPalabra = NULL;
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


//SIN TERMINAR
string InsertarPalabra(int posicionLinea, int posicionPalabra, string PALABRA){
    if(L->sig == NULL){ return "ERROR POSICION DE LINEA INVALIDA"; }

    if (!(posicionLinea >= 1 && posicionLinea <= getCantNodoLinea() ))
    {
        return "ERROR.POSICION INVALIDA";
    }
 
    ListaLinea aux = L;

    for (int i = 1; i <= posicionLinea   ; i++)
    {   
        aux = aux->sig;
    }
    cout << aux->cant_pal;
    ListaPalabra auxlp = aux->sigPalabra;  //NODO DUMMY
    int cantPal = getCantNodoPalabra(auxlp);

    if(cantPal < MAX_CANT_PALABRAS){
        if (!(posicionPalabra >= 1 && posicionPalabra <= cantPal + 1)){
            return "ERROR.POSICION DE PALABRA INVALIDA.";
        }
        for (int i = 1; i < posicionPalabra; i++){  auxlp = auxlp->sigPalabra; }

        ListaPalabra nuevaPalabra = new nodoPalabra;
        nuevaPalabra->palabra = PALABRA;
        nuevaPalabra->sigPalabra = auxlp->sigPalabra;
        auxlp->sigPalabra = nuevaPalabra;
        return  "INSERTADA CORRECTAMENTE";
        
    }else{
        return  "LO SENTIMOS LA CANTIDAD DE PALABRA DE ESTA LINEA ESTA LLENA";

    }

}

int main()
{
    inicializarDummy();

    insertar_linea_al_final() ;
    //InsertarLineaEnPosicion(0) ;
    insertar_linea_al_final() ;
    insertar_linea_al_final() ;


    cout << InsertarPalabra(1,1,"Hola"); 

    imprimir();
    //cout << L->sig->cant_pal;
}
