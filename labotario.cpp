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


enum TipoRetorno{
    OK,
    ERROR,
    NO_IMPLEMENTADA
};

typedef unsigned int Posicion;



/*** FUNCIONES REQUERIDAS ***/

TipoRetorno insertar_linea_al_final();
TipoRetorno InsertarLineaEnPosicion(int);
void imprimir();
TipoRetorno InsertaPalabra();
TipoRetorno Borrar_linea_segun_posicion(int);
TipoRetorno BorrarTodo();
TipoRetorno BorrarOcurrenciasPalabraEnLinea(int,string);
void ImprimirLinea();




//** FUNCIONES ADICIONALES  ***/

void inicializarDummy();
int  getCantNodoLinea();
int  getCantNodoPalabra();
ListaLinea createLine();
ListaPalabra createPalabra();
ListaLinea buscarLine(int);
ListaPalabra buscarPalabra();



void  inicializarDummy()
{
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

ListaLinea findLine(int posicionLinea){
    if (!(posicionLinea >= 1 && posicionLinea <= getCantNodoLinea() + 1))
    {
        return NULL;
    }    
    ListaLinea aux = L;
    for (int i = 1; i < posicionLinea; i++)
    {
        aux = aux->sig;
    }

    return aux;
}

ListaLinea findPalabra(ListaPalabra bpal , int posicionPal)
{
    if (!(posicionPal >= 1 && posicionPal <= getCantNodoPalabra(bpal) + 1))
    {
        return NULL;
    }
    ListaPalabra aux = bpal;
    for (int i = 1; i < posicionPal; i++)
    {
        aux = aux->sig;
    }
    return aux;
}

ListaLinea createLine()
{
    ListaLinea newline = new nodoLinea;
    newline->sig = NULL;
    newline->sigPalabra = new nodoPalabra;
    newline->sigPalabra->sigPalabra = NULL;
    return newline;
}

ListaLinea createPalabra(string palabra)
{
    ListaPalabra nodoPalabra = new nodoPalabra;
    nodoPalabra->palabra = palabra;
    nodoPalabra->sigPalabra = NULL;
    return nodoPalabra;
}



//Insertar linea al final
TipoRetorno insertar_linea_al_final () {
    ListaLinea newline = new nodoLinea;
    newline->sig = NULL;
    newline->sigPalabra = new nodoPalabra;
    newline->sigPalabra->sigPalabra = NULL;
    if (L->sig == NULL) {
        L->sig = newline;
        return OK;
    }
    else {
        ListaLinea aux = L;
        while (aux->sig != NULL) {
            aux = aux->sig;
        }  
        aux->sig = newline;
    }
    return OK;
}





//Insertar nueva linea en posicion n
//UTILIZA NODO DUMMY;

TipoRetorno InsertarLineaEnPosicion(int posicionLinea){
    if(!(posicionLinea >=1 && posicionLinea <= getCantNodoLinea() + 1)){  return ERROR;  }

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
    return OK;
}



//Imprimir texto
void imprimir () {
    int num_linea = 1;
    ListaLinea aux = L;
    while (aux->sig != NULL) {
        cout << num_linea << ":";
        if (aux->sig->sigPalabra != NULL){
            ListaPalabra auxp = aux->sig->sigPalabra;
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
TipoRetorno InsertarPalabra(int posicionLinea, int posicionPalabra, string PALABRA)
{
    if (L->sig == NULL)
    {
        return ERROR;
    }

    if (!(posicionLinea >= 1 && posicionLinea <= getCantNodoLinea()))
    {
        return ERROR;
    }
    if (posicionPalabra > MAX_CANT_PALABRAS)
    {
        return ERROR;
    }
    ListaLinea aux = L;
    for (int i = 1; i < posicionLinea; i++)
    {
        aux = aux->sig;
    }
    ListaPalabra ant = NULL; //Almacenamos SI ES REQUERIDO EL ultimo nodo de la linea anterior ,para luego insertarlo en el primero de la siguiente.
    while (aux->sig != NULL)
    {
        ListaPalabra auxlp = aux->sig->sigPalabra; //LISTA PALABRAS DE LA LINEA
        int cantPal = getCantNodoPalabra(auxlp);   //Cantidad de palabras en la linea

        if (cantPal < MAX_CANT_PALABRAS && ant == NULL) //SI el nodo tiene menos palabras que el anterior
        {
            for (int i = 1; i < posicionPalabra; i++)
            {
                auxlp = auxlp->sigPalabra;
            }
            ListaPalabra nuevaPalabra = new nodoPalabra;
            nuevaPalabra->palabra = PALABRA;
            nuevaPalabra->sigPalabra = auxlp->sigPalabra;
            auxlp->sigPalabra = nuevaPalabra;
            return OK;
        }
        else if (cantPal < MAX_CANT_PALABRAS && ant != NULL)
        {
            ant->sigPalabra = auxlp->sigPalabra;
            auxlp->sigPalabra = ant;
            return OK;
        }
        else
        {

            if (ant != NULL)
            {
                ant->sigPalabra = auxlp->sigPalabra;
                auxlp->sigPalabra = ant;
            }
            else
            {
                for (int i = 1; i < posicionPalabra; i++)
                {
                    auxlp = auxlp->sigPalabra;
                }
                ListaPalabra nuevaPalabra = new nodoPalabra;
                nuevaPalabra->palabra = PALABRA;
                nuevaPalabra->sigPalabra = auxlp->sigPalabra;
                auxlp->sigPalabra = nuevaPalabra;

                ListaPalabra auxlp2 = auxlp;
                while (auxlp2->sigPalabra->sigPalabra != NULL)
                {
                    auxlp2 = auxlp2->sigPalabra;
                }
                ListaPalabra lastNodo = new nodoPalabra;
                lastNodo->palabra = auxlp2->sigPalabra->palabra;
                auxlp2->sigPalabra = NULL;
                ant = lastNodo;
            }

            aux = aux->sig;
        }
    }
}



//Borrar linea segun posicion
TipoRetorno Borrar_linea(int pos) {
    int cant = getCantNodoLinea();
    if (cant == 0 || cant < pos) {
        return ERROR;
    }
    else {
       ListaLinea aux = L;
        for (int i = 1; i < pos; i++) {
        aux = aux->sig;
        }
        ListaLinea borrar = aux->sig;
        ListaPalabra bpal = aux->sig->sigPalabra;
        while (bpal->sigPalabra != NULL) {
            ListaPalabra borrar_palabra = bpal->sigPalabra;
            bpal->sigPalabra = borrar_palabra->sigPalabra;
            delete borrar_palabra;
        }
        borrar->sigPalabra = NULL;
        delete bpal;
        aux->sig = borrar->sig;
        delete borrar; 
        return OK;
    }
}


TipoRetorno BorrarTodo(){
    ListaLinea aux = L;
    while (aux->sig != NULL){
        ListaLinea borrarLinea = aux->sig;
        ListaPalabra bpal = borrarLinea->sigPalabra;
        while (bpal->sigPalabra != NULL)
        {
            ListaPalabra borrar_palabra = bpal->sigPalabra;
            bpal->sigPalabra = borrar_palabra->sigPalabra;
            delete borrar_palabra;
        }
        aux->sigPalabra = NULL;
        delete bpal;

        //
        aux->sig = borrarLinea->sig;
        delete borrarLinea;
        
    }
    return OK;
}

TipoRetorno BorrarOcurrenciasPalabraEnLinea(int posicionLinea, string PALABRA){
    int cant = getCantNodoLinea();
    if (cant == 0 || cant < posicionLinea)
    {
        return ERROR;
    }
    ListaLinea aux = L;
    for (int i = 1; i < posicionLinea; i++)
    {
        aux = aux->sig;
    }
    ListaPalabra auxlp = aux->sig->sigPalabra;
    while (auxlp->sigPalabra != NULL)
    {
        if(auxlp->sigPalabra->palabra == PALABRA){
             ListaPalabra borrar_pal= auxlp->sigPalabra;
             auxlp->sigPalabra = borrar_pal->sigPalabra;
             delete borrar_pal;
        }else{
            auxlp = auxlp->sigPalabra;
        }
    }

    return OK;
}

void ImprimirLinea(int posLine){
    if(!(posLine >= 1 && posLine <= getCantNodoLinea())){
        cout << "Linea no existe";
    }
    int num_linea = 1;
    ListaLinea aux = L;
    for (int i = 1; i < posLine; i++)
    {
         num_linea ++;
         aux = aux->sig;
    }
    cout << num_linea << ":";
    ListaPalabra auxp = aux->sig->sigPalabra;
    while (auxp->sigPalabra != NULL){
       cout << auxp->sigPalabra->palabra << " ";
       auxp = auxp->sigPalabra;
    }

}




void test_leo () {
    inicializarDummy();

    insertar_linea_al_final();
    InsertarLineaEnPosicion(2);
    InsertarLineaEnPosicion(3);
    insertar_linea_al_final();
    insertar_linea_al_final();
    InsertarPalabra(1,1,"Hola"); 
    InsertarPalabra(1,2,"Perro");
    InsertarPalabra(1,1,"Gato");
    InsertarPalabra(1,1,"Gato");
    InsertarPalabra(1,1, "Gatito"); 
    InsertarPalabra(1,1, "Gatito");
    imprimir();
    cout << endl;
    Borrar_linea(2);
    imprimir();
     
    //cout << contar_lineas();
}

void test_rodri(){
    inicializarDummy();

    insertar_linea_al_final() ;
    insertar_linea_al_final() ;
    insertar_linea_al_final() ;
    InsertarPalabra(1,1,"Hola");
    InsertarPalabra(1, 1, "Mujica");
    InsertarPalabra(1, 1, "Hola");
    InsertarPalabra(1, 1, "Hola");

    imprimir();
    cout << endl;
    imprimir();
}

int main()
{
   test_rodri();
}
