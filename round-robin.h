#include "job.h"

typedef struct Round
{
    int tam;
    Job *start; 
}Round;

void
add_job(Round *robin, Job *j)
{
    /*  Doc
        Descricao:
            Adiciona o Job ao robin (lista circular)
        
    */
    j->prox = robin->start;
    robin->start = j;

    robin->tam++;
}

Job *
drop_job (Round* robin)
{
    /*  Doc
        Descricao:
            Remove no do inicio da fila circular;
    */

    logs("ei3");
    if (robin == NULL) err("robin null"); 
    Job *no = robin->start;  ///// por algun motivo apos um drop, robin start fica null
    logs("ei4");

    if (no) // se for NULL, quer dizer que a fila esta vazia
    {
        if (no->prox == NULL) // se ele for o ultmimo elemento da lista
        {
            robin->start = NULL;
        } else {
            robin->start = no->prox;
        }

        no->prox = NULL;
        
        robin->tam--;
    }

    return no;
}