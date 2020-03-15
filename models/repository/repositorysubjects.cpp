#include "repositorysubjects.h"

repositorySubjects::repositorySubjects()
{

}

repositorySubjects::~repositorySubjects()
{

}

QList<Subject>::iterator repositorySubjects::getIteratorById(int id) {
    QList<Subject>::iterator it = std::find_if(this->subjects.begin(), this->subjects.end(), [id](Subject subject){ return subject.id == id; });
    return it;
}

void repositorySubjects::add(Subject subject)
{
    this->subjects.append(subject);
}

bool repositorySubjects::remove(int id)
{
    QList<Subject>::iterator it = this->getIteratorById(id);
    if (it != subjects.end()){
        this->subjects.erase(it);
        return true;
    }
    return false;
}

bool repositorySubjects::update(int id, Subject subject)
{
    if(this->remove(id)) {
        this->add(subject);
        return true;
    }
    return false;
}

Subject repositorySubjects::getById(int id)
{
    QList<Subject>::iterator it = this->getIteratorById(id);
    if(it != subjects.end()) {
        return *it;
    }
    return Subject();
}

QList<Subject> repositorySubjects::getAll() {
    return this->subjects;
}
