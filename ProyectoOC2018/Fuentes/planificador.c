#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "constantes.h"
#include "colacp.h"


typedef struct ciudad{
    char *nombre;
    float pos_x;
    float pos_y;
} *TCiudad;

/**
    Si el primer argumento pasado a la funcion fAscendente es menor al segundo, retorna -1.
    Si ambos argumentos son iguales retorna 0.
    En otro caso 1
*/
int fAscendente(TEntrada a,TEntrada b){
    int salida;

    int * pa;
    pa = (int *)a->clave;
    int *pb;
    pb = (int *)b->clave;

    if (*pa == *pb)
        salida= 0;
    else
        if (*pa>*pb) /** ESTA LINEA ESTA CAMBIADA, HABIA PUESTO MAL LA CONDICION !! AHORA ANDA BIEN */
            salida = -1; /** PARA ASCENDENTE.. CLAVE(A) = 70 Y CLAVE(B) = 5 . EN ESTE CASO B TIENE MAS PRIORIDAD QUE A */
        else
            salida = 1;

   return salida;
}

int fDescendente(TEntrada a,TEntrada b){
    int salida;

    int * pa;
    pa = (int *)a->clave;
    int *pb;
    pb = (int *)b->clave;

    if (*pa == *pb)
        salida= 0;
    else
        if (*pa<*pb) /** ClAVE(A) = 5 Y CLAVE (B) = 70 . RETORNO -1 */
            salida = -1;
        else
            salida = 1;

   return salida;
}


void mostrarLista(TLista *lista){
    TPosicion pos = *lista;
    int *pElemento = (int *)pos;
    while(pos != NULL)
    {
        pElemento = pos->elemento;
        printf("%d ",*pElemento);
        //pElemento = pos->elemento;
        pos = pos->celda_siguiente;

    }
}

int profundidadNodo(TColaCP cola,TNodo n){

    if(n == cola->raiz)
        return 0;
    else
        return 1 + profundidadNodo(cola,n->padre);


}

/** Este metodo mostrara a la cola con prioridad en recorrido pre orden y cada elemento con su profundidad */
void mostrarCCP(TColaCP cola,TNodo raiz){
    TEntrada t = NULL;
    if(raiz != NULL)
    {
        t = raiz->entrada;
        printf("%d ",*(int*)t->clave);
        printf(" profundidad = %d\n",profundidadNodo(cola,raiz));
        mostrarCCP(cola,raiz->hijo_izquierdo);
        mostrarCCP(cola,raiz->hijo_derecho);
    }


}


