#include <stdio.h>
#include <stdlib.h>

#define NUM_FRAMES 4  // Número de frames (páginas físicas en memoria)

typedef struct {
    char page;    // Identificador de la página
    int freq;     // Conteo de uso (frecuencia)
} Frame;

// Función para imprimir el estado actual de las páginas en memoria
void printFrames(Frame frames[], int numFrames) {
    printf("Estado actual de las páginas en memoria:\n");
    for (int i = 0; i < numFrames; i++) {
        printf("Página: %c, Frecuencia de uso: %d\n", frames[i].page, frames[i].freq);
    }
    printf("\n");
}

// Función para encontrar la página con el menor conteo de uso (LFU)
int findPageToReplace(Frame frames[]) {
    int minFreqIndex = 0;  // Suponemos que la primera página tiene la frecuencia más baja
    for (int i = 1; i < NUM_FRAMES; i++) {
        if (frames[i].freq < frames[minFreqIndex].freq) {
            minFreqIndex = i;
        }
    }
    return minFreqIndex;
}

// Función para simular la carga de una nueva página usando el algoritmo LFU
void loadPage(Frame frames[], char newPage) {
    // Encontrar la página con la menor frecuencia de uso
    int pageToReplace = findPageToReplace(frames);
    printf("Reemplazando página %c por página %c.\n", frames[pageToReplace].page, newPage);

    // Reemplazar la página y resetear su frecuencia
    frames[pageToReplace].page = newPage;
    frames[pageToReplace].freq = 1;  // Inicializamos la frecuencia de la nueva página en 1
}

// Función para simular el acceso a una página en memoria (incrementa su frecuencia de uso)
void accessPage(Frame frames[], char page) {
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (frames[i].page == page) {
            frames[i].freq++;  // Incrementa la frecuencia de uso de la página
            printf("Página %c accedida. Nueva frecuencia: %d\n", page, frames[i].freq);
            return;
        }
    }
    printf("Página %c no encontrada en memoria.\n", page);
}

int main() {
    // Inicializar los frames con las páginas [A, B, C, D] y frecuencias de uso [3, 1, 2, 4]
    Frame frames[NUM_FRAMES] = {
        {'A', 3},
        {'B', 1},
        {'C', 2},
        {'D', 4}
    };

    // Mostrar el estado inicial de las páginas en memoria
    printFrames(frames, NUM_FRAMES);

    // Simular el acceso a algunas páginas para cambiar sus frecuencias
    accessPage(frames, 'A');
    accessPage(frames, 'C');
    accessPage(frames, 'A');

    // Cargar la nueva página E usando el algoritmo LFU
    loadPage(frames, 'E');

    // Mostrar el estado final de las páginas en memoria
    printFrames(frames, NUM_FRAMES);

    return 0;
}
