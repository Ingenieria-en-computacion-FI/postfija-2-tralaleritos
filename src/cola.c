#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cola.h"

Cola* crearCola(){
      Cola* c = (Cola*)malloc(sizeof(Cola));
      if (c==NULL){
           return NULL;
      }
      c->frente = NULL;
      c->final = NULL;
      return c;
}

void enqueue(Cola* c, void *dato, size_t size){
      if(c == NULL){
           return;
      }
      if(dato == NULL){
           return;
      }
      NodoCola* nuevo = (NodoCola*)malloc(sizeof(NodoCola));
      if(nuevo = NULL){
           return;
      }
      memcpy(nuevo->dato, dato, size);
      nuevo->siguiente = NULL;
      if(colaVacia(c)){
           c->frente = nuevo;
      }else{
           c->final->siguiente = nuevo;
      }
      c->final = nuevo;
}

char dequeue(Cola* c){
      if (colaVacia(c)){
           return '\0';
      }
      NodoCola* tmp = c->frente;
      c->frente = c->frente->siguiente;
      if(c->frente == NULL){
           c->final== NULL;
      }
      char valor = *(char*)(tmp->dato);
      free(tmp->dato);
      free(tmp);
      return dato;
}

int colaVacia(Cola* c){
      return(c->frente = NULL);
}

void imprimirCola(Cola* c){
      if(colaVacia(c)){
           printf("\n");
           return;
      }
      NodoCola* actual = c->frente;
      while(actual != NULL){
           printf("%c ", *(char*)(actual->dato));
           actual = actual->siguiente;
      }
      printf("\n");
}

void destruirCola(Cola* c){
      if (c == NULL){
           return;
      }
      while(!colaVacia(c)){
           dequeue(c);
      }
      free(c);
}