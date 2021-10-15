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





/*** FUNCIONES REQUERIDAS ***/

string insertar_linea_al_final();
string InsertarLineaEnPosicion(int);
void imprimir();
string InsertaPalabra();
string Borrar_linea_segun_posicion(int);
string BorrarTodo();
void ImprimirLinea();




//** FUNCIONES ADICIONALES  ***/

void inicializarDummy();
int  getCantNodoLinea();
int  getCantNodoPalabra();




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
string InsertarPalabra(int posicionLinea, int posicionPalabra, string PALABRA)
{
    if (L->sig == NULL)
    {
        return "ERROR POSICION DE LINEA INVALIDA.LA LINEA ESTA VACIA";
    }

    if (!(posicionLinea >= 1 && posicionLinea <= getCantNodoLinea()))
    {
        return "ERROR.POSICION INVALIDA";
    }
    if (posicionPalabra > MAX_CANT_PALABRAS)
    {
        return "POSICION INVALIDA!,LA POSICION EXCEDE LA CANTIDAD DE PALABRAS POR LINEAS";
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
            return "INSERTADA CORRECTAMENTE";
        }
        else if (cantPal < MAX_CANT_PALABRAS && ant != NULL)
        {
            ant->sigPalabra = auxlp->sigPalabra;
            auxlp->sigPalabra = ant;
            return "";
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
string Borrar_linea(int pos) {
    int cant = getCantNodoLinea();
    if (cant == 0 || cant < pos) {
        return "La linea no existe";
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
        return "borrado";
    }
}


string BorrarTodo(){
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
    return "Lista borrada completamente!";
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
    imprimir();
}

int main()
{
   test_rodri();
}
