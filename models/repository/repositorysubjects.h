#ifndef REPOSITORYSUBJECTS_H
#define REPOSITORYSUBJECTS_H

#include <QList>
#include "../subject.h"

class repositorySubjects
{
private:
    QList<Subject> subjects;

    QList<Subject>::iterator getIteratorById(int id);
public:
    int currentCount = 0;

    repositorySubjects();
    ~repositorySubjects();

    // Добавить предмет
    void add(Subject data);

    // Удалить предмет
    bool remove(int id);

    // Обновить предмет
    bool update(int id, Subject data);

    // Получить премет
    Subject getById(int id);

    // Получить все редметы
    QList<Subject> getAll();
};

#endif // REPOSITORYSUBJECTS_H
