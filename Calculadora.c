#include <stdio.h>
#include <math.h>

// Declaramos una pila e implementamos sus métodos principales

float stack[8];
int counter = -1;

void push(float stack[], int *counter, float value) { // * Es una referencia al valor de counter
    if(is_full(*counter)) {
        printf("La pila está llena");
        return;
    }

    (*counter)++; // Incrementamos el valor de counter
    stack[*counter] = value; // Asignamos el valor a la posición counter
}

float pop(float stack[], int *counter) {
    if (is_empty(*counter)) {
        printf("La pila está vacía\n");
        return 0.0f;  
    }

    float valor = stack[*counter];
    (*counter)--;                   
    return valor;
}

int is_empty(int counter) { 
    return counter == -1; // Evaluación Lógica para saber si counter es igual a -1, implicando una pila vacía
}

int is_full(int counter) {
    return counter >= 7; // Evaluación Lógica para saber si el contador es superior o igual a 7
}

void clear_stack(int *counter) {
    for (int i = 0; i < 8; i++) {
        stack[i] = 0.0f;
    }
    *counter = -1;
}

void print_stack(const float stack[], int counter) {
    printf("\n");

    for (int idx = 8; idx >= 1; idx--) {
        int pos_arreglo = idx - 1;          

        if (counter >= 0 && pos_arreglo <= counter) {
            printf("%d. %.6f\n", idx, stack[pos_arreglo]);
        } 
        else {
            // Imprimimos posiciones vacías
            printf("%d. 0.000000\n", idx);
        }
    }

    printf("\n");
}

int main(void) {

    int opcion;
    float ingresado;
    float descartado;

    printf("Calculadora RPN con 8 registros \n");

    while(1){
        
        print_stack(stack, counter);

        printf("¿Qué desea hacer?\n1.Ingresar número\t2.Realizar operación\t3.Limpiar último\t4.Limpiar todo\t5.Salir\nIngrese Opción: ");
    
        scanf("%d", &opcion);
        
        if(opcion < 1 || opcion > 5){

            printf("Ingrese una opción válida");
            break;
        }

        switch (opcion) {
            case 1: {
                float ingresado;
                printf("Ingrese el número: ");
                if (scanf("%f", &ingresado) == 1) {
                    push(stack, &counter, ingresado);
                } else {
                    printf("Número inválido.\n");
                    while (getchar() != '\n');
                }
                break;
            }

            case 2: { 
                char op;
                float a, b, resultado;

                printf("Ingrese operador (+ - * / r ^ s c t): ");
                scanf(" %c", &op);  // Espacio antes de %c para limpiar buffer

                // Operaciones unarias
                if (op == 'r' || op == 's' || op == 'c' || op == 't') {

                    if (counter < 0) {
                        printf("No hay operandos suficientes.\n");
                        break;
                    }

                    a = pop(stack, &counter);

                    switch (op) {
                        case 'r': // Raíz cuadrada
                            if (a < 0) {
                                printf("Error: no se puede sacar raíz de un número negativo.\n");
                                push(stack, &counter, a);
                                break;
                            }
                            resultado = sqrtf(a);
                            push(stack, &counter, resultado);
                            break;

                        case 's': // Seno (grados)
                            resultado = sinf(a * M_PI / 180.0f);
                            push(stack, &counter, resultado);
                            break;

                        case 'c': // Coseno (grados)
                            resultado = cosf(a * M_PI / 180.0f);
                            push(stack, &counter, resultado);
                            break;

                        case 't': // Tangente (grados)
                            if (fmodf(a, 180.0f) == 90.0f) {
                                printf("Error: la tangente no está definida para %.2f grados.\n", a);
                                push(stack, &counter, a);
                                break;
                            }
                            resultado = tanf(a * M_PI / 180.0f);
                            push(stack, &counter, resultado);
                            break;
                    }
                }
                // Operaciones binarias
                else {

                    if (counter < 1) {
                        printf("No hay operandos suficientes.\n");
                        break;
                    }

                    a = pop(stack, &counter); // Primer elemento
                    b = pop(stack, &counter); // Segundo elemento

                    switch (op) {
                        case '+':
                            resultado = b + a;
                            push(stack, &counter, resultado);
                            break;

                        case '-':
                            resultado = b - a;
                            push(stack, &counter, resultado);
                            break;

                        case '*':
                            resultado = b * a;
                            push(stack, &counter, resultado);
                            break;

                        case '/':
                            if (a == 0) {
                                printf("Error: no se puede dividir por cero.\n");
                                push(stack, &counter, b);
                                push(stack, &counter, a);
                                break;
                            }
                            resultado = b / a;
                            push(stack, &counter, resultado);
                            break;

                        case '^': // Potencia
                            resultado = powf(b, a);
                            push(stack, &counter, resultado);
                            break;

                        default:
                            printf("Operador inválido.\n");
                            push(stack, &counter, b);
                            push(stack, &counter, a);
                            break;
                    }
                }
                break;
            }


            case 3: { // Pop
                descartado = pop(stack, &counter);
                printf("Elemento descartado: %.4f\n", descartado);
                
                break;
            }

            case 4: {  // Limpiar todo
                clear_stack(&counter);
                printf("Pila limpiada completamente.\n");
                break;
            }

            case 5: {  // Exit
                printf("\n¡Gracias por usar la calculadora!\n");
                return 0;
            }

            default:{
                printf("Opción inválida. Elija entre 1 y 5.\n");
                break;
            }
        }
    }
}