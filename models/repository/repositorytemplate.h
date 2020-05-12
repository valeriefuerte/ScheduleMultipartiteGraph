#ifndef REPOSITORYTEMPLATE_H
#define REPOSITORYTEMPLATE_H

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
class RepositoryTemplate
{
private:
    // Список всех нод.
    QList<T> elements;

    // Порядковый номер ноды (идентификатор ноды).
    int increment = -1;

    // Наименование класса, с которым работает репозиторий.
    // Нужен для именования файлов и папок, в которых храняться соотвествующие данные.
    QString tname;

    // Наименование папки, в которой храняться данные.
    QString dirStorager = "storage";

    // Наименование папки, в которой храняться данные по данном виду данных.
    QString dir;

    // Инициализация репозитория.
    void init();

    // Проверка ноды.
    void checkNode();

    // Инициализация внутренних переменных.
    void initEnvironment();

    // Инициализация хранилища.
    void initStorage();

    // Получение итератора по идентификатору.
    class QList<T>::iterator getIteratorById(int id);

public:
    RepositoryTemplate();
    ~RepositoryTemplate();

    // Добавить объект.
    int add(T data);

    // Удалить объект.
    bool remove(int id);

    // Удалить объект по индексу

    void removeByIndex(int index);

    // Обновить объект.
    bool update(int id, T data);

    // Получить объект по идентификатору.
    T getById(int id);

    // Получить объект по индексу.
    T getByIndex(int index);

    // Получить объекты по свойствам объекта.
    QList<T> getByParameters(T searchObject);

    // Получить все объекты.
    QList<T> getAll();

    // Начало итератора.
    class QList<T>::iterator begin();

    // Конец итератора.
    class QList<T>::iterator end();

    // Получить текущий инкремент.
    int getIncrement();

    // Получить количество элементов.
    int getAmount();

    QString getTname();

    // Преобразование в json.
    QJsonObject toJson();

    // Преобразование в json.
    void fromJson(QJsonObject);

    // Сохранить все объекты на диск.
    void save();

    // Сохранить все объекты на диск.
    void save(QString string);

    // Загрузить всё с диска.
    void load();
};

// Начало инициализации

template <class T>
RepositoryTemplate<T>::RepositoryTemplate() {
    this->init();
}

template <class T>
void RepositoryTemplate<T>::init() {
    this->checkNode();
    this->initEnvironment();
//    this->initStorage();
//    this->load();
}

template <class T>
void RepositoryTemplate<T>::checkNode() {
    // Проверка на наследование ноды от abstractNodeRepository
    abstractNodeRepository* test = dynamic_cast<abstractNodeRepository*> (new T);
    if (!test) {
        throw std::runtime_error("The type of template does not satisfy the required. The type must be a descendant of the abstractNodeRepository class.");
    }
}

template <class T>
void RepositoryTemplate<T>::initEnvironment() {
    this->tname = T().getClassName();
    this->dir = QString("%1/%2").arg(this->dirStorager).arg(this->tname);
}

template <class T>
void RepositoryTemplate<T>::initStorage() {
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
}

template <class T>
void RepositoryTemplate<T>::fromJson(QJsonObject object) {
    QJsonArray data = object["data"].toArray();
    QJsonObject metadata = object["metadata"].toObject();

    // Считываемпредыдущее положение счетчика
    this->increment = metadata["increment"].toInt();

    // Добавлем в репозиторий данные
    for (auto element : data) {
        T t;
        t.fromJson(element.toObject());
        this->elements.append(t);
    }
}

template <class T>
void RepositoryTemplate<T>::load() {
    // Достаем список файлов для сущности, с которой работает репозиторий
    QDir dir(this->dir);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);
    QFileInfoList list = dir.entryInfoList();

    // Если файлы существуют, то считываем их
    if (!list.empty()){
        // Берем файл последний файл
        QString jsonName = QString("%1/%2").arg(this->dir).arg(list.at(list.size()-1).fileName());

        // Десериализуем
        QFile jsonFile(jsonName);
        jsonFile.open(QFile::ReadOnly);
        QJsonDocument json = QJsonDocument().fromJson(jsonFile.readAll());
        QJsonObject object = json.object();

        this->fromJson(object);
    }
}

