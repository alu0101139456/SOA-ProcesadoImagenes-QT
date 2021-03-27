#include "togray.h"


QImage togray::ApplyGrayFilterToImage(QImage imagen)
{
    for(int i=0; i < imagen.width(); i++) {
        for(int j=0; j < imagen.height(); j++) {
            int graypixel = qGray(imagen.pixel(i,j));
            imagen.setPixel(i,j, QColor(graypixel,graypixel,graypixel).rgb());
        }
    }

    return imagen;
}

void togray::ApplyGrayFilterToImage(eImagen& imagen)
{
    for(int i=0; i < imagen.imagen.width(); i++) {
        for(int j=0; j < imagen.imagen.height(); j++) {
            int graypixel = qGray(imagen.imagen.pixel(i,j));
            imagen.imagen.setPixel(i,j, QColor(graypixel,graypixel,graypixel).rgb());
        }
    }
}
