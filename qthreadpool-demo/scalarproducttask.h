#ifndef SCALARPRODUCTTASK_H
#define SCALARPRODUCTTASK_H

#include <QRunnable>
#include <QVector>

class ScalarProductTask : public QRunnable
{
public:
    typedef QVector<double>::const_iterator VectorConstIterator;

    ScalarProductTask(VectorConstIterator beginV1Iterator,
                      VectorConstIterator endV1Iterator,
                      VectorConstIterator beginV2Iterator,
                      VectorConstIterator endV2Iterator);

    void run();

    double result();

private:
    const VectorConstIterator beginV1Iterator_;
    const VectorConstIterator endV1Iterator_;
    const VectorConstIterator beginV2Iterator_;
    const VectorConstIterator endV2Iterator_;

    double result_;
};

inline double ScalarProductTask::result()
{
    return result_;
}

#endif // SCALARPRODUCTTASK_H
