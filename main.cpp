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


void testVirtualDestructors() {
    std::cout << "\n=== ТЕСТ 2: Виртуальные деструкторы ===" << std::endl;

    std::cout << "\n1. Без виртуального деструктора (проблема):" << std::endl;
    std::cout << "   Base* obj = new Derived();" << std::endl;
    std::cout << "   delete obj; // Вызовется только ~Base(), а не ~Derived()!" << std::endl;

    std::cout << "\n2. С виртуальным деструктором (правильно):" << std::endl;
    Base* obj = new Derived(400, 2.71);
    std::cout << "   Сейчас вызовется delete obj:" << std::endl;
    delete obj; // Вызовется ~Derived(), потом ~Base()

    std::cout << "\n3. Демонстрация порядка вызова деструкторов:" << std::endl;
    {
        Derived localObj(500, 1.41);
        std::cout << "   Создан локальный объект Derived" << std::endl;
        // При выходе из блока вызовется ~Derived(), потом ~Base()
    }
    std::cout << "   Локальный объект уничтожен" << std::endl;
}

void testClassChecking() {
    std::cout << "\n=== ТЕСТ 3: Проверка на принадлежность классу ===" << std::endl;

    Base baseObj(600);
    Derived derivedObj(700, 1.618);
    Base* polymorphicObj = new Derived(800, 3.333);

    std::cout << "\n1. Метод className():" << std::endl;
    std::cout << "   baseObj.className() = " << baseObj.className() << std::endl;
    std::cout << "   derivedObj.className() = " << derivedObj.className() << std::endl;
    std::cout << "   polymorphicObj->className() = " << polymorphicObj->className() << std::endl;

    std::cout << "\n2. Метод isA():" << std::endl;
    std::cout << "   baseObj.isA(\"Base\") = " << (baseObj.isA("Base") ? "true" : "false") << std::endl;
    std::cout << "   baseObj.isA(\"Derived\") = " << (baseObj.isA("Derived") ? "true" : "false") << std::endl;

    std::cout << "   derivedObj.isA(\"Base\") = " << (derivedObj.isA("Base") ? "true" : "false") << std::endl;
    std::cout << "   derivedObj.isA(\"Derived\") = " << (derivedObj.isA("Derived") ? "true" : "false") << std::endl;
    std::cout << "   derivedObj.isA(\"Unknown\") = " << (derivedObj.isA("Unknown") ? "true" : "false") << std::endl;

    std::cout << "\n3. Проблема метода className():" << std::endl;
    std::cout << "   Base* ptr = &derivedObj;" << std::endl;
    Base* ptr = &derivedObj;
    std::cout << "   ptr->className() = " << ptr->className() << " (работает, т.к. виртуальный)" << std::endl;

    delete polymorphicObj;
}


int main() {
    setlocale(LC_ALL, "Russian");
    testVirtualVsNonVirtual();
    testVirtualDestructors();
    testClassChecking();

    return 0;
}