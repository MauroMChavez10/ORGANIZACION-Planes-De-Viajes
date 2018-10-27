#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "constantes.h"




TLista crear_lista(){
    return POS_NULA;    /** SOLO ESTO PORQUE SI PIDO MEMORIA PARA GUARDAR UNA STRUCT CELDA ESTOY HACIENDO UN CENTINELA Y ESTA MAL */

}

int l_insertar(TLista * lista, TPosicion pos, TElemento elem){ /** EL parametro lista es un puntero a un TLista, pero TLista a su vez es un puntero a struct celda. Por lo tanto
                                                                   el primer argumento espera un puntero a un puntero struct celda. */

    int salida = TRUE;
    TPosicion primera= *lista; /** LA VARIABLE PRIMERO GUARDA EL PRIMER ELEMENTO DE LA LISTA PARA NO DESCONECTAR EL RESTO DE LA LISTA */
    TPosicion nueva = (TPosicion)  malloc(sizeof(struct celda));

    if( nueva != NULL)
    {
        if(pos == POS_NULA && *lista == POS_NULA)
        {
            nueva->elemento = elem; /** COMO HAGO PARA QUE ACEPTE CUALQUIER TIPO SIN DESREFERENCIAR UN PUNTERO A VOID ? */
            nueva->celda_anterior = POS_NULA;
            nueva->celda_siguiente = POS_NULA;
            *lista = nueva;
            salida = TRUE;
        }
        else
        {   /** CASO EN EL QUE INSERTE Y LA LISTA PREVIAMENTE NO TENIA ELEMENTOS */
            if( pos == *lista || (pos == POS_NULA && *lista != POS_NULA))
            {
                nueva->elemento = elem;
                nueva->celda_anterior = POS_NULA;
                nueva->celda_siguiente = *lista;
                TLista exPrimera = *lista;
                exPrimera->celda_anterior = nueva;
                *lista = nueva;
                salida = TRUE;
            }else /** 3ER CASO : SE INSERTARA LA CELDA */
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
    }else
        salida = FALSE;

 return salida ;
}



int l_size(TLista lista){
    if(lista == POS_NULA)
        return FALSE;

    int cant = 0;
    TPosicion pos = lista;

    while(pos != POS_NULA){
        cant ++ ;
        pos = (pos->celda_siguiente);
    }

    return cant ;
}

TPosicion l_primera(TLista lista){
    if(lista == POS_NULA){
        //printf("la lista es nula");
    }

    return lista;

}

TPosicion l_ultima(TLista lista){
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


TPosicion l_anterior(TLista lista, TPosicion pos){
       return pos->celda_anterior;
}


TPosicion l_siguiente(TLista lista, TPosicion pos){

    return pos->celda_siguiente;
}

TElemento l_recuperar(TLista lista, TPosicion pos){ /** Recibe como parametro un puntero*/
    TElemento salida;
    if(lista == POS_NULA){
     exit(LST_NO_INI);
    }

    if(pos == POS_NULA){
        salida = ELE_NULO;
    }

    salida = pos->elemento;
    return salida ;



}


int l_eliminar(TLista * lista, TPosicion pos){
    int salida = FALSE;
    if(*lista == POS_NULA)
        exit(LST_NO_INI);
     //printf("%d Elemento eliminado : \n", *(int*) pos->elemento);

   if(*lista == pos){ /** Entonces es la primer celda */
        *lista = pos->celda_siguiente;
        pos->celda_siguiente->celda_anterior = POS_NULA;
        pos->celda_siguiente = POS_NULA;

        salida = TRUE;
    }else
    {
    if(pos->celda_siguiente == POS_NULA)
    { // ES EL ULTIMO ELEMENTO DE LA LISTA
        if(pos->celda_anterior != *lista){ // HAY AL MENOS 3 ELEMENTOS EN LA LISTA
            TPosicion celdaAnterior = pos->celda_anterior;
            celdaAnterior->celda_siguiente = POS_NULA;
            pos->celda_anterior = POS_NULA;
            salida = TRUE;
        }else // HAY 2 ELEMENTOS EN LA LISTA YA QUE EL ANTERIOR ES IGUAL A *LISTA Y EL SIGUIENTE ES NULO
        {
          //  printf("%d Elemento eliminado : \n", *(int*) pos->elemento);
            TPosicion celdaAnterior = pos->celda_anterior;
            TPosicion celdaSiguiente = pos->celda_siguiente;
            celdaAnterior->celda_siguiente = celdaSiguiente;
            celdaSiguiente->celda_anterior = celdaAnterior;
            pos->celda_anterior = POS_NULA;
            pos->celda_siguiente = POS_NULA;
            salida = TRUE;
        }

    }

    }

    free(pos);
    return salida;

}

int l_destruir(TLista * lista){
    int salida= FALSE;

    if(lista == POS_NULA)
        exit(LST_NO_INI);

    TPosicion p = *lista;

    while (p->celda_siguiente != POS_NULA){
            *lista = p->celda_siguiente;
            free(p); /** debo hacer los 2 free ? por los dos punteros o con el de p alcanza? */
    }

    salida = TRUE;
    return salida;
}






