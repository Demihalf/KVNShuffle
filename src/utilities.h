#ifndef UTILITIES_H
#define UTILITIES_H

namespace Utility {

template <class T>
QList<T> shuffled(QList<T> list)
{
    int newPos;

    for (int i = 0; i < list.size(); i++) {
        newPos = qrand() % list.size();
        qSwap(list[i], list[newPos]);
    }

    return list;
}

} // Utility


#endif // UTILITIES_H
