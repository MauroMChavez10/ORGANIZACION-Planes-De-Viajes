#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "constantes.h"



/**
 * Crea una lista doblemente enlazada vacía . Sin centinelas
 */
TLista crear_lista()
{
    return POS_NULA;    /** SOLO ESTO PORQUE SI PIDO MEMORIA PARA GUARDAR UNA STRUCT CELDA ESTOY HACIENDO UN CENTINELA Y ESTA MAL */

}

/**
 * Este metodo considerara varios casos al momento de insertar un nuevo elemento en la lista
 * CASO 1 : Si la lista no fue creada previamente, debe abortar la ejecucion
 * CASO 2 : SE CREO LA LISTA VACIA PREVIAMENTE Y NO HABIA ELEMENTOS ANTES
 * CASO 3 : La lista tenia al menos un elementos antes
 * CASO 4 : LA NUEVA CELDA QUEDARA ENTRE MEDIO DE DOS CELDAS
 */
int l_insertar(TLista * lista, TPosicion pos, TElemento elem)
{
    if(lista == POS_NULA)
        exit(LST_NO_INI);

    int salida = TRUE;
    TPosicion nueva = (TPosicion)  malloc(sizeof(struct celda));

    if( nueva != NULL)
    {
        if(pos == POS_NULA && *lista == POS_NULA) /** Caso 2 */
        {
            nueva->elemento = elem;
            nueva->celda_anterior = POS_NULA;
            nueva->celda_siguiente = POS_NULA;
            *lista = nueva;
            salida = TRUE;
        }
        else
        {
            if( pos == *lista || (pos == POS_NULA && *lista != POS_NULA)) /** CASO 3 */
            {
                nueva->elemento = elem;
                nueva->celda_anterior = POS_NULA;
                nueva->celda_siguiente = *lista;
                TLista exPrimera = *lista;
                exPrimera->celda_anterior = nueva;
                *lista = nueva;
                salida = TRUE;
            }
            else  /** 4 CASO  */
            {
                if( pos != POS_NULA && *lista != POS_NULA)
                {
                    TPosicion celdaAnterior = pos->celda_anterior;
                    celdaAnterior->celda_siguiente = nueva;
                    nueva->celda_anterior = celdaAnterior;
                    nueva->celda_siguiente = pos ;
                    pos->celda_anterior = nueva;
                    nueva->elemento = elem;
                    salida = TRUE;
                }
            }
        }
    }
    else
        salida = FALSE;

    return salida ;
}


/**
 * Si la lista pasada por parametro no esta inicializada, la cantidad de elementos es 0
 * Caso contrario, recorro cada uno de los elementos de la lista y aumento cantidad de elementos en uno.
 */
int l_size(TLista lista)
{
    if(lista == POS_NULA)
        return FALSE;

    int cant = 0;
    TPosicion pos = lista;

    while(pos != POS_NULA)
    {
        cant ++ ;
        pos = (pos->celda_siguiente);
    }

    return cant ;
}

/**
 *   Retorna la primer posicion de la lista, si la lista es vacia retorna POS_NULA
 */
TPosicion l_primera(TLista lista)
{

    return lista;

}

/**
 *   Retorna la ultima posicion de la lista, si la lista es vacia retorna POS_NULA
 */
TPosicion l_ultima(TLista lista)
{
    TPosicion ultima = POS_NULA;


    TPosicion pos = lista;

    while(pos != POS_NULA)
    {
        if (pos->celda_siguiente == POS_NULA)
            ultima = pos;

        pos = pos->celda_siguiente;
    }

    return ultima;


}


TPosicion l_anterior(TLista lista, TPosicion pos)
{
    return pos->celda_anterior;

}


TPosicion l_siguiente(TLista lista, TPosicion pos)
{

    return pos->celda_siguiente;
}

TElemento l_recuperar(TLista lista, TPosicion pos)  /** Recibe como parametro un puntero*/
{

    if(lista == POS_NULA)
    {
        exit(LST_NO_INI);
    }

    if(pos == POS_NULA)
    {
        return ELE_NULO;
    }else
        return pos->elemento;



}


int l_eliminar(TLista * lista, TPosicion pos)
{
    int salida = FALSE;
    if(lista == POS_NULA)
        exit(LST_NO_INI);
    //printf("%d Elemento eliminado : \n", *(int*) pos->elemento);

    if(*lista == pos) /** PUEDEN SUCEDER DOS COSAS CON ESTA CONDICION, O SOLO HAY UN ELEMENTO EN LA LISTO O HAY MAS DE UNO */
    {
        if(l_size(*lista) > 1)
        {
            *lista = pos->celda_siguiente;
            pos->celda_anterior = POS_NULA;
            pos->celda_siguiente->celda_anterior = POS_NULA;
            pos->celda_siguiente = POS_NULA;
            salida = TRUE;
        }
        else
        {
            if(l_size(*lista) == 1)
            {
                *lista = POS_NULA;
                salida = TRUE;
            }
        }
    }
    else
    {
        if(*lista != pos && (pos->celda_siguiente == POS_NULA))
        {
            TPosicion nuevaUltima = pos->celda_anterior;
            pos->celda_anterior = POS_NULA;
            nuevaUltima->celda_siguiente = POS_NULA;

        }
        else
        {
            if(*lista != pos && pos->celda_siguiente != POS_NULA) /** 4 caso pos apunta a una celda que tiene dos al costado */
            {
                TPosicion siguiente = pos->celda_siguiente;
                TPosicion anterior = pos->celda_anterior;
                anterior->celda_siguiente = siguiente;
                siguiente->celda_anterior = anterior;
                pos->celda_anterior = POS_NULA;
                pos->celda_anterior = POS_NULA;
            }
        }



    }

    free(pos);

    return salida;

}

/**
 * Si la lista pasada por parametro no esta inicializada, aborta la ejecucion
 * Caso contrario, recorro la lista pero cada vez que avanzo de posicion p, libero la memoria que ocupa..
 * Por ultimo libero la memoria de *lista que es la referencia al primer elemento de la lista
 */
int l_destruir(TLista * lista)
{
    int salida= FALSE;

    if(lista == POS_NULA)
        exit(LST_NO_INI);

    TPosicion p = *lista;

    while (p->celda_siguiente != POS_NULA)
    {
        p = *lista;
        *lista = p->celda_siguiente;
        free(p);
        //free(p);
    }

    free(*lista);
    salida = TRUE;
    return salida;
}






