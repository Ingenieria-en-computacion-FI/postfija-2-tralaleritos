#include <stdio.h>
#include <stdlib.h>

#include "../include/parser.h"
#include "../include/evaluator.h"
#include "../include/cola.h"

int main() {
    Variable variables[MAX_VARIABLES];
    int totalVariables = 0;
    char expresion[MAX_EXPR];

    cargarArchivo(
        "input/caso1.txt",
        variables,
        &totalVariables,
        expresion
    );

    printf("Expresion infija:\n");
    printf("%s\n\n", expresion);

    Cola* postfija = infijaAPostfija(expresion);

    if (postfija == NULL) {
        printf("Error: No se pudo generar la expresion postfija.\n");
        return 1;
    }

    printf("Expresion postfija:\n");
    imprimirCola(postfija);

    float resultado = evaluarPostfija(
        postfija,
        variables,
        totalVariables
    );

    printf("\nResultado:\n");
    printf("%.0f\n", resultado)ue; 
    destruirCola(postfija);

    return 0;
}
