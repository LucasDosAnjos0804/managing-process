#include "round-robin.h"

// typedef struct Row
// {
//     /*  Doc
//         Descricao:
//             Eh uma lista ligada
//     */
//     int tam;    // quantidade de itens que existem na fila
//     Job *start; // ponteiro para o primeiro elemento da fila
//     Job *end;   // ponteiro para o ultimo elemento da fila
// }Row;

typedef struct Priority_row
{
    /*  Doc
        Descricao:
            Eh uma fila de prioridades;
            cada 'Row' eh uma lista ligada;
    */
    Round *p4; // mais alta prioridade
    Round *p3;
    Round *p2;
    Round *p1; // mais baixa prioridade
} Priority_row;