// Конец инициализации

template <class T>
class QList<T>::iterator RepositoryTemplate<T>::getIteratorById(int id) {
    class QList<T>::iterator it = std::find_if(this->elements.begin(), this->elements.end(), [id](T element){ return element.id == id; });
    return it;
}

template <class T>
int RepositoryTemplate<T>::add(T data) {
    this->increment++;
    data.id = this->increment;
    this->elements.append(data);
    return data.id;
}

template <class T>
bool RepositoryTemplate<T>::remove(int id) {
    class QList<T>::iterator it = this->getIteratorById(id);
    if (it != this->elements.end()){
        this->elements.erase(it);
        return true;
    }
    return false;
}

template <class T>
bool RepositoryTemplate<T>::update(int id, T data) {
    class QList<T>::iterator it = this->getIteratorById(id);
    if (it != this->elements.end()){
        data.id = id;
        this->elements.replace(std::distance(this->elements.begin(), it), data);
        return true;
    }
    return false;
}

template <class T>
T RepositoryTemplate<T>::getById(int id) {
    class QList<T>::iterator it = this->getIteratorById(id);
    if(it !=this->elements.end()) {
        return *it;
    }
    return T();
}

template <class T>
T RepositoryTemplate<T>::getByIndex(int index) {
     return this->elements[index];
}

template <class T>
void RepositoryTemplate<T>::removeByIndex(int index) {
     this->elements.removeAt(index);
}

template <class T>
QList<T> RepositoryTemplate<T>::getByParameters(T searchObject) {
    QList<T> elements;
    for (T element : this->elements) {
        if (element == searchObject) {
            elements.append(element);
        }
    }
    return elements;
}

template <class T>
QList<T> RepositoryTemplate<T>::getAll() {
     return this->elements;

}

template <class T>
int RepositoryTemplate<T>::getIncrement()
{
    return this->increment;
}

template <class T>
int RepositoryTemplate<T>::getAmount()
{
    return this->elements.size();
}

template <class T>
class QList<T>::iterator RepositoryTemplate<T>::begin()
{
    return this->elements.begin();
}

template <class T>
class QList<T>::iterator RepositoryTemplate<T>::end()
{
    return this->elements.end();
}

template <class T>
QJsonObject RepositoryTemplate<T>::toJson() {
    QJsonArray data;
    QJsonObject metadata;
    QJsonObject object;

    for (T element : this->elements) {
        data.append(element.toJson());
    }
    metadata["increment"] = this->increment;

    object["data"] = data;
    object["metadata"] = metadata;

    return object;
}

template <class T>
void RepositoryTemplate<T>::save() {
    QJsonDocument json;

    QJsonObject object = this->toJson();

    json.setObject(object);

    QString jsonName = QString("storage/%1/%2_%3.json").arg(this->tname).arg(this->tname).arg(time(NULL));
    QFile jsonFine(jsonName);
    jsonFine.open(QFile::WriteOnly);
    jsonFine.write(json.toJson());
}

template <class T>
void RepositoryTemplate<T>::save(QString  filename) {
    QJsonDocument json;

    QJsonObject object = this->toJson();

    json.setObject(object);

    QString jsonName = QString(filename);
    QFile jsonFine(jsonName);
    jsonFine.open(QFile::WriteOnly);
    jsonFine.write(json.toJson());
}

template <class T>
QString RepositoryTemplate<T>::getTname() {
    return this->tname;
}

template <class T>
RepositoryTemplate<T>::~RepositoryTemplate() {
//    this->save();
}
#endif // REPOSITORYTEMPLATE_H
