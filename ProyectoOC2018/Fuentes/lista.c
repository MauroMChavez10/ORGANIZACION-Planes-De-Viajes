#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "constantes.h"




TLista crear_lista()
{
    return POS_NULA;    /** SOLO ESTO PORQUE SI PIDO MEMORIA PARA GUARDAR UNA STRUCT CELDA ESTOY HACIENDO UN CENTINELA Y ESTA MAL */

}


int l_insertar(TLista * lista, TPosicion pos, TElemento elem)
{
    if(lista == POS_NULA) /** Si la lista no fue creada previamente, debe abortar la ejecucion */
        exit(LST_NO_INI);

    int salida = TRUE;
    TPosicion nueva = (TPosicion)  malloc(sizeof(struct celda));

    if( nueva != NULL)
    {
        if(pos == POS_NULA && *lista == POS_NULA) /** CASO 2 : SE CREO LA LISTA VACIA PREVIAMENTE Y NO HABIA ELEMENTOS ANTES */
        {
            nueva->elemento = elem;
            nueva->celda_anterior = POS_NULA;
            nueva->celda_siguiente = POS_NULA;
            *lista = nueva;
            salida = TRUE;
        }
        else
        {
            if( pos == *lista || (pos == POS_NULA && *lista != POS_NULA))
            {
                nueva->elemento = elem;
                nueva->celda_anterior = POS_NULA;
                nueva->celda_siguiente = *lista;
                TLista exPrimera = *lista;
                exPrimera->celda_anterior = nueva;
                *lista = nueva;
                salida = TRUE;
            }
            else  /** 3ER CASO : LA NUEVA CELDA QUEDARA ENTRE MEDIO DE DOS CELDAS */
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

TPosicion l_primera(TLista lista)
{
    if(lista == POS_NULA)
    {
        //printf("la lista es nula");
    }

    return lista;

}

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
    if(*lista == POS_NULA)
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

int l_destruir(TLista * lista)
{
    int salida= FALSE;

    if(lista == POS_NULA)
        exit(LST_NO_INI);

    TPosicion p = *lista;

    while (p->celda_siguiente != POS_NULA)
    {

        *lista = p->celda_siguiente;
        free(p);
        //free(p);
    }

    salida = TRUE;
    return salida;
}






