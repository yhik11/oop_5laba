#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <string>

class Base {
private:
    int id;
    static int nextId;

public:
    Base();
    Base(int value);
    Base(const Base& other);           // Конструктор копирования
    Base(Base* other);                 // Конструктор из указателя
    Base(Base& other);                 // Конструктор из ссылки
    virtual ~Base();                   // Виртуальный деструктор

    virtual void print() const;        // Виртуальный метод
    void nonVirtualPrint() const;      // Невиртуальный метод

    virtual std::string className() const;
    virtual bool isA(const std::string& className) const;

    int getId() const { return id; }

protected:
    int value;
};

#endif // BASE_H