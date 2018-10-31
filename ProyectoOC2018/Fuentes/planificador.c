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
    TCiudad ciudadOrigen = l_recuperar(listaDeCiudades,l_ultima(listaDeCiudades));
    printf("%.f;%.f\n",ciudadOrigen->pos_x,ciudadOrigen->pos_x);
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
    //printf("%.f;%.f\n",origen->pos_x,origen->pos_y); /** %.f me escribe como punto flotante con 1 caracter despues del punto decimal */
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
void mostrarAscendenteODescendente(TLista listaDeCiudades,TColaCP colaDeCiudades)
{
    TPosicion pos = l_ultima(listaDeCiudades);
    TCiudad ciudadOrigen = l_recuperar(listaDeCiudades,pos);
    TEntrada e = NULL;
    float posX = ciudadOrigen->pos_x;
    float posY = ciudadOrigen->pos_y;
    //printf("origen x: %.f y: %.f\n",ciudadOrigen->pos_x,ciudadOrigen->pos_y);
    l_eliminar(&listaDeCiudades,pos);


    while(l_size(listaDeCiudades)>0)
    {
        e = malloc(sizeof(struct entrada));
        e->clave = malloc(sizeof(float));

        TCiudad ciudadDestino = l_recuperar(listaDeCiudades,l_ultima(listaDeCiudades));

        float d = abs((float)(ciudadDestino->pos_x - posX) ) + abs((float)(ciudadDestino->pos_y - posY)) ;
        *(float *)e->clave = d ;
       // printf("%.f \n",d);
        e->valor = ciudadDestino;
        cp_insertar(colaDeCiudades,e);
        l_eliminar(&listaDeCiudades,l_ultima(listaDeCiudades));

    }

    int i =0 ;
    for(i= 0 ; cp_size(colaDeCiudades)>0; i++)
    {
        TEntrada e = cp_eliminar(colaDeCiudades);
        TCiudad city = e->valor;
        printf("%d. %s\n",i+1,city->nombre);

    }

    free(e->clave);
    free(e);
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
    TLista listaParaColaDescendente = crear_lista();
    TColaCP colaDeCiudades = crear_cola_cp(&fAscendente);
    TColaCP colaDescendente = crear_cola_cp(&fDescendente);

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
        printf("---------------------------------------------\n");
        printf("Mostrar ascendente: \n");
        mostrarAscendenteODescendente(listaDeCiudades,colaDeCiudades);
        leerArchivo(punteroATxt,&listaParaColaDescendente);
        printf("---------------------------------------------\n");
        printf("Mostrar descedente: \n");
        mostrarAscendenteODescendente(listaParaColaDescendente,colaDescendente);
        printf("---------------------------------------------\n");
        printf("Reducir horas manejo: \n");


    }







    return 0;
}
