//Equipo tralaleritos Enriqwue, Nando, Ena, Germán. --__--

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#include "../include/evaluator.h"
#include "../include/pila.h"

float obtenerValorVariable(Variable variables[], int total, char nombre) {
    for (int i = 0; i < total; i++) {
        if (variables[i].nombre == nombre) {
            return variables[i].valor;
        }
    }
    return 0.0f; 
}

float evaluarPostfija(Cola* postfija, Variable variables[], int totalVariables) {
    Pila* pila_operandos = crearPila();
    
    while (!colaVacia(postfija)) {
        char* token = (char*) desencolar(postfija);
        
        if (token[0] == ' ' || token[0] == '\0') {
            continue;
        }

        if (isalpha(token[0])) {
            float valor = obtenerValorVariable(variables, totalVariables, token[0]);
            push(pila_operandos, &valor, sizeof(float));
        } 
        else if (isdigit(token[0])) {
            float valor = atof(token);
            push(pila_operandos, &valor, sizeof(float));
        }
        else {
            float op2 = 0.0f, op1 = 0.0f;

            if (!pilaVacia(pila_operandos)) {
                op2 = *(float*)(pila_operandos->tope->dato);
                pop(pila_operandos);
            }
            if (!pilaVacia(pila_operandos)) {
                op1 = *(float*)(pila_operandos->tope->dato);
                pop(pila_operandos);
            }

            float resultado = 0.0f;
            
            switch (token[0]) {
                case '+': resultado = op1 + op2; break;
                case '-': resultado = op1 - op2; break;
                case '*': resultado = op1 * op2; break;
                case '/': 
                    if(op2 != 0) {
                        resultado = op1 / op2; 
                    }
                    break;
                case '^': 
                    resultado = pow(op1, op2); 
                    break;
            }
            
            push(pila_operandos, &resultado, sizeof(float));
        }
    }
    float resultado_final = 0.0f;
    if (!pilaVacia(pila_operandos)) {
        resultado_final = *(float*)(pila_operandos->tope->dato);
        pop(pila_operandos);
    }
    destruirPila(pila_operandos);
    
    return resultado_final;
}
