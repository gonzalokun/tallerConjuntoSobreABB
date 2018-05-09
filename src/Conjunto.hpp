#include <vector>

// Constructor usando la lista de inicializacion
// Voy a calcular la cardinalidad del conjunto a medida que lo construyo asi no hace falta recorrerlo para contarlos
template <class T>
Conjunto<T>::Conjunto() : _cantidadElementos(0), _raiz(nullptr) {
    //
}

// Borra todos los nodos de la memoria
template <class T>
Conjunto<T>::~Conjunto() {
    // Creo una lista de punteros a los elementos
    std::vector<Nodo*> nodosEnLista;

    // Agarro el menor elemento
    T valorActual = minimo();

    // Agrego los punteros de los nodos que contienen los elementos a la lista
    while(valorActual != maximo()){

        nodosEnLista.push_back(buscar(valorActual));

        valorActual = siguiente(valorActual);
    }

    // Agrego el maximo (que no se deberia haber agregado antes)
    nodosEnLista.push_back(buscar(valorActual));

    // Ahora recorro la lista de punteros y libero todo
    for(int i = 0; i < nodosEnLista.size(); i++){

        nodosEnLista[i]->der = nullptr;
        nodosEnLista[i]->izq = nullptr;
        nodosEnLista[i]->padre = nullptr;

        delete nodosEnLista[i];
    }

    // Se deberian haber borrado todos los elementos
}

// Busca un elemento y te devuelve el puntero al nodo que lo contiene
// Si no lo encuentra devuelve el puntero nulo
template <class T>
typename Conjunto<T>::Nodo* Conjunto<T>::buscar(const T& elem) const {
    Nodo* nodoBuscado = nullptr;

    Nodo* nodoActual = _raiz;

    // Buscamos por todo el arbol empezando desde la raiz
    while(nodoActual != nullptr){

        // Si el valor actual es el ingresado, entonces pertenece y nos vamos del ciclo
        if(nodoActual->valor == elem){
            nodoBuscado = nodoActual;

            // Pongo el valor del nodo en nulo asi salgo del ciclo
            nodoActual = nullptr;
        }

        else{
            //No es el valor, tengo que ver por cual rama avanzo

            //Si la clave es mas chica, hay que recorrer la izquierda, sino recorro por la derecha
            if(nodoActual->valor > elem){
                nodoActual->izq;
            }

            else{
                nodoActual->der;
            }
        }

    }

    return nodoBuscado;
}

// Indica si el elemento ingresado pertenece al conjunto
template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    bool perteneceAlConjunto = false;

    Nodo* nodoActual = _raiz;

    // Buscamos por todo el arbol empezando desde la raiz
    while(nodoActual != nullptr){

        // Si el valor actual es el ingresado, entonces pertenece y nos vamos del ciclo
        if(nodoActual->valor == clave){
            perteneceAlConjunto = true;

            // Pongo el valor del nodo en nulo asi salgo del ciclo
            nodoActual = nullptr;
        }

        else{
            //No es el valor, tengo que ver por cual rama avanzo

            //Si la clave es mas chica, hay que recorrer la izquierda, sino recorro por la derecha
            if(nodoActual->valor > clave){
                nodoActual->izq;
            }

            else{
                nodoActual->der;
            }
        }

    }

    return perteneceAlConjunto;
}

// Inserta nuevos elementos
// SUPONGO QUE: no me van a dar uno repetido, o sea es un conjunto (PREGUNTAR POR LAS DUDAS)
template <class T>
void Conjunto<T>::insertar(const T& clave) {

    // Creamos el nodo en memoria
    Nodo* nuevoNodo = new Nodo(clave);

    // Si la raiz del arbol es nula, entonces es el primer elemento del árbol
    if(_raiz == nullptr){
        // Es el primer elemento agregado
        // Apunto la raiz al elemento
        _raiz = nuevoNodo;
    }

    else{
        // No es el primer elemento agregado
        // Recorro el arbol hasta encontrar el lugar donde poner el nodo

        Nodo* nodoActual = _raiz;
        Nodo* nodoAnterior = _raiz;

        while(nodoActual != nullptr){

            //Si el valor nuevo es menor, tengo qeu ir por la izquierda, sino voy por la derecha
            if(nodoActual->valor > nuevoNodo->valor){
                nodoAnterior = nodoActual;
                nodoActual = nodoActual->izq;
            }

            else{
                nodoAnterior = nodoActual;
                nodoActual = nodoActual->der;
            }
        }

        // Ahora nodoAnterior tiene al padre correcto, me fijo en que rama agregarlo

        if(nodoAnterior->valor > nuevoNodo->valor){
            // Va en la rama izquierda
            nodoAnterior->izq = nuevoNodo;

            // Le indico al nuevo nodo cual es su padre
            nuevoNodo->padre = nodoAnterior;
        }

        else{
            // Va en la rama derecha
            nodoAnterior->der = nuevoNodo;

            // Le indico al nuevo nodo cual es su padre
            nuevoNodo->padre = nodoAnterior;
        }

    }

    // Aumento la cantidad en uno
    _cantidadElementos++;
}

