//
// Created by Mr.X on 2022-05-10-0010.
//

#include "Student.h"

Student::Student(const char *name, const char *address, const char *phone,
                 const char *postCode, const char *eMail) {
    this->name = name;
    this->address = address;
    this->phone = phone;
    this->postCode = postCode;
    this->eMail = eMail;
}

const QString &Student::getPhone() const {
    return phone;
}

const QString &Student::getPostCode() const {
    return postCode;
}

const QString &Student::getEMail() const {
    return eMail;
}

const QString &Student::getName() const {
    return name;
}

const QString &Student::getAddress() const {
    return address;
}

void Student::setName(const char *n) {
    Student::name = n;
}

void Student::setName(const QString &n) {
    Student::name = n;
}

void Student::setAddress(const char *a) {
    Student::address = a;
}

void Student::setAddress(const QString &a) {
    Student::address = a;
}

void Student::setPhone(const char *p) {
    Student::phone = p;
}

void Student::setPostCode(const char *p) {
    Student::postCode = p;
}

void Student::setEMail(const char *e) {
    Student::eMail = e;
}

const char *Student::getCharName() const {
    return name.toStdString().c_str();
}

const char *Student::getCharAddress() const {
    return address.toStdString().c_str();
}

const char *Student::getCharPhone() const {
    return phone.toStdString().c_str();
}

const char *Student::getCharPostCode() const {
    return postCode.toStdString().c_str();
}

const char *Student::getCharEMail() const {
    return eMail.toStdString().c_str();
}

std::string Student::toString() {
    return std::string("Student(Name = \"").append(name.toStdString())
            .append("\", Address = \"").append(address.toStdString())
            .append("\", Phone = \"").append(phone.toStdString())
            .append("\", PostCode = \"").append(postCode.toStdString())
            .append("\", E-Mail = \"").append(eMail.toStdString())
            .append("\")");
}

Student::Student() = default;
