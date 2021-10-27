#include <iostream>
#include <string>

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

struct comandos {
    string sintaxis;
    string param1;
    string param2;
    string param3;
};

typedef nodoPalabra * ListaPalabra;
typedef nodoLinea * ListaLinea;

ListaLinea L = new nodoLinea;

enum TipoRetorno{
    ERROR,
    OK,
    NO_IMPLEMENTADA
};

typedef unsigned int Posicion;

/*** FUNCIONES REQUERIDAS ***/

TipoRetorno insertar_linea_al_final();
TipoRetorno InsertarLineaEnPosicion(int);
void imprimir();
TipoRetorno InsertaPalabra(int, int, string);
TipoRetorno Borrar_linea_segun_posicion(int);
TipoRetorno BorrarTodo();
TipoRetorno BorrarOcurrenciasPalabraEnLinea(int,string);
void ImprimirLinea();
TipoRetorno BorrarPalabra(int, int);
TipoRetorno BorrarOcurrenciasPalabraEnTexto(string);
TipoRetorno ComprimirTexto();
void menu();

//** FUNCIONES ADICIONALES  ***/

void inicializarDummy();
int  getCantNodoLinea();
int  getCantNodoPalabra(ListaPalabra);
ListaLinea createLine();
ListaPalabra createPalabra();
ListaLinea buscarLine(int);
ListaPalabra buscarPalabra();
ListaLinea findPalabra(ListaPalabra , int);



