#ifndef TOGRAY_H
#define TOGRAY_H

#include "tools.hpp"
#include <QTextStream>
#include <QImage>
#include <qmath.h>

class togray
{

public:

    eImagen test;
    togray() = default;
    ~togray() {}

    QImage ApplyGrayFilterToImage(QImage imagen);
    void ApplyGrayFilterToImage(eImagen& imagen);

};


#endif // TOGRAY_H
