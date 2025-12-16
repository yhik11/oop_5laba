#include <iostream>
#include "base.h"
#include "derived.h"

void testVirtualVsNonVirtual() {
    std::cout << "\n=== ТЕСТ 1: Виртуальные vs Невиртуальные методы ===" << std::endl;

    Base* basePtr = new Base(100);
    Derived* derivedPtr = new Derived(200, 3.14);

    Base* baseButActuallyDerived = new Derived(300, 6.28);

    std::cout << "\n1. Через указатель на Base:" << std::endl;
    basePtr->print();           // Base::print()
    basePtr->nonVirtualPrint(); // Base::nonVirtualPrint()

    std::cout << "\n2. Через указатель на Derived:" << std::endl;
    derivedPtr->print();           // Derived::print()
    derivedPtr->nonVirtualPrint(); // Derived::nonVirtualPrint()

    std::cout << "\n3. Через Base*, но объект Derived:" << std::endl;
    baseButActuallyDerived->print();           // Derived::print() (ВИРТУАЛЬНЫЙ!)
    baseButActuallyDerived->nonVirtualPrint(); // Base::nonVirtualPrint() (НЕВИРТУАЛЬНЫЙ!)

    // Освобождаем память
    delete basePtr;
    delete derivedPtr;
    delete baseButActuallyDerived;
}



int main() {
    setlocale(LC_ALL, "Russian");
    testVirtualVsNonVirtual();

    return 0;
}