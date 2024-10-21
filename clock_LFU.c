#include <stdio.h>
#include <stdlib.h>

#define NUM_FRAMES 4  // Número de frames (páginas físicas en memoria)

typedef struct {
    char page;    // Identificador de la página
    int useBit;   // Bit de uso: 1 si ha sido usada recientemente, 0 si no
} Frame;

// Función para imprimir el estado actual de los frames
void printFrames(Frame frames[], int numFrames) {
    printf("Estado actual de las páginas en memoria:\n");
    for (int i = 0; i < numFrames; i++) {
        printf("Página: %c, Bit de uso: %d\n", frames[i].page, frames[i].useBit);
    }
    printf("\n");
}

// Función para simular el algoritmo CLOCK
void loadPage(Frame frames[], int *hand, char newPage) {
    while (1) {
        // Si el bit de uso es 0, reemplazar la página
        if (frames[*hand].useBit == 0) {
            printf("Reemplazando página %c por página %c.\n", frames[*hand].page, newPage);
            frames[*hand].page = newPage;  // Reemplazar la página
            frames[*hand].useBit = 1;      // Establecer el bit de uso de la nueva página a 1
            *hand = (*hand + 1) % NUM_FRAMES;  // Mover la mano a la siguiente página
            break;
        } else {
            // Si el bit de uso es 1, ponerlo en 0 y pasar a la siguiente página
            frames[*hand].useBit = 0;
            *hand = (*hand + 1) % NUM_FRAMES;
        }
    }
}

int main() {
    // Inicializar los frames con las páginas [A, B, C, D] y sus bits de uso [1, 0, 1, 0]
    Frame frames[NUM_FRAMES] = {
        {'A', 1},
        {'B', 0},
        {'C', 1},
        {'D', 0}
    };

    int hand = 0;  // Inicialmente, la mano apunta a la página A

    // Mostrar el estado inicial de las páginas en memoria
    printFrames(frames, NUM_FRAMES);

    // Cargar la nueva página E usando el algoritmo CLOCK
    loadPage(frames, &hand, 'E');

    // Mostrar el estado final de las páginas en memoria
    printFrames(frames, NUM_FRAMES);

    return 0;
}
