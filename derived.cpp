#include "derived.h"

Derived::Derived() : Base(), extra(0.0) {
    std::cout << "Derived() конструктор #" << getId() << std::endl;
}

Derived::Derived(int val, double extraVal) : Base(val), extra(extraVal) {
    std::cout << "Derived(int, double) конструктор #" << getId()
        << " value=" << value << " extra=" << extra << std::endl;
}

Derived::Derived(const Derived& other) : Base(other), extra(other.extra) {
    std::cout << "Derived(const Derived&) конструктор копирования #" << getId()
        << " из #" << other.getId() << std::endl;
}

Derived::Derived(Derived* other) : Base(other), extra(other->extra) {
    std::cout << "Derived(Derived*) конструктор из указателя #" << getId()
        << " из #" << other->getId() << std::endl;
}

Derived::Derived(Derived& other) : Base(other), extra(other.extra) {
    std::cout << "Derived(Derived&) конструктор из ссылки #" << getId()
        << " из #" << other.getId() << std::endl;
}

Derived::~Derived() {
    std::cout << "~Derived() деструктор #" << getId() << std::endl;
}

void Derived::print() const {
    std::cout << "Derived::print() #" << getId() << " value=" << value
        << " extra=" << extra << std::endl;
}

void Derived::nonVirtualPrint() const {
    std::cout << "Derived::nonVirtualPrint() #" << getId() << " value=" << value
        << " extra=" << extra << std::endl;
}

std::string Derived::className() const {
    return "Derived";
}

bool Derived::isA(const std::string& className) const {
    return (className == "Derived") || Base::isA(className);
}

void Derived::derivedOnly() const {
    std::cout << "Derived::derivedOnly() #" << getId() << " extra=" << extra << std::endl;
}