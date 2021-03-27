#ifndef INITRANDOMVECTORTASK_H
#define INITRANDOMVECTORTASK_H

#include <QRunnable>
#include <QVector>

class InitRandomVectorTask : public QRunnable
{
public:
    typedef QVector<double>::iterator VectorIterator;

    InitRandomVectorTask(VectorIterator beginIterator,
                         VectorIterator endIterator);

    void run();

private:
    const VectorIterator beginIterator_;
    const VectorIterator endIterator_;
};

#endif // INITRANDOMVECTORTASK_H
