#ifndef COLA_T_H
#define COLA_T_H

#include <QWaitCondition>
#include <QMutex>
#include <QDebug>
#include <unistd.h>
#include <QVector>
#include <QThreadPool>
#include "process_t.h"

template<typename T>
class cola_t
{
 private:
    QMutex mutex_;
    QWaitCondition condition_;
    QVector<T> cola_;
    int limit_buff = 50;

public:
    cola_t() = default;
    cola_t(int limit): limit_buff(limit){ }
    bool isEmpty() { return cola_.empty(); }
    bool push( const T& data) {
        QMutexLocker lock(&mutex_);
        if ( cola_.size() > limit_buff ) {
            qDebug() << "Cola llena";
            sleep(1);
        } else {
            cola_.push_back(data);
            condition_.wakeAll();
            return true;
        }
    }

    T pop() {
        QMutexLocker lock(&mutex_);
        if(cola_.empty()){
            condition_.wait(&mutex_);
        }
        if ( !cola_.empty() ) {
            T aux = cola_.front();
            cola_.pop_front();
            return aux;
        }

    }
};
#endif // COLA_T_H
