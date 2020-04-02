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
    int currentCount = -1;

    RepositoryGeneral();
    ~RepositoryGeneral();

    // Добавить <T>
    void add(T data);

    // Удалить <T>
    bool remove(int id);

    // Обновить <T>
    bool update(int id, T data);

    // Получить <T>
    T getById(int id);

    // Получить все <T>
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
    this->currentCount++;
    data.id = this->currentCount;
    this->elements.append(data);
}

template <class T>
bool RepositoryGeneral<T>::remove(int id) {
    class QList<T>::iterator it = this->getIteratorById(id);
    if (it != this->elements.end()){
        elements.erase(it);
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
