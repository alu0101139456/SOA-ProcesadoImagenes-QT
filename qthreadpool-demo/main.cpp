#include <QCoreApplication>
#include <QVector>
#include <QThreadPool>
#include <QDebug>
#include <QTime>

#include "initrandomvectortask.h"
#include "scalarproducttask.h"

#define VECTOR_SIZE         100000000
#define SLICE_SIZE          40960

//
// Crear un QVector de números aleatorios
//

QVector<double> createRandomVector(int size)
{
    QVector<double> v(size);

    QVector<double>::iterator beginIterator = v.begin();
    QVector<double>::iterator endIterator = v.begin() + SLICE_SIZE;

    // Lanzar las tareas para operar sobre subvectores de tamaño SUBVECTOR_SIZE
    while (endIterator < v.end()) {
        // Insertar la tarea en el pool de hilos
        InitRandomVectorTask *task = new InitRandomVectorTask(beginIterator, endIterator);
        QThreadPool::globalInstance()->start(task);

        beginIterator = endIterator;
        endIterator += SLICE_SIZE;
    }

    // Lanzar una tarea para operar sobre lo que reste del vector original
    if (endIterator != v.end()) {
        InitRandomVectorTask *task = new InitRandomVectorTask(beginIterator, v.end());
        QThreadPool::globalInstance()->start(task);
    }

    return v;
}

//
// Calcular el producto escalar de dos vectores QVector
//

double scalarProduct(const QVector<double>& v1, const QVector<double>& v2)
{
    // Lista de tareas para después poder recuperar el resultado de cada una
    QList<ScalarProductTask*> tasks;

    QVector<double>::const_iterator beginV1Iterator = v1.begin();
    QVector<double>::const_iterator beginV2Iterator = v2.begin();
    QVector<double>::const_iterator endV1Iterator = beginV1Iterator + SLICE_SIZE;
    QVector<double>::const_iterator endV2Iterator = beginV2Iterator + SLICE_SIZE;

    // Lanzar las tareas para operar sobre subvectores de tamaño SUBVECTOR_SIZE
    while (endV1Iterator < v1.end()) {
        // Insertar la tarea en el pool de hilos
        ScalarProductTask *task = new ScalarProductTask(beginV1Iterator,
                                                        endV1Iterator,
                                                        beginV2Iterator,
                                                        endV2Iterator);
        QThreadPool::globalInstance()->start(task);
        tasks.append(task);

        beginV1Iterator = endV1Iterator;
        beginV2Iterator = endV2Iterator;
        endV1Iterator += SLICE_SIZE;
        endV2Iterator += SLICE_SIZE;
    }

    // Lanzar una tarea para operar sobre lo que reste del vector original
    ScalarProductTask *task = new ScalarProductTask(beginV1Iterator, v1.end(),
                                                    beginV2Iterator, v2.end());
    QThreadPool::globalInstance()->start(task);
    tasks.append(task);

    // Esperar a que todas las tareas hayan terminado
    QThreadPool::globalInstance()->waitForDone();

    // Sumar el resultado de cada subtarea
    double result = 0.0;
    foreach(ScalarProductTask* task, tasks)
        result += task->result();

    return result;
}

//
// Programa principal
//

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTime timer;

    // Configurar el número de hilos del pool
//    QThreadPool::globalInstance()->setMaxThreadCount(1);
    qDebug() << "Comenzamos, Usando"
             << QThreadPool::globalInstance()->maxThreadCount()
             << "hilos...";

    qDebug() << "Generando dos vectores de números aleatorios...";
    timer.start();

    QVector<double> v1 = createRandomVector(VECTOR_SIZE);
    QVector<double> v2 = createRandomVector(VECTOR_SIZE);

    // Esperar a que todas las tareas hayan terminado
    QThreadPool::globalInstance()->waitForDone();

    qDebug() << "Hecho en" << timer.elapsed() << "ms.";
    qDebug() << "Calculando el producto escalar...";
    timer.start();

    double scalar = scalarProduct(v1, v2);

    qDebug() << "Hecho en" << timer.elapsed() << "ms.";
    qDebug() << "El resultado es" << qSetRealNumberPrecision(10) << scalar;

    return a.exec();
}
