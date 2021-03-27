#include "tograytask.h"

void toGrayTask::run() {
    gray_->ApplyGrayFilterToImage(eImagen_);

    cola_->push(eImagen_);
}
