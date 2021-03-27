#include "scalarproducttask.h"

ScalarProductTask::ScalarProductTask(VectorConstIterator beginV1Iterator,
                                     VectorConstIterator endV1Iterator,
                                     VectorConstIterator beginV2Iterator,
                                     VectorConstIterator endV2Iterator)
    : beginV1Iterator_(beginV1Iterator), endV1Iterator_(endV1Iterator),
      beginV2Iterator_(beginV2Iterator), endV2Iterator_(endV2Iterator),
      result_(0.0)
{
    // Evitar que el objeto sea destruido automáticamente al terminar la tarea
    setAutoDelete(false);
}

void ScalarProductTask::run()
{
    VectorConstIterator it1 = beginV1Iterator_;
    VectorConstIterator it2 = beginV2Iterator_;

    // Calcular el producto escalar de los vectores indicados
    for(; it1 < endV1Iterator_; ++it1, ++it2)
        result_ += (*it1) * (*it2);
}
