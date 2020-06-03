#ifndef PLANET_H
#define PLANET_H

#include <QString>

struct Planet{
    Planet(const QString& name = QString(), double gravity = 0.0,
           double density = 0.0):
        m_name(name), m_gravity(gravity), m_density(density){
    }

    QString m_name;
    double m_gravity;
    double m_density;
};

#endif // PLANET_H
