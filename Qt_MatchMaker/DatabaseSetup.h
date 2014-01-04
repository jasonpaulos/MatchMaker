#ifndef DATABASESETUP_H
#define DATABASESETUP_H

#include <QStringList>

class DatabaseSetup{
public:
    explicit DatabaseSetup(const QString &table = "",
                           const QString &gender = "",
                           const QString &grade = "",
                           const QString &first = "",
                           const QString &middle = "",
                           const QString &last = "");

    bool hasFirstName() const;
    bool hasMiddleName() const;
    bool hasLastName() const;
    bool hasGrade() const;
    const QString& getTable() const;
    const QString& getGender() const;
    const QString& getGrade() const;
    const QString& getFirstName() const;
    const QString& getMiddleName() const;
    const QString& getLastName() const;
    const QStringList& getQuestions() const;
    void setTable(const QString &t);
    void setGender(const QString &g);
    void setGrade(const QString &g);
    void setFirstName(const QString &name);
    void setMiddleName(const QString &name);
    void setLastName(const QString &name);
    void addQuestion(const QString &name);
    void clearQuestions();

private:
    QString table, gender, grade, firstName, middleName, lastName;
    QStringList questions;
};

#endif // DATABASESETUP_H
