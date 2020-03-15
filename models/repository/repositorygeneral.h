#ifndef REPOSITORYGENERAL_H
#define REPOSITORYGENERAL_H

#include <QList>

template <class T>
class RepositoryGeneral
{
private:
    QList<T> elements;

    class QList<T>::iterator getIteratorById(int id);
public:
    int currentCount = 0;

    RepositoryGeneral();
    ~RepositoryGeneral();

    // Добавить предмет
    void add(T data);

    // Удалить предмет
    bool remove(int id);

    // Обновить предмет
    bool update(int id, T data);

    // Получить премет
    T getById(int id);

    // Получить все редметы
    QList<T> getAll();
};

template <class T>
RepositoryGeneral<T>::RepositoryGeneral() {

}

template <class T>
RepositoryGeneral<T>::~RepositoryGeneral() {

}

template <class T>
class QList<T>::iterator RepositoryGeneral<T>::getIteratorById(int id) {
    class QList<T>::iterator it = std::find_if(this->elements.begin(), this->elements.end(), [id](T element){ return element.id == id; });
    return it;
}

template <class T>
void RepositoryGeneral<T>::add(T data) {
    ++this->currentCount;
    data.id = this->currentCount;
    this->elements.append(data);
}

template <class T>
bool RepositoryGeneral<T>::remove(int id) {
    class QList<T>::iterator it = this->getIteratorById(id);
    if (it != this->elements.end()){
        this->elements.erase(it);
        return true;
    }
    return false;
}

template <class T>
bool RepositoryGeneral<T>::update(int id, T data) {
    class QList<T>::iterator it = this->getIteratorById(id);
    if (it != this->elements.end()){
        data.id = id;
        this->elements.replace(std::distance(this->elements.begin(), it), data);
        return true;
    }
    return false;
}

template <class T>
T RepositoryGeneral<T>::getById(int id) {
    class QList<T>::iterator it = this->getIteratorById(id);
    if(it !=this->elements.end()) {
        return *it;
    }
    return T();
}

template <class T>
QList<T> RepositoryGeneral<T>::getAll() {
    return this->elements;
}



#endif // REPOSITORYGENERAL_H