void  inicializarDummy() {
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

int getCantNodoPalabra(ListaPalabra lp) {
     int cantPal = 0;
     while (lp->sigPalabra != NULL){
        cantPal++;
        lp = lp->sigPalabra;
     }
     return cantPal; 
}

ListaLinea buscarLine(int posicionLinea) {
    if (!(posicionLinea >= 1 && posicionLinea <= getCantNodoLinea() + 1)) {
        return NULL;
    }    
    ListaLinea aux = L;
    for (int i = 1; i < posicionLinea; i++) {
        aux = aux->sig;
    }
    return aux;
}

//ListaPalabra findPalabra (ListaPalabra bpal , int posicionPal) {
//    if (!(posicionPal >= 1 && posicionPal <= getCantNodoPalabra(bpal))) {
//        return NULL;
//    }
//    ListaPalabra aux = bpal;
//    for (int i = 1; i < posicionPal; i++) {
//        aux = aux->sigPalabra;
//    }
//    return aux;
//}

ListaLinea createLine() {
    ListaLinea newline = new nodoLinea;
    newline->sig = NULL;
    newline->sigPalabra = new nodoPalabra;
    newline->sigPalabra->sigPalabra = NULL;
    return newline;
}

//ListaLinea createPalabra(string palabra)
//{
//    ListaPalabra nodoPalabra = new nodoPalabra;
//    nodoPalabra->palabra = palabra;
//    nodoPalabra->sigPalabra = NULL;
//    return nodoPalabra;
//}

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
    if(!(posicionLinea >=1 && posicionLinea <= getCantNodoLinea() + 1)) { 
        return ERROR;  
    }
    ListaLinea aux = L;
    ListaLinea newLine = new nodoLinea;
    newLine->sigPalabra = new nodoPalabra;
    newLine->sigPalabra->sigPalabra = NULL;
    for(int i=1; i < posicionLinea; i++) {  
        aux = aux->sig; 
    }
    if(aux->sig == NULL) {
        newLine->sig = NULL;
        aux->sig = newLine;
    }
    else {
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
        if (aux->sig->sigPalabra != NULL) {
            ListaPalabra auxp = aux->sig->sigPalabra;
            while (auxp->sigPalabra != NULL) {
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
TipoRetorno InsertarPalabra(int posicionLinea, int posicionPalabra, string PALABRA) {
     ListaLinea lineaAnt = buscarLine(posicionLinea);
     if(lineaAnt == NULL){
         return ERROR;
     }   
     if(posicionPalabra > MAX_CANT_PALABRAS){
         return ERROR;
     }

     ListaPalabra nuevaPalabra = new nodoPalabra;
     nuevaPalabra->palabra = PALABRA;
     ListaPalabra ant = NULL;

     while (lineaAnt->sig != NULL){
         ListaPalabra auxlp = lineaAnt->sig->sigPalabra;
         int cantPalabras = getCantNodoPalabra(auxlp);

         if (cantPalabras < MAX_CANT_PALABRAS)
         {
             if (ant == NULL)
             {
                 nuevaPalabra->sigPalabra = auxlp->sigPalabra;
                 auxlp->sigPalabra = nuevaPalabra;
                 return OK;
             }
             else
             {
                ant->sigPalabra = auxlp->sigPalabra;
                auxlp->sigPalabra = ant;
                return OK;
             }
         }
         else
         {
             while (auxlp->sigPalabra->sigPalabra != NULL)
             {
                 auxlp = auxlp->sigPalabra;
             }
             ListaPalabra ultimo = auxlp->sigPalabra;
             auxlp->sigPalabra = NULL;
             auxlp = lineaAnt->sig->sigPalabra;
             
        
             if (ant == NULL)
             {
                 for (int i = 0; i < posicionPalabra; i++)
                 {
                     auxlp = auxlp->sigPalabra;
                 }
                 nuevaPalabra->sigPalabra = auxlp->sigPalabra;
                 auxlp->sigPalabra = nuevaPalabra;
             }
             else
             {
                 ant->sigPalabra = auxlp->sigPalabra;
                 auxlp->sigPalabra = ant;
             }
             ant = ultimo;
             lineaAnt = lineaAnt->sig;
         }
       
     }

     ListaLinea nuevaLinea = createLine();
     lineaAnt->sig = nuevaLinea;
     nuevaLinea->sigPalabra->sigPalabra = ant; 
     return OK;
     
    
     

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

TipoRetorno BorrarTodo() {
    ListaLinea aux = L;
    while (aux->sig != NULL){
        ListaLinea borrarLinea = aux->sig;
        ListaPalabra bpal = borrarLinea->sigPalabra;
        while (bpal->sigPalabra != NULL)  {
            ListaPalabra borrar_palabra = bpal->sigPalabra;
            bpal->sigPalabra = borrar_palabra->sigPalabra;
            delete borrar_palabra;
        }
        aux->sigPalabra = NULL;
        delete bpal;
        
        aux->sig = borrarLinea->sig;
        delete borrarLinea;
    }
    return OK;
}

TipoRetorno BorrarOcurrenciasPalabraEnLinea(int posicionLinea, string PALABRA) {
    int cant = getCantNodoLinea();
    if (cant == 0 || cant < posicionLinea) {
        return ERROR;
    }
    ListaLinea aux = L;
    for (int i = 1; i < posicionLinea; i++) {
        aux = aux->sig;
    }
    ListaPalabra auxlp = aux->sig->sigPalabra;
    while (auxlp->sigPalabra != NULL) {
        if(auxlp->sigPalabra->palabra == PALABRA) {
             ListaPalabra borrar_pal= auxlp->sigPalabra;
             auxlp->sigPalabra = borrar_pal->sigPalabra;
             delete borrar_pal;
        }else {
            auxlp = auxlp->sigPalabra;
        }
    }
    return OK;
}

void ImprimirLinea(int posLine){
    if(!(posLine >= 1 && posLine <= getCantNodoLinea())) {
        cout << "Linea no existe";
    }
    int num_linea = 1;
    ListaLinea aux = L;
    for (int i = 1; i < posLine; i++) {
         num_linea ++;
         aux = aux->sig;
    }
    cout << num_linea << ":";
    ListaPalabra auxp = aux->sig->sigPalabra;
    while (auxp->sigPalabra != NULL) {
       cout << auxp->sigPalabra->palabra << " ";
       auxp = auxp->sigPalabra;
    }
}

TipoRetorno BorrarPalabra (int poslinea, int pospalabra) {
    if (L->sig == NULL || getCantNodoLinea() < poslinea) {
        return ERROR;
    }
    else {
        ListaLinea aux = L;
        for (int i = 1; i < poslinea; i++) {
            aux = aux->sig;
        }
        if ( getCantNodoPalabra(aux->sig->sigPalabra) < pospalabra ) {
            return ERROR;
        }
        else {
            ListaPalabra pal = aux->sig->sigPalabra;
            for (int i = 1; i < pospalabra; i++) {
                pal = pal->sigPalabra;
            }
            ListaPalabra borrar = pal->sigPalabra;
            pal->sigPalabra = borrar->sigPalabra;
            delete borrar;
        }
    }
    return OK;
}

TipoRetorno BorrarOcurrenciasPalabraEnTexto (string pal) {
    ListaLinea aux = L;
    ListaPalabra palabra;
    ListaPalabra borrar;
    if (L->sig == NULL) {
        return ERROR;
    }
    else {
        while (aux->sig != NULL) {
            aux = aux->sig;
            palabra = aux->sigPalabra;
            while (palabra->sigPalabra != NULL) {
                if ( palabra->sigPalabra->palabra == pal ) {
                    borrar = palabra->sigPalabra;
                    palabra->sigPalabra = borrar->sigPalabra;
                    delete borrar;
                }
                else {
                    palabra = palabra->sigPalabra;
                }
            }
        }
        return OK;  
    }
}


TipoRetorno ComprimirTexto(){
    ListaLinea aux = L;
    
    //Nuevo texto empezando por dummy
    ListaLinea textoComprimido = new nodoLinea;
    textoComprimido->sig = NULL;
    textoComprimido->sigPalabra = NULL;

    ListaLinea auxTextoComp = textoComprimido;

    int cantPalabrasForLine = 0;

    while (aux->sig != NULL)
    {     
        ListaPalabra auxlp = aux->sig->sigPalabra;
        while (auxlp->sigPalabra != NULL)
        { 
          if(cantPalabrasForLine == 0){
              auxTextoComp->sig = createLine();
          }

          ListaPalabra nueva_palabra = new nodoPalabra;
          nueva_palabra->palabra = auxlp->sigPalabra->palabra;
          nueva_palabra->sigPalabra = NULL;     
        
          ListaPalabra aux_nuevas_palabras = auxTextoComp->sig->sigPalabra;
          while (aux_nuevas_palabras->sigPalabra != NULL)
          {
              aux_nuevas_palabras = aux_nuevas_palabras->sigPalabra;
          }
          aux_nuevas_palabras->sigPalabra = nueva_palabra;
          cantPalabrasForLine ++;
          if(cantPalabrasForLine == MAX_CANT_PALABRAS){
              cantPalabrasForLine = 0;
              auxTextoComp = auxTextoComp->sig;
          }
          auxlp = auxlp->sigPalabra;
        }
        aux = aux->sig;
    }

    BorrarTodo();
    imprimir();
    L = textoComprimido;
    return OK; 
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
    InsertarPalabra(1,1, "Lorito");
    InsertarPalabra(1,1, "Lorito");
    InsertarPalabra(3,1, "Lorito");
    InsertarPalabra(3,2, "Lorito");
    InsertarPalabra(4,1, "Lorito");
    imprimir();

    cout << endl;

    BorrarOcurrenciasPalabraEnTexto("Pepito");
    //Borrar_linea(2);
    //BorrarPalabra(20, 5);
    imprimir();
}

void test_rodri(){
    inicializarDummy();

    insertar_linea_al_final() ;
    insertar_linea_al_final() ;
    insertar_linea_al_final() ;
    InsertarPalabra(1,1,"Hola");
    InsertarPalabra(1, 1, "Rodrigo");
    InsertarPalabra(1, 1, "Castro");
    InsertarPalabra(1, 1, "como");
    InsertarPalabra(1, 1, "como");
    InsertarPalabra(1, 1, "como");
    InsertarPalabra(1, 1, "como");
    InsertarPalabra(1, 1, "como");
    InsertarPalabra(1, 1, "como");
    InsertarPalabra(1, 1, "como");
    InsertarPalabra(1,2,"Muzarella");

    BorrarOcurrenciasPalabraEnTexto("como");

    InsertarPalabra(2,1, "Fantasma");
    InsertarPalabra(3, 1, "Mujica");

    cout << endl;
    imprimir();
}

comandos procesar(){ 
    string comando;
    comandos com;
    cout << "Ingrese el comando: ";
    cin >> comando;

    int pos = 0;
    string delimiter = "(";
    string delimiter2 = ",";
    string delimiter3 = ")";

    pos = comando.find (delimiter);
    com.sintaxis = comando.substr(0, pos);
    comando.erase(0, pos + delimiter.length());

    if (comando.find(delimiter2)) {
        pos = comando.find(delimiter2);
        com.param1 = comando.substr(0, pos);
        comando.erase(0, pos + delimiter2.length());

        if (comando.find(delimiter2)) {
            pos = comando.find(delimiter2);
            com.param2 = comando.substr(0, pos);
            comando.erase(0, pos + delimiter2.length());
        }
    }
    pos = comando.find(delimiter3);
    com.param3 = comando.substr(0, pos);
    comando.erase(0, pos + delimiter3.length());
    return com;
}

void Menu() {

    char opcion;
    do
    {
        comandos com = procesar();
        string sintaxis = com.sintaxis;
        int i = 0;

        if (sintaxis == "InsertarLinea")
        {
            if (insertar_linea_al_final() == 1)
            {
                cout << "OK";
            }
            else
            {
                cout << "ERROR MACHAZO";
            }
        }
        else if (sintaxis == "ImprimirTexto")
        {
            imprimir();
        }
        else if (sintaxis == "InsertarLineaEnPosicion")
        {
            try
            {
                int p1 = std::stoi(com.param1);
                InsertarLineaEnPosicion(p1);
            }
            catch (invalid_argument const &e)
            {
                cout << "syntax error: parametros invalidos";
            }
        }
        else
        {
            cout << "Error en el comando!";
        }

        cout << endl << "Deseas salir? 1: Yes 0: No";
        cin >> opcion;
        while (opcion != '1' && opcion != '2')
        {
            cout << "OPCION INVALIDA VUELVE A INTENTARLO";
            cin >> opcion;
        }
    } while (opcion != '1');


    cout << "PROGRAMA FINALIZADO!";
}
    
void imprimir_fecha(comandos com) {
    cout << endl;
    cout << "   DIA >>> " << com.sintaxis << endl; 
    cout << "   MES >>> " << com.param1 << endl; 
    cout << "   ANIO >>> " << com.param2 << endl; 
    cout << "   ANIO >>> " << com.param3 << endl;
}

int main()
{
    inicializarDummy();
    //test_rodri();
    //test_leo();
    //menu();
    //imprimir_fecha(com);
    Menu();
}
