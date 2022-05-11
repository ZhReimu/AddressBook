//
// Created by Mr.X on 2022-05-10-0010.
//

#ifndef CLIONPROJECTS_STUDENT_H
#define CLIONPROJECTS_STUDENT_H


#include <QString>
#include <ostream>

class Student {

private:
    QString name;
    QString address;
    QString phone;
    QString postCode;
    QString eMail;
public:
    static Student EMPTY_STUDENT;

    Student();

    Student(const char *name, const char *address, const char *phone,
            const char *postCode, const char *eMail);

    const QString &getName() const;

    const QString &getAddress() const;

    const QString &getPhone() const;

    const QString &getPostCode() const;

    const QString &getEMail() const;

    const char *getCharName() const;

    const char *getCharAddress() const;

    const char *getCharPhone() const;

    const char *getCharPostCode() const;

    const char *getCharEMail() const;

    void setName(const char *name);

    void setAddress(const char *address);

    void setPhone(const char *phone);

    void setPostCode(const char *postCode);

    void setEMail(const char *eMail);

    void setName(const QString &n);

    void setAddress(const QString &a);

    std::string toString();

    friend std::ostream &operator<<(std::ostream &os, Student student);

};


#endif //CLIONPROJECTS_STUDENT_H
