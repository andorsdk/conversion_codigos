#include <stdio.h>
#include <stdlib.h>

#define NUM_FRAMES 4  // Número de frames (páginas físicas en memoria)
#define NUM_PAGES 10  // Número total de páginas futuras para simular

typedef struct {
    char page;    // Identificador de la página
    int futureUse;  // Índice de la siguiente aparición en la secuencia futura de páginas
} Frame;

// Función para imprimir el estado actual de las páginas en memoria
void printFrames(Frame frames[], int numFrames) {
    printf("Estado actual de las páginas en memoria:\n");
    for (int i = 0; i < numFrames; i++) {
        printf("Página: %c, Próximo uso en índice: %d\n", frames[i].page, frames[i].futureUse);
    }
    printf("\n");
}

// Función para buscar la página que no se utilizará por más tiempo en el futuro (OPR)
int findPageToReplace(Frame frames[], char futurePages[], int currentIndex) {
    int maxFutureIndex = -1;  // Mayor índice de la siguiente aparición
    int pageToReplace = -1;   // Índice de la página a reemplazar

    for (int i = 0; i < NUM_FRAMES; i++) {
        frames[i].futureUse = NUM_PAGES + 1;  // Si la página no se encuentra en la secuencia futura, poner un valor grande
        
        // Buscar el próximo uso de la página en la secuencia futura
        for (int j = currentIndex + 1; j < NUM_PAGES; j++) {
            if (frames[i].page == futurePages[j]) {
                frames[i].futureUse = j;  // Guardar el índice del próximo uso
                break;
            }
        }

        // Si encontramos una página que no se usará por más tiempo, la seleccionamos para reemplazar
        if (frames[i].futureUse > maxFutureIndex) {
            maxFutureIndex = frames[i].futureUse;
            pageToReplace = i;
        }
    }

    return pageToReplace;
}

// Función para simular la carga de una nueva página usando el algoritmo OPR
void loadPage(Frame frames[], char newPage, char futurePages[], int currentIndex) {
    // Encontrar la página con el uso más lejano en el futuro
    int pageToReplace = findPageToReplace(frames, futurePages, currentIndex);
    printf("Reemplazando página %c por página %c.\n", frames[pageToReplace].page, newPage);

    // Reemplazar la página
    frames[pageToReplace].page = newPage;
}

// Función para simular el acceso a una página en memoria
int isPageInMemory(Frame frames[], char page) {
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (frames[i].page == page) {
            return 1;  // Página encontrada en memoria
        }
    }
    return 0;  // Página no encontrada en memoria
}

int main() {
    // Secuencia de páginas futuras para simular
    char futurePages[NUM_PAGES] = {'A', 'B', 'C', 'D', 'E', 'A', 'C', 'F', 'B', 'D'};

    // Inicializar los frames con las páginas [A, B, C, D]
    Frame frames[NUM_FRAMES] = {
        {'A', 0},
        {'B', 0},
        {'C', 0},
        {'D', 0}
    };

    // Mostrar el estado inicial de las páginas en memoria
    printFrames(frames, NUM_FRAMES);

    // Simular la carga de páginas futuras y el reemplazo con el algoritmo OPR
    for (int i = 4; i < NUM_PAGES; i++) {
        char currentPage = futurePages[i];