int main(){

    TLista lista = crear_lista();
    int a = 5;
    int b = 6;
    int c = 10;
    int d = 30;
    int e = 70;
    void *pA, *pB, *pC,*pD,*pE;

    pA = &a;
    pB = &b;
    pC = &c;
    pD = &d;
    pE = &e;

    l_insertar(&lista,POS_NULA,pA); /** el tercer parametro tambien es un puntero. Mandar & */

    TPosicion primeraPosicion = l_primera(lista);



    l_insertar(&lista,primeraPosicion,pB);


    TPosicion ultimaPosicion = l_ultima(lista);
//    printf("%d\n",segundaPosicion == NULL);

    l_insertar(&lista,ultimaPosicion,pC);


    TPosicion segundaPosicion = l_siguiente(lista,primeraPosicion); /** NO ME ESTA DANDO LA SEGUNDA POSICION DE LA LISTA, SINO LA PRIMERA */
    l_insertar(&lista,segundaPosicion,pD); /** Esta bien que no inserte ante ultimo, porque y si ante penultimo */


    //l_insertar(&lista,segundaPosicion,pE);








    /**TESTEO DE METODOS TDA LISTA */


    printf("TDA Lista \n");
    mostrarLista(&lista);

    //printf("El primer elemento insertado es : %d\n",*(int*)tprimera->elemento);
    //printf("El anterior al primero es : %p\n",l_anterior(lista,tprimera));
    //printf("El ultimo elemento insertado es : %d\n",*(int*)tultima->elemento);
    //printf("La cantidad de elementos en la lista es : %d\n",l_size(lista));
    //printf("El elemento eliminado es : %d\n",)
    //printf("Primer elemento : %i\n", *(int *)tprimera->elemento);// Es un puntero a void no puedo desreferenciarlo de una
    //printf("Segundo elemento : %i\n",*(int *)(tprimera->celda_siguiente->elemento));
   // printf("Tercer elemento : %i\n",*(int *)(tultima->elemento));

    //l_eliminar(&lista,tprimera); /** falla con primera posicion y con pos nula */
    //printf("La cantidad de elementos de la lista luego de eliminar 1 es : %d\n",l_size(lista));
//    TPosicion nuevoPrimerElemento = l_primera(lista);
    //tprimera = l_primera(lista);
   // printf("El nuevo primer elemento de la lista es : %d\n",*(int *)tprimera->elemento);

    //printf("El primer elemento luego de eliminar es : %d\n",*(int*)tprimera->elemento);


    /** TDA COLA CON PRIORIDAD */
    printf("\n\nTDA Cola Con Prioridad \n");
    int numero1 = 10;
    int numero2 = 12;
    int numero3 = 14;
    int numero4 = 8;
    char caracter = 'r';
    char s = 'a';
    char h = 'h';
    char p = 'p';

    /** Creacion de las claves y los valores, ambos son punteros a void */
    TClave clave = &numero1;
    TValor valor = &caracter;

    TClave clave2 = &numero2;
    TValor valor2 = &s;

    TClave clave3 = &numero3;
    TValor valor3 = &h;

    TClave clave4 = &numero4;
    TClave valor4 = &p;

    /** Creacion de las entradas */
    TEntrada primerEntrada,segundaEntrada,tercerEntrada,cuartaEntrada;

    primerEntrada = (TEntrada )malloc(sizeof(struct entrada));
    primerEntrada->valor = valor;
    primerEntrada->clave = clave;

    segundaEntrada = (TEntrada) malloc(sizeof(struct entrada));
    segundaEntrada->clave = clave2;
    segundaEntrada->valor = valor2;

    tercerEntrada = (TEntrada) malloc(sizeof(struct entrada));
    tercerEntrada->clave = clave3;
    tercerEntrada->valor = valor3;

    cuartaEntrada = (TEntrada) malloc((sizeof(struct entrada)));
    cuartaEntrada->clave = clave4;
    cuartaEntrada->valor = valor4;

   int funcionDeComparacionAscendente = fAscendente(primerEntrada,segundaEntrada); /** ACA ES NECESARIO MANDARLE & ? NO VEO LA DIFERENCIA */

   printf("El valor de la funcion de comparacion es : %d\n",funcionDeComparacionAscendente);

   /** TESTEANDO METODO INSERTAR DE COLA CON PRIORIDAD, PRIMERO CREAR LA CCP*/


    int (*pFuncion)(void*,void*) = fAscendente;
    //int j = pFuncion(primerEntrada,segundaEntrada);

    TColaCP ccp = crear_cola_cp(pFuncion); /** FAscendente para minHeap, es necesario POR QUE EL WARNING? */
    /** por que los 3 warnings? uno porque no use la variable todavia ccp..*/
   // int *(pointerFunction) = ccp->f;
    //fAscendente(primerEntrada,segundaEntrada);
    //printf("%d El valor del puntero a la funcion es : \n",*pointerFunction);
    cp_insertar(ccp,primerEntrada);
    cp_insertar(ccp,segundaEntrada);
    cp_insertar(ccp,tercerEntrada);
    cp_insertar(ccp,cuartaEntrada);
    printf("La cantidad de elementos en la cola con prioridad es : %d\n",ccp->cantidad_elementos);

    /** MOSTRANDO LOS ELEMENTOS INSERTADOS EN LA CCP EN PRE ORDEN */
    printf("CCP LUEGO DE INSERTAR \n");
    mostrarCCP(ccp,ccp->raiz);


    /** TESTEANDO METODO ELIMINAR DE CCP  */


    TEntrada eliminado = cp_eliminar(ccp);

    printf("\nLuego de eliminar el elemento %d. CCP es: \n",*(int*)eliminado->clave);


    mostrarCCP(ccp,ccp->raiz);

    printf("La cantidad de elementos en la cola con prioridad es : %d\n",ccp->cantidad_elementos);








return 0;
}
