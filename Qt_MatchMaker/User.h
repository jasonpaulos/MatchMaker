#ifndef USER_H
#define USER_H

#include <QString>
#include "Point.h"

class User{
public:
    explicit User(const QString &name, Gender gender, unsigned int dimensions);

    QString name;
    Gender gender;
    Point answers;
    std::vector<const User*> matches;
};

#endif // USER_H
