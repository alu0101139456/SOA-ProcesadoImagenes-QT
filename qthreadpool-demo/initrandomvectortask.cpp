#include <QtGlobal>

#include "initrandomvectortask.h"

InitRandomVectorTask::InitRandomVectorTask(VectorIterator beginIterator,
                                           VectorIterator endIterator)
    : beginIterator_(beginIterator), endIterator_(endIterator)
{
}

void InitRandomVectorTask::run()
{
    VectorIterator it = beginIterator_;

    // Iniciar el vector indicado de forma aleatoria
    for(; it < endIterator_; ++it)
        *it = qrand() / (RAND_MAX + 1.0);
}
