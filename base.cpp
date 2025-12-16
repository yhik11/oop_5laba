#include "base.h"

int Base::nextId = 1;

Base::Base() : id(nextId++), value(0) {
    std::cout << "Base() конструктор #" << id << std::endl;
}

Base::Base(int val) : id(nextId++), value(val) {
    std::cout << "Base(int) конструктор #" << id << " value=" << value << std::endl;
}

Base::Base(const Base& other) : id(nextId++), value(other.value) {
    std::cout << "Base(const Base&) конструктор копирования #" << id
        << " из #" << other.id << std::endl;
}

Base::Base(Base* other) : id(nextId++), value(other->value) {
    std::cout << "Base(Base*) конструктор из указателя #" << id
        << " из #" << other->id << std::endl;
}

Base::Base(Base& other) : id(nextId++), value(other.value) {
    std::cout << "Base(Base&) конструктор из ссылки #" << id
        << " из #" << other.id << std::endl;
}

Base::~Base() {
    std::cout << "~Base() деструктор #" << id << std::endl;
}

void Base::print() const {
    std::cout << "Base::print() #" << id << " value=" << value << std::endl;
}

void Base::nonVirtualPrint() const {
    std::cout << "Base::nonVirtualPrint() #" << id << " value=" << value << std::endl;
}

std::string Base::className() const {
    return "Base";
}

bool Base::isA(const std::string& className) const {
    return className == "Base";
}