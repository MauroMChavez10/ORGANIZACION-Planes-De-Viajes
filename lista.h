#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

typedef void * TElemento;
typedef struct celda *TLista;
typedef struct celda *TPosicion;

struct celda{
    TElemento elemento;
    struct celda * celda_anterior;
    struct celda * celda_siguiente;
};
/**
    Crea y retorna una lista vacía.
*/
TLista crear_lista();

/**
    Agrega el elemento elem en la posición pos, dentro de la lista.
    Si pos es POS_NULA, inserta el elemento en la primera posición de la lista.
    Retorna verdadero si procede con éxito , falso en caso contrario.
*/
int l_insertar(TLista * lista, TPosicion pos, TElemento elem);

/**
    Elimina el elemento en la posición pos. Reacomoda la lista adecuadamente. Retorna verdadero si procede con éxito, falso en caso contrario.
*/
int l_eliminar(TLista* lista, TPosicion pos);

/**
    Retorna la primera posición de la lista. Si la lista es vacía, retorna POS_NULA
*/
TPosicion l_primera(TLista lista);

/**
    Retorna la última posición de la lista. Si la lista es vacía, retorna POS_NULA
*/
TPosicion l_ultima(TLista lista);

/**
    Retorna la posición anterior a pos en la lista lista. Si pos es la primera posicion de la lista, retorna POS_NULA.
*/
TPosicion l_anterior(TLista lista, TPosicion pos);

/**
    Retorna la posición siguiente a pos en la lista lista. Si pos es la última posición de la lista, retorna POS_NULA.
*/
TPosicion l_siguiente(TLista lista, TPosicion pos);

/**
    Retorna el elemento correspondiente a la posición pos. Si la posición es POS_NULA, retorna ELE_NULO.
*/
TElemento l_recuperar(TLista lista, TPosicion pos);

/**
    Retorna la cantidad de elemento de la lista.
*/
int l_size(TLista lista);

/**
    Elimina todos los elemento y libera toda la memoria utilizada por la lista lista. Retorna verdadero si procede con éxito, falso en caso contrario.
*/
int l_destruir(TLista *lista);



#endif // LISTA_H_INCLUDED
