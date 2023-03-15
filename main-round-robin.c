#include "round-robin.h" // acoplamento gritante

#define QUANTUM 2
#define ENABLE_LOGS 0

void *
thr_one (int tmp)
{

    // pthread_mutex_lock (&j->lock);
    // pthread_cond_wait (&j->cond,&j->lock);
    // pthread_mutex_unlock (&j->lock);

    // do anything
    printf("HUEHUE\n");
}

int 
main(void)
{
    srand(time(NULL));

    Round *robin = (Round *) malloc(sizeof(Round));

    if (robin)
    {
        add_job( robin, create_job(thr_one,1) );
        add_job( robin, create_job(thr_one,1) );
        add_job( robin, create_job(thr_one,1) );
        add_job( robin, create_job(thr_one,1) ); // 4 Jobs criados
        

        for ( Job *j = drop_job(robin); j; j = drop_job(robin))
        {
            /*
                A cada QUANTUM um Job deve ser executado, mesmo que o Job anterior nao tenha acabado, 
                se esse fosse o caso ele deve parar de executar e o proximo deve ser executado

            */

            if (pthread_create( (pthread_t *) &j->pt, NULL,j->fn, NULL) != 0)
                err("can't create thread!");
                       
            sleep(1);

            j->tmp -= QUANTUM;

            if ( j->tmp > 0 )
            {
                //manda a thread pausar

                // pthread_mutex_lock (&j->lock);
                // pthread_cond_signal (&j->cond);
                // pthread_mutex_unlock (&j->lock);

                add_job(robin, j);  //adiciona o Job ao final da fila circular
            } else {
                // da join
                if ( (pthread_join( (pthread_t) j->pt, j->tret) ) != 0)
                    err("thread join Error");
                else
                    logs(" - thread terminated join success!");
            }
        }
    } else {
        err("can't malloc robin");
    }
    
    logs("FIM");

    free(robin);

    return 0;
}