#include <iostream>
#include <string>
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RED   "\x1b[31m"

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
    int cant_params;   
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
comandos procesar();
int getCantParamsComando(comandos);

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
     if(!(posicionPalabra >= 1 && posicionPalabra <= MAX_CANT_PALABRAS)){
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
             if (ant == NULL){
                 if(posicionPalabra - 1 > cantPalabras){
                     cout << "ERROR";
                     return ERROR;
                 }else{
                     for (int i = 1; i < posicionPalabra; i++){
                         auxlp = auxlp->sigPalabra;
                     }
                     nuevaPalabra->sigPalabra = auxlp->sigPalabra;
                     auxlp->sigPalabra = nuevaPalabra;

                     return OK;
                 }   
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
                 for (int i = 1; i < posicionPalabra; i++)
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
          if(cantPalabrasForLine == 0) {
              auxTextoComp->sig = createLine();
          }
          ListaPalabra nueva_palabra = new nodoPalabra;
          nueva_palabra->palabra = auxlp->sigPalabra->palabra;
          nueva_palabra->sigPalabra = NULL;     
        
          ListaPalabra aux_nuevas_palabras = auxTextoComp->sig->sigPalabra;
          while (aux_nuevas_palabras->sigPalabra != NULL) {
              aux_nuevas_palabras = aux_nuevas_palabras->sigPalabra;
          }
          aux_nuevas_palabras->sigPalabra = nueva_palabra;
          cantPalabrasForLine ++;
          if(cantPalabrasForLine == MAX_CANT_PALABRAS) {
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

comandos procesar() { 
    string comando;
    comandos com;
    com.cant_params = 0;

    cout <<ANSI_COLOR_YELLOW "Ingrese el comando: " ANSI_COLOR_RESET;
    cin >> comando;

    com.param1 = "";
    com.param2 = "";
    com.param3 = "";


    int pos = 0;
    string delimiter = "(";
    string delimiter2 = ",";
    string delimiter3 = ")";


    pos = comando.find (delimiter);
    com.sintaxis = comando.substr(0, pos);
    comando.erase(0, pos + delimiter.length());      //InsertarPalabra(1,2,3)
                                                        
                                                        //sinxtaxis =InsertarPalabra
                                                          //1,2,

    if (comando.find(delimiter2) == true) {
        pos = comando.find(delimiter2);              //param1 = 1
        com.param1 = comando.substr(0, pos);
        com.cant_params ++;
        comando.erase(0, pos + delimiter2.length());   // 2,3)

        if (comando.find(delimiter2) == true) {             
            pos = comando.find(delimiter2);                  //3)
            com.param2 = comando.substr(0, pos);
            com.cant_params++;
            comando.erase(0, pos + delimiter2.length());

            if(comando.find(delimiter2) == true){
                pos = comando.find(delimiter2); //3)
                com.param3 = comando.substr(0, pos);
                com.cant_params++;
                comando.erase(0, pos + delimiter2.length());

                if (comando != "")
                {
                    com.cant_params = -1;
                }
            }else{
                pos = comando.find(delimiter3); //3)
                com.param3 = comando.substr(0, pos);
                comando.erase(0, pos + delimiter3.length());

                if(comando != ""){
                    com.cant_params = -1;
                }
            }
           
        }else{
            pos = comando.find(delimiter3); //3)
            com.param2 = comando.substr(0, pos);
            comando.erase(0, pos + delimiter3.length());
        }
    }else{
        pos = comando.find(delimiter3);
        com.param1 = comando.substr(0, pos);
        comando.erase(0, pos + delimiter3.length());
    }
    return com;
}

void Menu() {
    char opcion;
    string sintaxis;
    try {
        do {
            comandos com = procesar();
            if(com.cant_params == -1){
                cout << "ERROR, EL COMANDO NO RECIBE ESA CANTIDAD DE PARAMETROS" << endl;
            }else{
                sintaxis = com.sintaxis;
                cout << "Parametro 1:  " << com.param1 << endl;
                cout << "Parametro 2:  " << com.param2 << endl;
                cout << "Parametro 3:  " << com.param3 << endl;
    

                if (sintaxis == "InsertarLinea")
                {
                    if (insertar_linea_al_final() == OK)
                    {
                        cout << "OK" << endl;
                    }
                    else
                    {
                        cout << "ERROR" << endl;
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
                        cout << InsertarLineaEnPosicion(p1);
                    }
                    catch (invalid_argument const &e)
                    {
                        cout << "ERROR" << endl;
                    }
                }
                else if (sintaxis == "BorrarLinea")
                {
                    int p1 = std::stoi(com.param1);
                    if (Borrar_linea(p1) == 1)
                    {
                        cout << "OK" << endl;
                    }
                    else
                    {
                        cout << "ERROR" << endl;
                    }
                }
                else if (sintaxis == "BorrarTodo")
                {
                    if (BorrarTodo() == 1)
                    {
                        cout << "OK" << endl;
                    }
                    else
                    {
                        cout << "ERROR" << endl;
                    }
                }
                else if (sintaxis == "BorrarOcurrenciasPalabraEnTexto")
                {
                    if (BorrarOcurrenciasPalabraEnTexto(com.param3) == 1)
                    {
                        cout << "OK" << endl;
                    }
                    else
                    {
                        cout << "ERROR" << endl;
                    }
                }
                else if (sintaxis == "ComprimirTexto")
                {
                    if (ComprimirTexto() == 1)
                    {
                        cout << "OK" << endl;
                    }
                    else
                    {
                        cout << "ERROR" << endl;
                    }
                }
                else if (sintaxis == "InsertarPalabra")
                {
                    if (com.cant_params == 3)
                    {
                        try
                        {
                            int p1 = std::stoi(com.param1);
                            int p2 = std::stoi(com.param2);
                            if (InsertarPalabra(p1, p2, com.param3) == OK)
                            {
                                cout << "OK" << endl;
                            }
                            else
                            {
                                cout << "ERROR" << endl;
                            }
                        }
                        catch (invalid_argument const &e)
                        {
                            cout << "ERROR" << endl;
                        }
                    }
                    else
                    {
                        cout << "ERROR";
                    }
                }
                else if (sintaxis == "ImprimirLinea")
                {
                    int p1 = std::stoi(com.param1);
                    ImprimirLinea(p1);
                }
                else if (sintaxis == "BorrarPalabra")
                {
                    int p1 = std::stoi(com.param1);
                    int p2 = std::stoi(com.param2);
                    if (BorrarPalabra(p1, p2) == 1)
                    {
                        cout << "OK" << endl;
                    }
                    else
                    {
                        cout << "ERROR" << endl;
                    }
                }
                else if (sintaxis == "BorrarOcurrenciasPalabraEnLinea")
                {
                    int p1 = std::stoi(com.param1);
                    if (BorrarOcurrenciasPalabraEnLinea(p1, com.param3) == 1)
                    {
                        cout << "OK" << endl;
                    }
                    else
                    {
                        cout << "ERROR" << endl;
                    }
                }
                else if (sintaxis == "Help")
                {
                    cout << endl;
                    cout << ANSI_COLOR_GREEN "****SINTAXIS PARA EL CORRECRTO FUNCIONAMIENTO DE LOS COMANDOS:****" ANSI_COLOR_RESET << endl;
                    cout << endl;
                    cout << "NombreDelComando(parametro 1,parametro 2,parametro 3)" << endl;
                    cout << endl;
                    cout << ANSI_COLOR_BLUE "EN CASO DE QUE EL COMANDO REQUIRA MENOS PARAMETROS:" ANSI_COLOR_RESET << endl;
                    cout << endl;
                    cout << "NombreDelComando(parametro 1,parametro 2)" << endl;
                    cout << "NombreDelComando(parametro)" << endl;
                    cout << "NombreDelComando()" << endl;
                    cout << endl;
                    cout << ANSI_COLOR_RED "ES IMPORTANTE QUE NO HAYA ESPACIOS ENTRE LA COMA Y EL PARAMETRO, LA PALABRA NO DEBE TENER COMILLAS" ANSI_COLOR_RESET << endl;
                    cout << endl;
                    cout << ANSI_COLOR_GREEN "****LISTADO DE COMANDOS DISPONIBLES:****" ANSI_COLOR_RESET << endl;
                    cout << endl;
                    cout << "InsertarLinea()" << endl;
                    cout << "InsertarLineaEnPosicion(PosicionLinea)" << endl;
                    cout << "BorrarLinea(Posicion posicionLinea)" << endl;
                    cout << "BorrarTodo()" << endl;
                    cout << "BorrarOcurrenciasPalabraEnTexto(palabraABorrar)" << endl;
                    cout << "ImprimirTexto()" << endl;
                    cout << "ComprimirTexto()" << endl;
                    cout << "InsertarPalabra(posicionLinea, posicionPalabra, palabraAIngresar)" << endl;
                    cout << "ImprimirLinea(posicionLinea)" << endl;
                    cout << "BorrarPalabra(posicionLinea, posicionPalabra)" << endl;
                    cout << "BorrarOcurrenciasPalabraEnLinea(posicionLinea, palabraABorrar)" << endl;
                    cout << "Help()- Comando para ver ayuda" << endl;
                    cout << ANSI_COLOR_BLUE "Exit()- finaliza el programa" ANSI_COLOR_RESET << endl;
                    cout << endl;
                }
                else
                {
                    cout << ANSI_COLOR_RED "¡Comando Desconocido!" ANSI_COLOR_RESET << endl;
                }
            }
        }
        while (sintaxis != "Exit");
        cout << "PROGRAMA FINALIZADO!";
    }
    catch (invalid_argument const &e) {
        cout << "ERROR";
    }
}

int main() {
    inicializarDummy();


    Menu();


}
