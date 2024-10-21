#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_FRAMES 4   // Número de frames (páginas físicas en memoria)
#define NUM_PAGES 10   // Número total de páginas virtuales

// Estructura para un frame de página en memoria física
typedef struct Frame {
    int page;           // Número de página almacenada en el frame (valor -1 si está vacío)
    bool valid;         // Indica si el frame está ocupado (true) o vacío (false)
    int frequency;      // Contador de frecuencia de uso
    struct Frame *prev; // Puntero al frame previo (para lista doblemente enlazada)
    struct Frame *next; // Puntero al frame siguiente (para lista doblemente enlazada)
} Frame;

// Estructura para la lista de frames en memoria física
typedef struct FrameList {
    int numFrames;      // Número de frames actualmente ocupados
    Frame *head;        // Puntero al primer frame de la lista
    Frame *tail;        // Puntero al último frame de la lista
} FrameList;

// Función para crear un nuevo frame
Frame* createFrame() {
    Frame *frame = (Frame *)malloc(sizeof(Frame));
    if (frame != NULL) {
        frame->page = -1;   // Inicialmente no hay página asignada
        frame->valid = false;
        frame->frequency = 0; // Frecuencia inicial en 0
        frame->prev = NULL;
        frame->next = NULL;
    }
    return frame;
}

// Función para inicializar la lista de frames en memoria física
FrameList* createFrameList() {
    FrameList *frameList = (FrameList *)malloc(sizeof(FrameList));
    if (frameList != NULL) {
        frameList->numFrames = 0;
        frameList->head = NULL;
        frameList->tail = NULL;
    }
    return frameList;
}

// Función para insertar un frame al frente de la lista (más recientemente usado)
void insertFrame(FrameList *frameList, Frame *frame) {
    if (frameList->head == NULL) {
        // Lista vacía
        frameList->head = frame;
        frameList->tail = frame;
    } else {
        // Insertar al frente de la lista
        frame->next = frameList->head;
        frameList->head->prev = frame;
        frameList->head = frame;
    }
    frameList->numFrames++;
}

// Función para eliminar un frame de la lista (el menos frecuentemente usado)
void removeFrame(FrameList *frameList, Frame *frame) {
    if (frame->prev != NULL) {
        frame->prev->next = frame->next;
    } else {
        frameList->head = frame->next;
    }
    if (frame->next != NULL) {
        frame->next->prev = frame->prev;
    } else {
        frameList->tail = frame->prev;
    }
    frameList->numFrames--;
    free(frame);
}

// Función para buscar un frame específico por número de página
Frame* findFrame(FrameList *frameList, int page) {
    Frame *current = frameList->head;
    while (current != NULL) {
        if (current->page == page) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Función para encontrar el frame con menor frecuencia (LFU)
Frame* findLFUFrame(FrameList *frameList) {
    Frame *current = frameList->head;
    Frame *lfuFrame = current;
    while (current != NULL) {
        if (current->frequency < lfuFrame->frequency) {
            lfuFrame = current;
        }
        current = current->next;
    }
    return lfuFrame;
}

// Función para simular la carga de una página a memoria física utilizando LFU
void loadPage(FrameList *frameList, int page) {
    Frame *existingFrame = findFrame(frameList, page);

    // Si la página ya está en memoria, solo incrementa la frecuencia
    if (existingFrame != NULL) {
        existingFrame->frequency++;
        return;
    }

    Frame *frame = createFrame();
    frame->page = page;
    frame->valid = true;
    frame->frequency = 1; // Nueva página empieza con frecuencia 1

    // Si la lista de frames ya está llena, eliminar el frame con menor frecuencia (LFU)
    if (frameList->numFrames == NUM_FRAMES) {
        Frame *lfuFrame = findLFUFrame(frameList);
        removeFrame(frameList, lfuFrame);
    }

    insertFrame(frameList, frame);
}

// Función para imprimir el estado actual de la lista de frames (solo para fines de depuración)
void printFrameList(FrameList *frameList) {
    printf("Estado actual de la lista de frames:\n");
    Frame *current = frameList->head;
    while (current != NULL) {
        printf("Página: %d, Frecuencia: %d, ", current->page, current->frequency);
        if (current->valid) {
            printf("Estado: Ocupado\n");
        } else {
            printf("Estado: Vacío\n");
        }
        current = current->next;
    }
    printf("\n");
}

int main() {
    FrameList *frameList = createFrameList();

    // Simular la carga de varias páginas a memoria física
    loadPage(frameList, 1);
    loadPage(frameList, 2);
    loadPage(frameList, 3);
    loadPage(frameList, 4);
    printFrameList(frameList);  // Debería imprimir el estado actual de los frames

    // Intentar cargar otra página cuando todos los frames están ocupados
    loadPage(frameList, 5);
    printFrameList(frameList);  // Debería imprimir el estado actual después de la sustitución

    // Liberar la memoria utilizada por la lista de frames
    free(frameList);

    return 0;
}
