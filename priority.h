#include "round-robin.h"

typedef struct Priority_row
{
    /*  Doc
        Descricao:
            Eh uma fila de prioridades;
            cada 'Row' eh uma lista ligada;
    */
    Round *p5;
    Round *p4; // mais alta prioridade
    Round *p3;
    Round *p2;
    Round *p1; // mais baixa prioridade
} Priority_row;