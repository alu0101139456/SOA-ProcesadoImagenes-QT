#include <QCoreApplication>
#include <QImage>
#include <QElapsedTimer>
#include <iostream>
#include "gaussianblur.h"
#include <QDir>
#include "process_t.h"
#include <QCommandLineParser>
#include <QDebug>
#include <QVector>
#include <string>
#include <QThreadPool>
#include "cola_t.h"
#include "tograytask.h"
#include "togaussianbtask.h"


//This function is call in Divide&Conquer mode
void divide(QVector<eImagen> list, QList<QVector<eImagen>> *outLists, int profundidad, int actual = 1) {
    if(actual <= profundidad)
    {
        divide(list.mid(0, list.size()/2), outLists, profundidad, actual+1);
        divide(list.mid(list.size()/2), outLists, profundidad, actual+1);

    }else {
        outLists->push_back(list);
    }
}

//createGrayTask and createGBTask make task to push in queue
void createGrayTask(cola_t<eImagen> *pcola, QVector<eImagen>& eVectorList) {
    for( auto& eVImagen: eVectorList) {
        toGrayTask *task = new toGrayTask(eVImagen, pcola);
        QThreadPool::globalInstance()->start(task);
    }
}

void createGBTask(cola_t<eImagen> *pcola, QVector<eImagen>& eVectorList) {
    for( auto& eVImagen: eVectorList) {
        toGaussianBTask* task = new toGaussianBTask(pcola->pop(), pcola);
        QThreadPool::globalInstance()->start(task);
    }
}


//Init vector make vector of eImagen to use in both modes
void init_vector(QStringList& filtro, QDir& dir, QStringList& files, QVector<eImagen>& efile) {

    filtro << "*.png" << "*.PNG" << "*.jpg" << "*.JPG";
    filtro << "*.jpeg" << "*.JPEG";
    dir.setNameFilters(filtro);
    files = dir.entryList();
    for (const auto& i : files) {
       eImagen aux;
       aux.path = dir.absolutePath()+"/";
       aux.name = i;
       QImage im(aux.path+aux.name);
       aux.imagen = im;
       QString svfl;
       svfl = i;
       svfl.replace(".", "_grBl.");
       aux.newname = svfl;
       efile.push_back(aux);
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QElapsedTimer timer;
    QDir dir("../Images");
    QStringList filtro;
    QStringList filesList;
    //Create vector of struct EImagen
    QVector<eImagen> eVectorFiles;

     timer.start();
    //Init vector
    init_vector(filtro, dir, filesList, eVectorFiles);
    //Use "listas" for divide and conquer algorithm


    QCommandLineParser commandLine;
    commandLine.setApplicationDescription("Procesado de imágenes");
    commandLine.addHelpOption();

    QCommandLineOption deepness("d" ,
            QCoreApplication::translate("main", "Nivel de profundidad para divide y vencerás"),
            QCoreApplication::translate("main", "Value"));
            commandLine.addOption(deepness);

    QCommandLineOption thread("p",
            QCoreApplication::translate("main", "Número de hilos en el threadpool"),
            QCoreApplication::translate("main", "Value"));
            commandLine.addOption(thread);

    commandLine.process(a);

    int deep = commandLine.value(deepness).toInt();
    int threads = threads = commandLine.value(thread).toInt();

    if(commandLine.isSet(deepness)) {
         std::cout << "Nivel de profundidad: " << deep << "\n";
         QList<QVector<eImagen>> listas;
         divide(eVectorFiles, &listas, deep);
         process_t pro[listas.size()];

         for(int i=0; i < listas.size(); i++) {
             pro[i].setList(listas[i]);
         }
         for(int i=0; i < listas.size(); i++) {
             pro[i].start();
         }
         for(int i=0; i < listas.size(); i++) {
             pro[i].wait();
         }

    }
    else {
        std::cout << "Número de hilos del Threadpool: " << threads << '\n';
        cola_t<eImagen> cola_;
        if(threads != -1) {
            QThreadPool::globalInstance()->setMaxThreadCount(threads);
        }
        else  {
            std::cout << "Usando maximo de hilos\n";
            QThreadPool::globalInstance()->maxThreadCount();
        }
        createGrayTask(&cola_, eVectorFiles);
        createGBTask(&cola_, eVectorFiles);

        QThreadPool::globalInstance()->waitForDone();
    }



    std::cout << "Elapsed " << timer.elapsed() << " ms\n";
    return 0;
    //return a.exec();
}



