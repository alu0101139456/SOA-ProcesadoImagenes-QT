#ifndef TOGAUSSIANBTASK_H
#define TOGAUSSIANBTASK_H

#include "tools.hpp"
#include <QRunnable>
#include "cola_t.h"
#include <QImage>
#include "process_t.h"
#include "gaussianblur.h"

class toGaussianBTask : public QRunnable
{
 private:
    cola_t<eImagen>* cola_;
    eImagen eImagen_;
    QImage gaussianImage_;
    GaussianBlur* gb_;

 public:
    toGaussianBTask(eImagen eimagen, cola_t<eImagen> *pcola):
        eImagen_(eimagen), cola_(pcola){
        gb_ = new GaussianBlur(3,5);
    }


 private:
   void run() override;

};

#endif // TOGAUSSIANBTASK_H

