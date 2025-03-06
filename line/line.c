#include <stdio.h>
#include <SDL2/SDL.h>


typedef struct {
    char colorIndex;
} Color;

// Szakaszstruktúra, amely tartalmazza a végpontokat és a színt
typedef struct {
    int x1, y1; // Első végpont koordinátái
    int x2, y2; // Második végpont koordinátái
    Color color; // A szakasz színe
} Line;

// Példa egy szakasz létrehozására és kiírására
void printLine(const Line *line) {
    printf("Szakasz: (%d, %d) -> (%d, %d), Szín index: %c\n", line->x1, line->y1, line->x2, line->y2, line->color.colorIndex);
}

int main() {
    Line myLine = {10, 20, 30, 40, {'R'}}; // Piros szín indexszel
    
    printLine(&myLine);
    
    return 0;
}



