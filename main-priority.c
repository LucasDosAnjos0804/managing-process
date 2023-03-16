#include "priority.h"

#define QUANTUM 2

void *
thr_one (int tmp)
{

    // pthread_mutex_lock (&j->lock);
    // pthread_cond_wait (&j->cond,&j->lock);
    // pthread_mutex_unlock (&j->lock);

    // do anything
    printf("ASDF\n");
}

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


int main()
{
    srand(time(NULL));

    Priority_row *pr = (Priority_row*) malloc (sizeof(Priority_row));
    
    Round *p1 = (Round*) malloc (sizeof(Round));
    pr->p1 = p1;

    Round *p2 = (Round*) malloc (sizeof(Round));
    pr->p2 = p2;

    Round *p3 = (Round*) malloc (sizeof(Round));
    pr->p3 = p3;
    
    Round *p4 = (Round*) malloc (sizeof(Round));
    pr->p4 = p4;

    if (!pr)
    {
        err("can't malloc Priority_row");
        return 1;
    }


    add_JobToPriorityRow( create_job(thr_one,4),pr );
    add_JobToPriorityRow( create_job(thr_one,4),pr );
    add_JobToPriorityRow( create_job(thr_one,4),pr );

    add_JobToPriorityRow(create_job(thr_one,3),pr);
    add_JobToPriorityRow(create_job(thr_one,3),pr);

    add_JobToPriorityRow(create_job(thr_one,2),pr);

    
    Job *j;
    while ( (j = drop_PriorityJob(pr)) != NULL )
    {
        // executar o job
        /* 
            Simula a execucao de um precesso
        */

        if (pthread_create( (pthread_t *) &j->pt, NULL,j->fn, NULL) != 0)
            err("can't create thread!");
                    
        sleep(1);

        // diminuir QUANTUN do tempo de execucao
        j->tmp = j->tmp - QUANTUM;

        
        if ( j->tmp > 0 )
        {
            //manda a thread pausar

            // pthread_mutex_lock (&j->lock);
            // pthread_cond_signal (&j->cond);
            // pthread_mutex_unlock (&j->lock);

            add_JobToPriorityRow(j,pr);  //adiciona o Job ao final da fila de prioridade
        } else {
            // da join
            if ( (pthread_join( (pthread_t) j->pt, j->tret) ) != 0)
                err("thread join Error");
            else
                logs(" - thread terminated join success!");
        }
    }

    printf("FIM\n");

    free(pr);

    return 0;
}