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

/**
 * BUSCA EL NODO PADRE AL CUAL DEBE ENGANCHARSE EL NUEVO NODO EN INSERTAR.
 * EN ELIMINAR SE UTILIZA PARA ENCONTRAR EL NODO MAS PROFUNDO DEL ARBOL
 */
TNodo buscarNodo(TColaCP cola,int x)
{
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

/**
 * INTERCAMBIARA SOLAMENTE LAS ENTRADAS DE LOS NODOS .
 */
void intercambiar(TNodo hijo, TNodo padre)
{
    TEntrada entradaPadre = padre->entrada;
    padre->entrada = hijo->entrada;
    hijo->entrada = entradaPadre;

}

void burbujeoHaciaArriba(TColaCP cola, TNodo nuevo)
{
    if(nuevo != cola->raiz)
    {
        //int i = cola->comparador(nuevo->padre->entrada,nuevo->entrada);
        int i = cola->comparador(nuevo->entrada,nuevo->padre->entrada);
        if( i == 1 ) // ya que si son iguales tambien debo hacer el burbujeo, ESTO PARA MIN HEAP YA QUE LA FUNCION DE COMPARACION SERIA FASCENDENTE Y TENGO QUE INTERCAMBIAR CUANDO ES -1
        {
            intercambiar(nuevo,nuevo->padre);
            burbujeoHaciaArriba(cola,nuevo->padre);
        }

    }

}


/** Este metodo provocara que el heap no rompa la propiedad de orden que debe cumplir
*   El parametro r hace referencia a la raiz del heap, la entrada de este es lo que valia el ultimo nodo
*   Si la cola tiene solo un nodo (la raiz),entonces la propiedad de ordenesta trivialmente satisfecha
*/
void downHeap(TColaCP cola, TNodo r)
{

    if(r != NULL && r->hijo_izquierdo != NULL && r->hijo_derecho != NULL)
    {
        /** La prioridad del hijo izquierdo de la raiz es mayor que la de su hijo derecho */
        if( cola->comparador(r->hijo_izquierdo->entrada,r->hijo_derecho->entrada) == 1)
        {
            intercambiar(r->hijo_izquierdo,r); /** PRIMER PARAMETRO HIJO, SEGUNDO PADRE */
            downHeap(cola,r->hijo_izquierdo);
        }
        else
        {
            /** La prioridad del hijo derecho de la raiz es mayo que la de su hijo izquierdo */
            if( cola->comparador(r->hijo_izquierdo->entrada,r->hijo_derecho) == -1)
            {
                intercambiar(r->hijo_derecho,r);
                downHeap(cola,r->hijo_derecho);
            }
        }
    }
    else
    {
        /** LA RAIZ SOLO TIENE HIJO IZQUIERDO */
        if(r->hijo_izquierdo != NULL)
        {
            if(cola->comparador(r->hijo_izquierdo->entrada,r->entrada) == 1)
            {
                intercambiar(r->hijo_izquierdo,r);
                //ACA ESTABA EL ERROR ESTABA LLAMANDO RECURSIVAMENTE Y EN ESTE CASO NO ERA NECESARIOO !
            }
        }
    }

}

/**
 * Si la cola no tenia elementos, entonces agregara uno nuevo con la entrada entr pasada por parametro.
 * Caso contrario utilizara la funcion buscarNodo para encontrar a su padre(que es de donde debe engancharse como hijo)
 * Luego si la propiedad de orden del heap se rompe, Burbujeara hacia arriba hasta llegar a la raiz en el peor caso.
 */
int cp_insertar(TColaCP cola, TEntrada entr)
{
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
    }
    else  // LA COLA TIENE MAS DE UN ELEMENTO
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
        }
        else
        {
            padreNuevo->hijo_derecho = nuevo;
        }

        burbujeoHaciaArriba(cola,nuevo);

        cola->cantidad_elementos = cola->cantidad_elementos + 1 ;

    }

    return TRUE;
}

/**
 * Eliminara de la cola la entrada con mayor prioridad, el nodoMasProfundo del arbol sera el que reemplaze momentaneamente a la raiz
 * y burbujeara hacia abajo si rompe la propiedad de orden del heap. El metodo buscarNodo, busca la posicion del padre del nodo a eliminar.
 * al ir burbujeando hacia abajo, en la implementacion se iran cambiando las entradas de los nodos .
 */
TEntrada cp_eliminar(TColaCP cola)
{
    if(cola == POS_NULA)
    {
        printf("Error cola NULA al intentar eliminar \n");
        exit(CCP_NO_INI);
    }

    TEntrada entradaAEliminar = NULL;
    if(cola->cantidad_elementos == 1) /** FALTARIA HACER ALGUN FREE ADENTRO DE ESTE IF ? */
    {
            entradaAEliminar = cola->raiz->entrada;
            cola->raiz = NULL;
            cola->cantidad_elementos = cola->cantidad_elementos - 1 ;
            return entradaAEliminar;
    }

    TNodo nodoMasProfundo = POS_NULA;
    //TEntrada entradaAEliminar = NULL;
    entradaAEliminar = cola->raiz->entrada; /** ME GUARDO EN UNA VARIABLE AUXILIAR PARA NO PERDER LA ENTRADA QUE QUIERO ELIMINAR */
    nodoMasProfundo = buscarNodo(cola,cola->cantidad_elementos);
    cola->raiz->entrada = nodoMasProfundo->entrada;


    TNodo padreDeNodoMasProfundo = nodoMasProfundo->padre;

    if(padreDeNodoMasProfundo->hijo_izquierdo == nodoMasProfundo)
        padreDeNodoMasProfundo->hijo_izquierdo = NULL;
    else
        padreDeNodoMasProfundo->hijo_derecho = NULL;

    nodoMasProfundo->padre = NULL;
    free(nodoMasProfundo); /** A ESTA ALTURA LO QUE HICE FUE CAMBIAR LA ENTRADA DEL ULTIMO NODO EN LA RAIZ Y LUEGO ELIMINAR EL ULTIMO NODO.FALTA BURBUJEAR HACIA ABAJO */


    downHeap(cola,cola->raiz);



    cola->cantidad_elementos = cola->cantidad_elementos - 1;
    return entradaAEliminar;
}

/** Recorrera la ccp en posOrden IZQUIERDO-DERECHO-RAIZ */
void posOrden(TColaCP cola,TNodo r)
{
    if(r != NULL)
    {
        posOrden(cola,r->hijo_izquierdo);
        posOrden(cola,r->hijo_derecho);
        TEntrada t = r->entrada;
        //printf("%d ",*(int*) t->clave); /** MUESTRA POR PANTALLA LA DESTRUCCION DE LA COLA EN POSORDEN */
        free(r);

    }
}

/**
 * Destruye los elementos de la cola en posOrden y libera toda la memoria siempre que tenga al menos un elemento.
 * Caso contrario aborta la ejecucion
 */
int cp_destruir(TColaCP cola)
{

    int salida = FALSE;
    if(cola == NULL)
    {
        exit(CCP_NO_INI);
    }

    if(cola->cantidad_elementos>0){
        posOrden(cola,cola->raiz);
        free(cola);
        salida = TRUE;
    }

    return salida ;
}

/**
 * Retorna la cantidad de elementos en la cola
 */
int cp_size(TColaCP cola)
{
    if(cola == NULL)
        exit(CCP_NO_INI);

    return cola->cantidad_elementos;
}





