#include "DatabaseSetup.h"

DatabaseSetup::DatabaseSetup(const QString &table,
                             const QString &gender,
                             const QString &grade,
                             const QString &first,
                             const QString &middle,
                             const QString &last):
    table(table),
    gender(gender),
    grade(grade),
    firstName(first),
    middleName(middle),
    lastName(last)
{ }

bool DatabaseSetup::hasFirstName() const{
    return !firstName.isEmpty();
}

bool DatabaseSetup::hasMiddleName() const{
    return !middleName.isEmpty();
}

bool DatabaseSetup::hasLastName() const{
    return !lastName.isEmpty();
}

bool DatabaseSetup::hasGrade() const{
    return !grade.isEmpty();
}

const QString& DatabaseSetup::getTable() const{
    return table;
}

const QString& DatabaseSetup::getGender() const{
    return gender;
}

const QString& DatabaseSetup::getGrade() const{
    return grade;
}

const QString& DatabaseSetup::getFirstName() const{
    return firstName;
}

const QString& DatabaseSetup::getMiddleName() const{
    return middleName;
}

const QString& DatabaseSetup::getLastName() const{
    return lastName;
}

const QStringList& DatabaseSetup::getQuestions() const{
    return questions;
}

void DatabaseSetup::setTable(const QString &t){
    table = t;
}

void DatabaseSetup::setGender(const QString &g){
    gender = g;
}

void DatabaseSetup::setGrade(const QString &g){
    grade = g;
}

void DatabaseSetup::setFirstName(const QString &name){
    firstName = name;
}

void DatabaseSetup::setMiddleName(const QString &name){
    middleName = name;
}

void DatabaseSetup::setLastName(const QString &name){
    lastName = name;
}

void DatabaseSetup::addQuestion(const QString &name){
    questions << name;
}

void DatabaseSetup::clearQuestions(){
    questions.clear();
}
