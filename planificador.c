#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "constantes.h"
#include "colacp.h"
#include <string.h>


typedef struct ciudad
{
    char *nombre;
    float pos_x;
    float pos_y;
} *TCiudad;

/** Este metodo computa la distancia entre dos ciudades */
float distanciaDeManhattan(TCiudad ciudadOrigen,TCiudad ciudadDestino)
{
    return abs((float)ciudadDestino->pos_x- ciudadOrigen->pos_x) + abs((float)ciudadDestino->pos_y-ciudadOrigen->pos_y);

}


/**
    Si el primer argumento pasado a la funcion fAscendente es menor al segundo, retorna -1.
    Si ambos argumentos son iguales retorna 0.
    En otro caso 1
*/
int fAscendente(TEntrada a,TEntrada b)
{
    float salida;

    float * pa;
    pa = (float *)(a->clave);
    float *pb;
    pb = (float *)(b->clave);

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

    float * pa;
    pa = (float *)(a->clave);
    float *pb;
    pb = (float *)(b->clave);

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


void mostrarCiudades(TLista listaDeCiudades)
{
    int i = 0;
    TPosicion pos = l_anterior(listaDeCiudades,l_ultima(listaDeCiudades));
    for(i = 0; pos != NULL; i++)
    {
        TCiudad city = pos->elemento;
        printf("%s",city->nombre);

        printf(";%.f;%.f\n",city->pos_x,city->pos_y);

        //mostrarNombreCiudad(city->nombre,strlen(city),city->pos_x,city->pos_y);
        pos = l_anterior(listaDeCiudades,pos);
    }

}



/** Este metodo se encargara de recorrer el archivo, formando el nombre de cada ciudad y su respectiva posicion
    y añadiendolos a un listado de ciudades a visitar */
void leerArchivo(char * txt,TLista *lista)
{
    int x= 0.0;
    int y= 0.0;
    TCiudad origen = malloc(sizeof(struct ciudad));
    TCiudad nueva = POS_NULA;
    TLista listaDeCiudades = crear_lista();
    TPosicion pos = POS_NULA;
    char nombreCiudad[50];
    //char direccion[80];
    FILE *fd;



    fd = fopen(txt,"r");

    if(fd == NULL)
    {
        printf("Error al tratar de leer el archivo");
        exit(FALSE);
    }


    fscanf(fd,"%d;%d\n",&x,&y); /** ESTARIA LEYENDO EL FORMATO DE LA PRIMER CIUDAD */
    origen->pos_x = x;
    origen->pos_y = y;
    printf("%.f;%.f\n",origen->pos_x,origen->pos_y); /** %.f me escribe como punto flotante con 1 caracter despues del punto decimal */
    l_insertar(&listaDeCiudades,pos,origen);

    while (!feof(fd))
    {
        nueva = malloc(sizeof(struct ciudad));
        nueva->nombre = malloc(50*sizeof(char));
        fscanf(fd,"%[^;];",nombreCiudad);
        strcpy(nueva->nombre,nombreCiudad);
        fscanf(fd,"%d;",&x);
        nueva->pos_x = x;
        fscanf(fd,"%d\n",&y);
        nueva->pos_y = y;
        l_insertar(&listaDeCiudades,pos,nueva);
    }

    *lista = listaDeCiudades;
    fclose(fd);


}

/**
 * LLenara la colaDeCiudades con ciudades, donde la clave de su entrada sera la distancia entre la ciudad origen y la destino
 * y el valor sera la ciudad.
 */
void mostrarAscendente(TLista listaDeCiudades,TColaCP colaDeCiudades)
{
    TPosicion pos = l_ultima(listaDeCiudades);
    TCiudad ciudadOrigen = l_recuperar(listaDeCiudades,pos);
    TPosicion p = l_primera(listaDeCiudades);
    TEntrada e = malloc(sizeof(struct entrada));
    e->clave = malloc(sizeof(float));
    printf("origen x: %.f y: %.f\n",ciudadOrigen->pos_x,ciudadOrigen->pos_y);

    while(p != NULL)
    {
        TCiudad ciudadDestino = p->elemento;

        *(float *)(e->clave) = distanciaDeManhattan(ciudadOrigen,ciudadDestino);
        printf("Destino x: %.f y: %.f\n",ciudadDestino->pos_x,ciudadDestino->pos_y);
        printf("%.f \n",distanciaDeManhattan(ciudadOrigen,ciudadDestino));
        e->valor = ciudadDestino;
        cp_insertar(colaDeCiudades,e);
        p = l_siguiente(listaDeCiudades,p);
    }

    //TEntrada eliminada = cp_eliminar(colaDeCiudades);
    //printf("%.f distancia ",*(float*)eliminada->clave);
}

void menu()
{

    //mostrarCiudadesAscendente();
    //mostrarCiudadesDescendente();
    //reducirHorasManejo();

}



int main(int argc, char ** arreglo)
{

    /** ---------------- PROGRAMA PRINCIPAL ------------------- */

    printf("\n      PROGRAMA PRINCIPAL   \n" );

    /** PARA LEER POR CONSOLA EL ARCHIVO TXT */
    TLista listaDeCiudades = crear_lista();
    TColaCP colaDeCiudades = crear_cola_cp(&fAscendente);

    if (argc != 2) /** NO RECIBI EL TXT */
    {
        printf("Se aborto la ejecucion porque no se recibio el txt");
        exit(1);
    }
    else if( argc == 2)
    {
        char * punteroATxt = arreglo[1]; /** arreglo[1] es "fede.txt" */
        leerArchivo(punteroATxt, &listaDeCiudades);
        mostrarCiudades(listaDeCiudades);
        printf("---------------------------------------------\n\n");
        printf("Mostrar ascendente: \n");
        mostrarAscendente(listaDeCiudades,colaDeCiudades);

    }







    return 0;
}
