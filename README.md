#jonathan uriel paredes martinez
#espinosa olivera angel arturo
#garcia Torres Ivana yamile
#Analisis del código del algoritmo OPR
#1. Definiciones y estructuras iniciales
    • #define NUM_FRAMES 4 y #define NUM_PAGES 10: Define el número de frames (páginas físicas en memoria) y el número de páginas virtuales.
    • Estructura Frame:
#Representa un frame en memoria física. Contiene:
        ◦ int page: El número de la página que está almacenada en el frame. Si no hay ninguna página, el valor es -1.
        ◦ bool valid: Indica si el frame está ocupado (true) o vacío (false).
        ◦ Frame *prev y Frame *next: Son punteros que permiten enlazar los frames en una lista doblemente enlazada.
    • Estructura FrameList:
#Representa la lista de frames en memoria física. Contiene:
        ◦ int numFrames: Número de frames ocupados.
        ◦ Frame *head y Frame *tail: Punteros al primer y último frame de la lista, respectivamente.
#2. Funciones para manejar los frames
    • Frame* createFrame(): Crea un nuevo frame. Inicialmente, el frame no tiene ninguna página asignada (page = -1), está vacío (valid = false) y no tiene conexiones (prev = NULL, next = NULL).
    • FrameList* createFrameList(): Inicializa una lista vacía de frames. La lista no tiene ningún frame (numFrames = 0) y los punteros a la cabeza y la cola están vacíos.
#3. Manipulación de la lista de frames
    • insertFrame(FrameList *frameList, Frame *frame): Inserta un frame en la cabeza de la lista. Si la lista está vacía, el frame se convierte en la cabeza y la cola de la lista. Si no, el frame se inserta al frente y se actualizan los punteros.
    • removeFrame(FrameList *frameList, Frame *frame): Elimina un frame específico de la lista. Dependiendo de su posición (primero, en medio o último), actualiza los punteros prev y next y libera la memoria del frame.
    • Frame* findFrame(FrameList *frameList, int page): Busca un frame que contenga un número de página específico en la lista. Recorre la lista secuencialmente y devuelve el frame que tiene la página buscada, o NULL si no lo encuentra.
#4. Algoritmo de reemplazo de páginas óptimo
    • loadPage(FrameList *frameList, int page, int futureAccess[]): Simula la carga de una página en memoria utilizando el algoritmo de reemplazo de páginas óptimo. Si la lista de frames está llena, determina cuál es la página que no será utilizada por más tiempo en el futuro y la reemplaza. Este proceso involucra:
        ◦ Se crea un nuevo frame con la página que debe cargarse.
        ◦ Si la lista está llena, busca el frame que contiene la página que no se usará por el mayor tiempo futuro (usando el arreglo futureAccess[]).
        ◦ El frame más "óptimo" para ser reemplazado se elimina de la lista con removeFrame().
        ◦ Finalmente, se inserta el nuevo frame con la página cargada en la lista con insertFrame().
#5. Impresión del estado actual
    • printFrameList(FrameList *frameList): Imprime el estado actual de los frames en memoria, mostrando el número de página y si el frame está ocupado o vacío. Esto es útil para depuración.
#6. Función principal (main())
    • FrameList *frameList = createFrameList();: Inicializa la lista de frames en memoria física.
    • int futureAccess[NUM_PAGES] = {1, 2, 3, 4, 5, 1, 2, 1, 3, 4};: Define un arreglo que representa el acceso futuro de páginas virtuales (en este caso, las páginas que serán solicitadas en el orden dado).
    • for (int i = 0; i < NUM_PAGES; ++i): Itera sobre los accesos a las páginas virtuales y simula la carga de cada página en memoria usando el algoritmo de reemplazo óptimo.
    • loadPage(frameList, futureAccess[i], futureAccess + i + 1);: Para cada acceso, carga la página correspondiente en memoria. Si es necesario, reemplaza alguna página utilizando la política óptima.
    • printFrameList(frameList);: Después de cada carga de página, imprime el estado actual de la lista de frames.
    • free(frameList);: Libera la memoria utilizada por la lista de frames.
