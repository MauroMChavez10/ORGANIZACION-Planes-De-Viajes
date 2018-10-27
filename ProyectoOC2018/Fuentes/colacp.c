#include <stdio.h>
#include <stdlib.h>
#include "colacp.h"
#include "constantes.h"



TColaCP crear_cola_cp(int (*f) (TEntrada, TEntrada))
{
    TColaCP ccp = (TColaCP) malloc(sizeof(struct cola_con_prioridad));
    ccp->raiz = POS_NULA;
    ccp->cantidad_elementos = 0 ;
    ccp->comparador = f;
    return ccp;
}


TNodo buscarNodo(TColaCP cola,int x){
 TNodo pos = POS_NULA;

    if  (x == 1)
    {
        pos = cola->raiz;

    }
    else /** ESTO ME PARECE QUE ESTA MAL PORQUE SOLO ME ANDARIA CON 3 ELEMENTOS. */
    {
        pos = buscarNodo(cola,x/2); /** ES UNA LLAMADA RECURSIVA A FUNCION ! ASIGNAR LA VARIABLE SINO LA PIERDO. ! */

        if  (x % 2 == 0)
        {

            pos = pos->hijo_izquierdo;
        }
        else
            pos = pos->hijo_derecho;

    }
    return pos ;
}

void intercambiar(TNodo hijo, TNodo padre){
   TEntrada entradaPadre = padre->entrada;
   padre->entrada = hijo->entrada;
   hijo->entrada = entradaPadre;

}

void burbujeoHaciaArriba(TColaCP cola, TNodo nuevo){
    if(nuevo != cola->raiz)
    {

        int i = cola->comparador(nuevo->entrada,nuevo->padre->entrada);
        if( i == 1 ) // ya que si son iguales tambien debo hacer el burbujeo, ESTO PARA MIN HEAP YA QUE LA FUNCION DE COMPARACION SERIA FASCENDENTE Y TENGO QUE INTERCAMBIAR CUANDO ES -1
        {
            intercambiar(nuevo,nuevo->padre);
            burbujeoHaciaArriba(cola,nuevo->padre);
        }

    }

}

int tieneHijoIzquierdo(TNodo n)
{
    return n->hijo_izquierdo != POS_NULA;
}

int tieneHijoDerecho(TNodo n){
    return n->hijo_derecho != POS_NULA;
}

int esHoja(TNodo n){
    return (n->hijo_izquierdo == POS_NULA && n->hijo_derecho == POS_NULA);
}

/** Este metodo provocara que el heap no rompa la propiedad de orden que debe cumplir
*   El parametro r hace referencia a la raiz del heap, la entrada de este es lo que valia el ultimo nodo
*   Si la cola tiene solo un nodo (la raiz),entonces la propiedad de orden esta trivialmente satisfecha
*/
void downHeap(TColaCP cola, TNodo r)
{

    if(r != NULL)
    {
        if(!tieneHijoDerecho(r))
        {
            TNodo s = r->hijo_izquierdo;
            if (cola->comparador(r->entrada,s->entrada) == -1) /** Rompe la propiedad del orden del heap */
                intercambiar(r->entrada,s->entrada);
        }else
        {
            if(tieneHijoIzquierdo(r) && tieneHijoDerecho(r))
            {   TNodo s = POS_NULA;
                if (cola->comparador(r->hijo_izquierdo->entrada,r->hijo_derecho->entrada) == 1) /** Me interesa el hijo de la raiz con menor entrada(MAS PRIORIDAD) */
                {
                     s = r->hijo_izquierdo;
                }else
                {
                     s = r->hijo_derecho;
                }


                if(cola->comparador(r->entrada,s->entrada) == -1) /** DEBE INTERCAMBIARSE CON EL HIJO IZQUIERDO O DERECHO */
                {
                    intercambiar(r->entrada,s->entrada);
                    downHeap(cola,s);

                }else
                {
                if  (cola->comparador(r->entrada,s->entrada) == 1)
                {
                    intercambiar(r->entrada,s->entrada);
                    downHeap(cola,s);
                }


                }

            }
        }
    }

}


int cp_insertar(TColaCP cola, TEntrada entr){
    if(cola == POS_NULA)
    {
        printf("Error cola NULA\n");
        exit(CCP_NO_INI);

    }

    if(cola->raiz == POS_NULA)
    {
        TNodo nuevo = malloc(sizeof(struct nodo));
        if (nuevo == NULL)
            return FALSE;

        nuevo->entrada = entr;
        nuevo->padre = POS_NULA;
        nuevo->hijo_izquierdo = POS_NULA;
        nuevo->hijo_derecho = POS_NULA;
        cola->raiz = nuevo ;
        cola->cantidad_elementos = 1;
    }else // LA COLA TIENE MAS DE UN ELEMENTO
    {
        TNodo padreNuevo = POS_NULA;
        int numeroNodoAInsertar = cola->cantidad_elementos+1;
        padreNuevo = buscarNodo(cola,(numeroNodoAInsertar)/2); /** Este metodo buscara la posicion del padre del nuevo nodo a ser insertado */

        TNodo nuevo = malloc(sizeof(struct nodo));
        nuevo->padre = padreNuevo;

        nuevo->entrada = entr;
        nuevo->hijo_izquierdo = POS_NULA;
        nuevo->hijo_derecho = POS_NULA;

        if( padreNuevo->hijo_izquierdo == POS_NULA)
        {
            padreNuevo->hijo_izquierdo = nuevo;
        }else
        {
            padreNuevo->hijo_derecho = nuevo;
        }

        burbujeoHaciaArriba(cola,nuevo);

        cola->cantidad_elementos = cola->cantidad_elementos + 1 ;

    }

    return TRUE;
}

TEntrada cp_eliminar(TColaCP cola){
    if(cola == POS_NULA)
    {
        printf("Error cola NULA al intentar eliminar \n");
        exit(CCP_NO_INI);
    }

    TNodo w = POS_NULA;
    TEntrada entradaAEliminar = NULL;
    entradaAEliminar = cola->raiz->entrada; /** ME GUARDO EN UNA VARIABLE AUXILIAR PARA NO PERDER LA ENTRADA QUE QUIERO ELIMINAR */
    w = buscarNodo(cola,cola->cantidad_elementos); /** w es el ultimo nodo del arbol mas profundo */
    cola->raiz->entrada = w->entrada;

    TNodo padreDeW = w->padre;
    if(padreDeW->hijo_izquierdo == w)
        padreDeW->hijo_izquierdo = NULL;
    else
        padreDeW->hijo_derecho = NULL;

    w->padre = POS_NULA;
    free(w); /** A ESTA ALTURA LO QUE HICE FUE CAMBIAR LA ENTRADA DEL ULTIMO NODO EN LA RAIZ Y LUEGO ELIMINAR EL ULTIMO NODO.FALTA BURBUJEAR HACIA ABAJO */


    downHeap(cola,cola->raiz); /** EL ARBOL ESTA COMPLETO PERO PODRIA ESTAR VIOLANDO LA PROPIEDAD DE ORDEN DEL HEAP */



    cola->cantidad_elementos = cola->cantidad_elementos - 1;
    return entradaAEliminar;
}

/** DEBO DESTRUIR EN POSORDEN */
int cp_destruir(TColaCP cola);

int cp_size(TColaCP cola){
    if(cola == NULL)
        exit(CCP_NO_INI);

    return cola->cantidad_elementos;
}





