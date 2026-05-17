#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/pila.h"
#include "pila.h"

Pila* crearPila(){
         Pila* p = (Pila*)malloc(sizeof(Pila));
         if (p == NULL){
                 return NULL;
         } 
         p-> tope = NULL;
         return p;
}

void push(Pila* p, void *dato, size_t size){
         if (p == dato == NULL) return;

         nodoPila* nuevo = (nodoPila*)malloc(sizeof(nodoPila));
         if (nuevo == NULL) return;

         nuevo-> dato = malloc(size);
         if(nuevo->dato == NULL){
                 free(nuevo);
                 return;
         }

         memcpy(nuevo->dato, dato, size);

         nuevo->siguiente = p->tope;
         p->tope = nuevo;        
}

char pop(Pila* p){
         if(pilaVacia(p)){
         return "\0"
         }

         nodoPila* nodoAux = p->tope;
         p->tope = p->tope->siguiente;

         char valor= *(char*)(nodoAux->dato);

         free(nodoAux->dato);
         free(nodoAux);

         return valor;
}

char peek(Pila* p){
         if(pilaVacia(p)){
                 return "\0";
         }
         return *(char*)(p->tope->dato);
}

int pilaVacia(Pila* p){
         return(p->tope==NULL);
}

void destruirPila(Pila* p){
         if (p==NULL) return;

         while(!pilaVacia(p)){
                 pop(p);
         }
         free (p);
}