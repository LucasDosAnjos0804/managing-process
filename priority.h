#include "round-robin.h"

typedef struct Priority_row
{
    /*  Doc
        Descricao:
            Eh uma fila de prioridades;
            cada 'Row' eh uma lista ligada;
    */
    Round *p5; //n sei pq precisa disso mas precisa asdfasdfasdf
    Round *p4; // mais alta prioridade
    Round *p3;
    Round *p2;
    Round *p1; // mais baixa prioridade
} Priority_row;


void
add_JobToPriorityRow(Job *j, Priority_row *pr)
{

    /*  Doc
        Descricao:
            Adiciona um Job a uma fila de prioridade
    */
    switch ( (int) j->priority )
    {
    case 1:
        add_job(pr->p1,j);
        break;

    case 2:
        add_job(pr->p2,j);
        break;

    case 3:
        add_job(pr->p3,j);
        break;

    case 4:
        add_job(pr->p4,j);
        break;

    default:
        if (j->priority < 1 || j->priority > 4)
            err("job com prioridade invalida!");
        break;
    }

    logs("Job adicionado a fila de prioridades");
}

Job*
drop_PriorityJob (Priority_row *pr) 
{
    /*
        Dropa um job da primeira fila de prioridade que nao estiver vazia
    */
    Round *r;
    
    if (pr->p4->tam) // TAS ERRADO
    {
        r = pr->p4;
    } else if (pr->p3->tam) {
        r = pr->p3;
    } else if (pr->p2->tam) {
        r = pr->p2;
    } else if (pr->p1->tam) {
        r = pr->p1;
    } else {
        return NULL;
    }
    return drop_job(r);
}