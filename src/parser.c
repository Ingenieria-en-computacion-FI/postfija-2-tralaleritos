#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


#include "parser.h"
#include "pila.h"
#include "cola.h"

void cargarArchivo(
     const char* nombreArchivo,
     Variable variables[],
     int* totalVariables,
     char expresion[]
) {
     FILE* archivo = fopen(nombreArchivo, "r");
     if (archivo == NULL){
         printf("No es posible abrir el archivo\n");
         return;
     }
    char linea[256];
    *totalVariables = 0;

    while(fgets(linea, sizeof(linea), archivo)){
         linea[strcspn(linea, "\n")] = '0';
         if(strlen(linea) == 0){
             continue;
         }
         if(strchr(linea, '=')!= NULL){
             if(*totalVariables >= MAX_VARIABLES)continue;
             char* tokenVar = strtok(linea, "=");
             char* tokenVal = strtok(NULL, "=");
             if(tokenVar != NULL && tokenVal != NULL){
                 while(*tokenVar == ' ') tokenVar++;
                 variables[*totalVariables].nombre = *tokenVar;
                 variables[*totalVariables].valor = (float)atof(tokenVal);
                 (*totalVariables)++;
             }
         }else{
             int j = 0;
             for(int i = 0; linea[i] != '\0'; i++){
                 if(linea[i] != ' '){
                     expresion[j++] = linea [i];
                 }
             }
             expresion[j] = '\0';
         }
    }
     fclose(archivo);
}

int precedencia(char op){
     if(op == '^'){
         return 4;
     }
     if(op == '*' || op == '/'){
         return 3;
     }
     if(op == '+' || op == '-'){
         return 2;
     }
     return 0;
}

int esOperador(char c){
     return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

Cola* infijaAPostfija(char* expresion){
     Cola* colaSalida = crearCola();
     Pila* pilaOperadores = crearPila();
     if(colaSalida == NULL || pilaOperadores == NULL){
         return NULL;
     }
     for(int i = 0; expresion[i] != '\0'; i++){
         char token = expresion [i];
         if(isalpha(token)){
             enqueue(colaSalida, &token, sizeof(char));
         }
         else if(token == '('){
             push(pilaOperadores, &token, sizeof(char));
         }
         else if(token == ')'){
             while(!pilaVacia(pilaOperadores) && peek(pilaOperadores) != '('){
                 char opSaca = pop(pilaOperadores);
                 enqueue(colaSalida, &opSaca, sizeof(char));
             }
             if(!pilaVacia(pilaOperadores)){
                 pop(pilaOperadores);
             }
         }
         else if(esOperador(token)){
              while (!pilaVacia(pilaOperadores) && esOperador(peek(pilaOperadores))){
                 char opTope = peek(pilaOperadores);
                 if(token == '^'){
                    if(precedencia(opTope) > precedencia(token)){
                         char opSaca = pop(pilaOperadores);
                         enqueue(colaSalida, &opSaca, sizeof(char));
                    }else{
                         break;
                    }
                 }
                 else{
                     if(precedencia(opTope) >= precedencia(token)){
                         char opSaca = pop(pilaOperadores);
                         enqueue(colaSalida, &opSalida, sizeof(char));
                     }else{
                         break;
                     }
                 }
              }
              push(pilaOperadores, &token, sizeof(char));
         }
     }
     while(!pilaVacia(pilaOperadores)){
         char opSaca = pop(pilaOperadores);
         enqueue(colaSalida, &opSaca, sizeof(char));
     }
     destruirPila(pilaOperadores);
     return colaSalida;
}