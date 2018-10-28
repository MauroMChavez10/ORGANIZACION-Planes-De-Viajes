#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "constantes.h"
#include "colacp.h"


typedef struct ciudad
{
    char *nombre;
    float pos_x;
    float pos_y;
} *TCiudad;

/**
    Si el primer argumento pasado a la funcion fAscendente es menor al segundo, retorna -1.
    Si ambos argumentos son iguales retorna 0.
    En otro caso 1
*/
int fAscendente(TEntrada a,TEntrada b)
{
    int salida;

    int * pa;
    pa = (int *)a->clave;
    int *pb;
    pb = (int *)b->clave;

    if (*pa == *pb)
        salida= 0;
    else if (*pa>*pb) /** ESTA LINEA ESTA CAMBIADA, HABIA PUESTO MAL LA CONDICION !! AHORA ANDA BIEN */
        salida = -1; /** PARA ASCENDENTE.. CLAVE(A) = 70 Y CLAVE(B) = 5 . EN ESTE CASO B TIENE MAS PRIORIDAD QUE A */
    else
        salida = 1;

    return salida;
}

int fDescendente(TEntrada a,TEntrada b)
{
    int salida;

    int * pa;
    pa = (int *)a->clave;
    int *pb;
    pb = (int *)b->clave;

    if (*pa == *pb)
        salida= 0;
    else if (*pa<*pb) /** ClAVE(A) = 5 Y CLAVE (B) = 70 . RETORNO -1 */
        salida = -1;
    else
        salida = 1;

    return salida;
}


void mostrarLista(TLista *lista)
{
    TPosicion pos = *lista;
    int *pElemento = (int *)pos;
    while(pos != NULL)
    {
        pElemento = pos->elemento;
        printf("%d ",*pElemento);
        //pElemento = pos->elemento;
        pos = pos->celda_siguiente;

    }
    printf("\n");
}

int profundidadNodo(TColaCP cola,TNodo n)
{

    if(n == cola->raiz)
        return 0;
    else
        return 1 + profundidadNodo(cola,n->padre);


}