// Remueve el nodo con el elemento ingresado
template <class T>
void Conjunto<T>::remover(const T& elem) {
    // Obtengo el nodo a borrar
    Nodo* nodoABorrar = buscar(elem);

    //Si es hoja, entonces simplemente anulo la coneccion con el padre y lo borro
    if(esHola(elem)){
        // Tengo que saber si vino de una rama izquierda o derecha

        if(nodoABorrar->padre->izq == nodoABorrar){
            // Vino de rama izquierda
            nodoABorrar->padre->izq = nullptr;
        }

        else{
            // Vino de rama derecha
            nodoABorrar->padre->der = nullptr;
        }

        // Borro el nodo
        delete nodoABorrar;
    }
    else{
        // Puede tener una rama, dos ramas o ser la raiz

        // Si tiene una rama
        if((nodoABorrar->der != nullptr && nodoABorrar->izq == nullptr) || (nodoABorrar->der == nullptr && nodoABorrar->izq != nullptr)){
            //Hay que ver vino rama derecha o izquierda y si la rama hija es izquierda o derecha

            Nodo* nodoHijo = (nodoABorrar->izq != nullptr) ? nodoABorrar->izq : nodoABorrar->der;
            Nodo* nodoPadre = nodoABorrar->padre;

            if(nodoPadre->izq == nodoABorrar){
                // Vino de rama izquierda

                nodoPadre->izq = nodoHijo;
                nodoHijo->padre = nodoPadre;
            }

            else{
                // Vino de rama derecha

                nodoPadre->der = nodoHijo;
                nodoHijo->padre = nodoPadre;
            }

            delete nodoABorrar;
        }

        else{
            //Tiene dos ramas
        }
    }

    // Finalmente le resto uno a la cantidad
    _cantidadElementos--;
}

// Devuelve el elemento que le sigue al ingresado
template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    // Obtengo el nodo que tiene el elemento al cual le quiero encontrar el siguiente

    T valorDeseado;

    Nodo* nodoActual = buscar(clave);

    //Ahora, si hay subárbol derecho tendo que encontrarle el menor
    if(nodoActual->der != nullptr){
        //Hay subarbol derecho

        //Busco el menor
        Nodo* minimoNodo = nodoActual->der;

        while(minimoNodo->izq != nullptr){
            minimoNodo = minimoNodo->izq;
        }

        // minimoNodo ahora apunta al menor
        valorDeseado = minimoNodo->valor;
    }

    else{
        //No hay subarbol, hay que subir hasta encontrar un nodo tal que se haya provenido de una rama izquierda
        Nodo* siguiente = nodoActual->padre;

        // No deberia pasar que (siguiente->padre != nullptr) pero lo pongo por las dudas
        while(siguiente->padre != nullptr && siguiente->der == nodoActual){
            nodoActual = nodoActual->padre;
            siguiente = nodoActual->padre;
        }

        // Si sali entonces es porque vine de una rama izquierda, entonces siguiente apunta al valor que quiero
        valorDeseado = siguiente->valor;
    }

    return valorDeseado;
}

// Dice si un elemento es hoja o no
// Solo se le pueden pasar cosas del arbol!!!!
template <class T>
bool Conjunto<T>::esHola(const T &elem) const {
    bool elElementoEsHoja = true;

    // Obtengo el puntero del nodo que contiene al elemento
    Nodo* nodoDeseado = buscar(elem);

    // Si alguna de las ramas no es nula, entonces no es una hoja
    if(nodoDeseado->izq != nullptr || nodoDeseado->der != nullptr){
        elElementoEsHoja = false;
    }

    return elElementoEsHoja;
}

template <class T>
const T& Conjunto<T>::minimo() const {
    // Recorro el arbol agarrando siempre el elemento de la izquierda

    Nodo* nodoActual = _raiz;

    while(nodoActual->izq != nullptr){
        nodoActual = nodoActual->izq;
    }

    // Ahora nodoActual deberia apuntar al menor elemento, asi que lo devuelvo
    return nodoActual->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    // Recorro el arbol agarrando siempre el elemento de la derecha

    Nodo* nodoActual = _raiz;

    while(nodoActual->der != nullptr){
        nodoActual = nodoActual->der;
    }

    // Ahora nodoActual deberia apuntar al menor elemento, asi que lo devuelvo
    return nodoActual->valor;
}

// Devuelvo la cantidad de elementos que fui acumulando a medida que se fue armando el conjunto
template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return _cantidadElementos;
}

//OPCIONAL !!!!!!!
template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    //
}

