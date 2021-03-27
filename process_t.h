
#ifndef PIPELINE_T_H
#define PIPELINE_T_H

#include <QCoreApplication>
#include <QImage>
#include <QElapsedTimer>
#include <iostream>
#include "gaussianblur.h"
#include <QDir>
#include <QThread>
#include <QDebug>
#include "tools.hpp"
#include "togray.h"



class process_t : public QThread {
  private:
    QVector<eImagen> files_;

    virtual void run() override {

        GaussianBlur blur(3,5);
        togray toGray;

        for ( int i=0 ; i < files_.size(); i++)
        {
            std::cout << files_.at(i).name.toStdString() << "\n";
            toGray.ApplyGrayFilterToImage(files_[i]);
            blur.ApplyGaussianFilterToImage(files_[i]);
            files_[i].imagen.save(files_[i].path+"img_procesed/"+ files_[i].newname);
        }
    }

  public:
    process_t() = default;
    void setList(QVector<eImagen> files) {
        files_ = files;
    }

};

#endif // PIPELINE_T_H
