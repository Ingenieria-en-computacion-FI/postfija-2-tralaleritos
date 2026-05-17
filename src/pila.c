#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
         if (p == NULL){
                 return;
         } 
         if(dato == NULL){
                 return;
         }

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

char pop(Pila* p){
         if(pilaVacia(p)){
                 return '\0';
         }

         NodoPila* tmp = p->tope;
         p->tope = p->tope->siguiente;

         char valor= *(char*)tmp->dato;

         free(tmp->dato);
         free(tmp);

         return valor;
}

char peek(Pila* p){
         if(pilaVacia(p)){
                 return '\0';
         }
         return *(char*)(p->tope->dato);
}

int pilaVacia(Pila* p){
          return (p->tope == NULL);
}

void destruirPila(Pila* p){
         if (p==NULL) return;

         while(!pilaVacia(p)){
                 void* dato = pop(p);
                 free (dato)
         }
         free (p);
}