/** Este metodo mostrara a la cola con prioridad en recorrido pre orden y cada elemento con su profundidad */
void mostrarCCP(TColaCP cola,TNodo raiz)
{
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



int main()
{

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

    /** En el caso de que se intente mandar como primer argumento POS_NULA se abortara la ejecucion */
    l_insertar(&lista,POS_NULA,pA); /** el tercer parametro tambien es un puntero. Mandar & */

    TPosicion primeraPosicion = l_primera(lista);



    l_insertar(&lista,primeraPosicion,pB);

    primeraPosicion = l_primera(lista); /** VALOR ACTUALIZADO DEL NUEVO PRIMER ELEMENTO CUIDADO CON EL USO DE VARIABLES */
    //printf("primer elemento : %d\n",*(int*)primeraPosicion->elemento);


    TPosicion ultimaPosicion = l_ultima(lista);
//    printf("%d\n",segundaPosicion == NULL);

    l_insertar(&lista,ultimaPosicion,pC);





    // mostrarLista(&lista);
    TPosicion segundaPosicion = l_siguiente(lista,primeraPosicion);
    l_insertar(&lista,segundaPosicion,pD);



    primeraPosicion = l_primera(lista);
    segundaPosicion = l_siguiente(lista,primeraPosicion);
    l_insertar(&lista,segundaPosicion,pE);





    primeraPosicion = l_primera(lista);
    ultimaPosicion = l_ultima(lista);
    TPosicion anteriorAlUltimo = l_anterior(lista,ultimaPosicion);
    segundaPosicion = l_siguiente(lista,primeraPosicion);
    TPosicion terceraPosicion = l_siguiente(lista,segundaPosicion);

    /**TESTEO DE METODOS TDA LISTA */


    printf("TDA Lista \n");
    mostrarLista(&lista);


    //mostrarLista(&lista);
    //printf("El anterior al primero elemento es : %d\n",*(int *)l_anterior(lista,l_primera(lista))->elemento);
    printf("\nEl primer elemento de la lista es : %d\n",*(int *)l_primera(lista)->elemento);
    printf("El anterior del ultimo elemento %d es : %d \n",*(int *)l_ultima(lista)->elemento,*(int*)anteriorAlUltimo->elemento);
    printf("El ultimo elemento de la lista es : %d\n",*(int *)l_ultima(lista)->elemento);
    printf("El siguiente al ultimo elemento es : %p\n",l_siguiente(lista,l_ultima(lista)));
    printf("El anterior al primer elemento es : %p\n",l_anterior(lista,l_primera(lista))); /** COMO RETORNA LA POSICION NO DEBO CASTEAR, PERO TENGO QUE PONER %p */
    printf("El elemento en la  tercer posicion de la lista es : %d\n",*(int *)l_recuperar(lista,terceraPosicion));
    printf("El elemento en la  posicion POS_NULA de la lista es : %p\n",l_recuperar(lista,POS_NULA));
    printf("La cantidad de elementos en la lista es : %d \n",l_size(lista));
    l_eliminar(&lista,l_ultima(lista));
    printf("La lista luego de eliminar el ultimo elemento es : ");
    mostrarLista(&lista);
    printf("La cantidad de elementos en la lista luego de eliminar es : %d \n",l_size(lista));

    //int pudeDestruir = l_destruir(POS_NULA);  anda bien para pos nula


    /** TDA COLA CON PRIORIDAD */
    printf("\nTDA Cola Con Prioridad \n\n");
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
    // int *(pointerFunction) = ccp->f;
    //fAscendente(primerEntrada,segundaEntrada);
    //printf("%d El valor del puntero a la funcion es : \n",*pointerFunction);
    cp_insertar(ccp,primerEntrada);
    cp_insertar(ccp,segundaEntrada);
    cp_insertar(ccp,tercerEntrada);
    cp_insertar(ccp,cuartaEntrada);
    printf("La cantidad de elementos en la cola con prioridad es : %d\n",ccp->cantidad_elementos);

    /** MOSTRANDO LOS ELEMENTOS INSERTADOS EN LA CCP EN PRE ORDEN */
    printf("Cola con prioridad luego de insertar \n");
    mostrarCCP(ccp,ccp->raiz);
    //printf("direccion de hijo derecho de la raiz %p\n",ccp->raiz->hijo_derecho);
    /** TESTEANDO METODO DESTRUIR DE CCP */

    int destruccion = cp_destruir(ccp);

    printf("%d destruccion\n",destruccion);
    printf("cant elementos de ccp %p\n",ccp->raiz->hijo_derecho);

    /** TESTEANDO METODO ELIMINAR DE CCP  */


    //TEntrada eliminado = cp_eliminar(ccp);/** ELIMINA BIEN*/

    //printf("Cola con prioridad luego de eliminar el elemento :%d\n",*(int*)eliminado->clave);
    //mostrarCCP(ccp,ccp->raiz);

    //TEntrada laRaiz = ccp->raiz->entrada;
    //TNodo padreRaiz = ccp->raiz->padre;
    //TNodo hijoIzq = ccp->raiz->hijo_izquierdo;
    //TNodo hijoDer = ccp->raiz->hijo_derecho;
    //printf("Raiz elemento: %d ",*(int*)laRaiz->clave);
    //printf("Padre de la raiz: %p \n",padreRaiz);
    //printf("Hijo izquierdo raiz : %d\n",*(int*)hijoIzq->entrada->clave);
    //printf("Hijo derecho de la raiz : %d\n",*(int*)hijoDer->entrada->clave);

    //cp_eliminar(ccp);
    //printf("\nLuego de eliminar el elemento %d. CCP es: \n",*(int*)eliminado->clave);


    //mostrarCCP(ccp,ccp->raiz);

    //eliminado = cp_eliminar(ccp);


    //printf("Luego de eliminar el elemento %d. CCP es \n",*(int*)eliminado->clave);

    //mostrarCCP(ccp,ccp->raiz);

    //eliminado = cp_eliminar(ccp);

    //printf("Luego de eliminar el elemento %d. CCP es \n",*(int*)eliminado->clave);

    //mostrarCCP(ccp,ccp->raiz); /** Muestra la ccp vacia */

    //printf("\nCantidad de elementos luego de eliminarlos a todos : %d\n",cp_size(ccp));




    /** PROGRAMA PRINCIPAL */

    // leerArchivo();

    return 0;
}
