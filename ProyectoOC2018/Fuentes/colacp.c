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
        //printf("%d asda\n",pos != NULL);
        if  (x % 2 == 0)
        {
            //printf("pos %d \n",*(int*)pos->entrada->clave);
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
         //printf("nuevo->padre->entrada->clave = %d\n",*(int*)nuevo->padre->entrada->clave);
         //printf("nuevo->entrada->clave = %d\n",*(int*)nuevo->entrada->clave);
       // printf(*(int*)(nuevo->entrada->clave));
        int i = cola->comparador(nuevo->entrada,nuevo->padre->entrada);
        if( i == 1 ) // ya que si son iguales tambien debo hacer el burbujeo, ESTO PARA MIN HEAP YA QUE LA FUNCION DE COMPARACION SERIA FASCENDENTE Y TENGO QUE INTERCAMBIAR CUANDO ES -1
        {
            intercambiar(nuevo,nuevo->padre);
            //printf("%d hola\n",*(int*)nuevo->padre->entrada->clave);
            burbujeoHaciaArriba(cola,nuevo->padre);
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
        padreNuevo = buscarNodo(cola,(numeroNodoAInsertar)/2); /** BUSCO A MI PADRE, PORQUE NUMERONODOAINSERTAR NO EXISTE TODAVIA */
        /** DEBO FIJARME LA PARIDAD DEL PADRE.. SI ES PAR, ES HIJO IZQUIERDO, SI ES IMPAR ES HIJO DERECHO */
        TNodo nuevo = malloc(sizeof(struct nodo));
        nuevo->padre = padreNuevo;

        nuevo->entrada = entr;
        nuevo->hijo_izquierdo = POS_NULA;
        nuevo->hijo_derecho = POS_NULA;




        //printf("%d \n",padreNuevo != NULL);
            if( padreNuevo->hijo_izquierdo == POS_NULA)
            {
                padreNuevo->hijo_izquierdo = nuevo;
            }else
            {
                padreNuevo->hijo_derecho = nuevo;
            }


            burbujeoHaciaArriba(cola,nuevo);


        //printf("Padre nuevo en insertar es : %d\n",*(int*)padreNuevo->entrada->clave);

           cola->cantidad_elementos = cola->cantidad_elementos + 1 ;


    }




    return TRUE;
}

TEntrada cp_eliminar(TColaCP cola);


int cp_destruir(TColaCP cola);

int cp_size(TColaCP cola){
    if(cola == NULL)
        exit(CCP_NO_INI);

    return cola->cantidad_elementos;
}





