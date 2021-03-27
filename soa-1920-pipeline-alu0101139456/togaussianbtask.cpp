#include "togaussianbtask.h"

void toGaussianBTask::run() {

    gb_->ApplyGaussianFilterToImage(eImagen_);
    std::cout << eImagen_.name.toStdString() << "\n";
    eImagen_.imagen.save(eImagen_.path+"img_procesed/"+eImagen_.newname);
}

