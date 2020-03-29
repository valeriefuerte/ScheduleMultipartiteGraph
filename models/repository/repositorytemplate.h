#ifndef REPOSITORYGENERAL_H
#define REPOSITORYGENERAL_H

#include <QDebug>
#include <QList>
#include "../abstractnoderepository.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMap>
#include <QFile>
#include <QDir>
#include <ctime>

template <class T>
class RepositoryGeneral
{
private:
    QList<T> elements;

    class QList<T>::iterator getIteratorById(int id);
public:
    int currentCount = -1;
    QString tname;
    QString dirStorager = "storage";
    QString dir;

    RepositoryGeneral();
    ~RepositoryGeneral();

    // Добавить объект
    void add(T data);

    // Удалить объект
    bool remove(int id);

    // Обновить объект
    bool update(int id, T data);

    // Получить объект
    T getById(int id);

    // Получить все объекты
    QList<T> getAll();

    // Сохранить все объекты на диск
    void save();

    // Загрузить всё с диска
    void load();
};

template <class T>
RepositoryGeneral<T>::RepositoryGeneral() {
    abstractNodeRepository* test = dynamic_cast<abstractNodeRepository*> (new T);

    if (!test) {
        throw std::runtime_error("The type of template does not satisfy the required. The type must be a descendant of the abstractNodeRepository class.");
    }
    this->tname = T().getClassName();
    this->dir = QString("%1/%2").arg(this->dirStorager).arg(this->tname);
    this->load();
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

template <class T>
void RepositoryGeneral<T>::load() {
    QDir dirStorage(this->dirStorager);
    QDir dir(this->dir);

    bool ok = dirStorage.exists();
    if (!ok) {
        QDir().mkdir(this->dirStorager);
    }
    ok = dir.exists();
    if (!ok) {
        QDir().mkdir(this->dir);
    }

    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);
    QFileInfoList list = dir.entryInfoList();
    if (!list.empty()){
        QString jsonName = QString("%1/%2").arg(this->dir).arg(list.at(list.size()-1).fileName());

        QFile jsonFile(jsonName);
        jsonFile.open(QFile::ReadOnly);
        QJsonDocument json = QJsonDocument().fromJson(jsonFile.readAll());
        QJsonArray jsonArray = json.array();
        for (auto element : jsonArray) {
            T t;
            t.fromJson(element.toObject());
            this->add(t);
        }
    }
}

template <class T>
void RepositoryGeneral<T>::save() {
    QJsonDocument json;

    QJsonArray array;
    array = json.array();
    if (!this->elements.empty()) {
        for (T element : this->elements) {
            array.append(element.toJson());
        }

        json.setArray(array);

        QString jsonName = QString("storage/%1/%2_%3.json").arg(this->tname).arg(this->tname).arg(time(NULL));

        QFile jsonFine(jsonName);
        jsonFine.open(QFile::WriteOnly);
        jsonFine.write(json.toJson());
    }
}

#endif // REPOSITORYGENERAL_H
