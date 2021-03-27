#ifndef TOGRAYTASK_H
#define TOGRAYTASK_H

#include "tools.hpp"
#include <QRunnable>
#include "cola_t.h"
#include <QImage>
#include "process_t.h"
#include "togray.h"

class toGrayTask : public QRunnable
{
 private:
    cola_t<eImagen>* cola_;
    eImagen eImagen_;
    QImage grayImage_;
    togray * gray_;

 public:
    toGrayTask(eImagen imagen, cola_t<eImagen> *pcola):
        eImagen_(imagen), cola_(pcola){}

private:
   void run() override;

};

#endif // TOGRAYTASK_H
