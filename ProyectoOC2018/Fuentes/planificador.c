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
int distanciaDeManhattan(TCiudad primerCiudad,TCiudad segundaCiudad)
{
    return (abs((segundaCiudad->pos_x)+ (primerCiudad->pos_x)) - ((segundaCiudad->pos_y)-(primerCiudad->pos_y))) ;

}


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

void mostrarNombreCiudad(char *nombreCiudad,int longitudCiudad,float px,float py)
{
     int i = 0;
        for(i = 0 ; i< longitudCiudad; i++)
            printf("%c",*(nombreCiudad+i));

    printf(";%.f;%.f\n",px,py);

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
    char *nombreCiudad;
    //char direccion[80];
    FILE *fd;

    char  direccion [] = "/home/alumno/Escritorio/ProyectoOC2018/viajes.txt";

    fd = fopen(direccion,"r");

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

    while (!feof(fd)){
        nueva = malloc(sizeof(struct ciudad));
        nombreCiudad = nueva->nombre;
        nombreCiudad = malloc(50*sizeof(char));
        fscanf(fd,"%[^;];",nombreCiudad);
        //printf("long ciudad = %d\n",strlen(nombreCiudad)+1); esta bien esta longitud ?
        fscanf(fd,"%d;",&x);
        nueva->pos_x = x;
        fscanf(fd,"%d\n",&y);
        nueva->pos_y = y;

        //mostrarNombreCiudad(nombreCiudad,strlen(nombreCiudad)+1,nueva->pos_x,nueva->pos_y);
        //printf(" %c  ",(*nombreCiudad));
        //printf(" %c \n",(*nombreCiudad)+1); /** PERFECTO ME ESTA GUARDANDO EN LA PRIMER COMPONENTE LA PRIMER LETRA DE CADA CIUDAD */
        //printf("nueva x: %.f y: %.f\n",nueva->pos_x,nueva->pos_y);
        l_insertar(&listaDeCiudades,pos,nueva);
        mostrarNombreCiudad(nombreCiudad,strlen(nombreCiudad)+1,nueva->pos_x,nueva->pos_y);
        //TCiudad city1 = l_primera(*lista)->elemento;
        //printf("Primer pos x : %.f\n",city1->pos_x);

    }

    //*lista = listaDeCiudades;
    //TCiudad city = l_primera(*lista)->elemento;
    //printf("pos x en listadeciudades %.f",city->pos_x);
    //fscanf(archivo,"%d:%d\n",&x,&y); PARA FORMAR LA CIUDAD
    //fscanf(archivo,"%[^;];",nombre)
    //fscanf(archivo,"%d;",&x);/** CONSUMO HASTA EL PUNTO Y COMA. LO SALTEA
    //fscanf(archivo,"%d\n",&y);
    //*lista = listaDeCiudades;
    *lista = listaDeCiudades; /** NO ME DEJA USAR LA LISTA QUE LLENE !! */
    fclose(fd);
    //*lista = listaDeCiudades;

}

//void menu()
//{
    //mostrarCiudadesAscendente();
    //mostrarCiudadesDescendente();
    //reducirHorasManejo();

//}



int main(int argc, char ** arreglo)
{

    TLista lista = crear_lista();
    int a = 5;
    int b = 6;
    int g = 10;
    int d = 30;
    int e = 70;
    void *pA, *pB, *pG,*pD,*pE;

    pA = &a;
    pB = &b;
    pG = &g;
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

    l_insertar(&lista,ultimaPosicion,pG);





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

    int pudeDestruir = l_destruir(&lista);
    if( pudeDestruir )
        printf("Pude destruir toda la lista, la cantidad de elementos es : %d\n",l_size(lista));
    else
        printf("No pude destruir toda la lista, la cantidad de elementos es : %d\n",l_size(lista));



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

    if(destruccion == 1)
        printf("Se pudo destruir correctamente la Cola con prioridad \n");
    else
        printf("No se pudo destruir correctamente la Cola con prioridad \n");
    printf("La cantidad de elementos luego de destruir la cola es : %d\n",cp_size(ccp));

    //printf("La Cola con Prioridad luego de destruir todos los elementos es : \n"); /** NO SE PUEDE MOSTRAR LA COLA CON PRIORIDAD YA QUE SE DESTRUYO Y TIRA SEGMENTATION FAULT */
    //mostrarCCP(ccp,ccp->raiz);

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




    /** ---------------- PROGRAMA PRINCIPAL ------------------- */

    printf("\n      PROGRAMA PRINCIPAL   \n" );

    /** PARA LEER POR CONSOLA EL ARCHIVO TXT */
    TLista listaDeCiudades = NULL;

    //if (argc == 1) /** NO RECIBI EL TXT */
        //exit(1);
    //else
        //if( argc == 2)
        //{
            //char * punteroATxt = arreglo[1]; /** arreglo[1] es "fede.txt" */
            //leerArchivo(punteroATxt, &listaDeCiudades);
            //printf("cant ciudades en listaDeCiudades :%d\n",l_size(listaDeCiudades));
        //}


    leerArchivo("hola",&listaDeCiudades); /** ENVIARLE UN PUNTERO A TLISTA ! ASI VEO EL CAMBIO */

    TCiudad c1 = l_ultima(listaDeCiudades);
    //mostrarNombreCiudad(c1->nombre,strlen(c1->nombre)+1,c1->pos_x,c1->pos_y); //COMO NO ME COPIO EL NOMBRE NI LAS POSICIONES NO MUESTRA NADA . SINO SI ANDARIA //

    /** NO ME DEJA USAR LA LISTA FUERA DEL MAIN */


    return 0;
}
