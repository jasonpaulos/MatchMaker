#include "User.h"

User::User(const QString &name, Gender gender, unsigned int dimensions):
    name(name),
    gender(gender),
    answers(dimensions)
{ }
