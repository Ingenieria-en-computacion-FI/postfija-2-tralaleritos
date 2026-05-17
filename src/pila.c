#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/pila.h"


Pila* crearPila(){
         Pila* p = (Pila*)malloc(sizeof(Pila));
         if (p == NULL){
                 return NULL;
         } 
         p-> tope = NULL;
         return p;
}

void push(Pila* p, void *dato, size_t size){
         if (p == NULL || dato == NULL) return;

         NodoPila* nuevo = (NodoPila*)malloc(sizeof(NodoPila));
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

void* pop(Pila* p){
         if(pilaVacia(p)){
         return NULL;
         }

         NodoPila* nodoAux = p->tope;
         p->tope = p->tope->siguiente;

         void* valor= nodoAux->dato;

         free(nodoAux);

         return valor;
}

void* peek(Pila* p){
         if(pilaVacia(p)){
                 return NULL;
         }
         return p->tope->dato;
}

int pilaVacia(Pila* p){
          return (p == NULL || p->tope == NULL);
}

void destruirPila(Pila* p){
         if (p==NULL) return;

         while(!pilaVacia(p)){
                 void* dato = pop(p);
                 free (dato)
         }
         free (p);
}