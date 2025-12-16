#include <iostream>
#include "base.h"
#include "derived.h"
#include <typeinfo>

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

void testTypeCasting() {
    std::cout << "\n=== ТЕСТ 4: Приведение типов ===" << std::endl;

    Base* obj1 = new Base(900);
    Base* obj2 = new Derived(1000, 4.44);

    std::cout << "\n1. Опасное приведение (static_cast):" << std::endl;
    Derived* dangerousCast = static_cast<Derived*>(obj1);
    std::cout << "   Derived* dangerousCast = static_cast<Derived*>(obj1);" << std::endl;
    std::cout << "   dangerousCast->getExtra() = ";
    // ОПАСНО! Может привести к неопределённому поведению
    // std::cout << dangerousCast->getExtra() << std::endl; // Не вызывать!
    std::cout << "НЕВЫЗЫВАТЬ! (опасно)" << std::endl;

    std::cout << "\n2. Безопасное приведение (dynamic_cast):" << std::endl;
    Derived* safeCast1 = dynamic_cast<Derived*>(obj1);
    if (safeCast1) {
        std::cout << "   dynamic_cast<Derived*>(obj1) успешен" << std::endl;
    }
    else {
        std::cout << "   dynamic_cast<Derived*>(obj1) вернул nullptr" << std::endl;
    }

    Derived* safeCast2 = dynamic_cast<Derived*>(obj2);
    if (safeCast2) {
        std::cout << "   dynamic_cast<Derived*>(obj2) успешен" << std::endl;
        safeCast2->derivedOnly(); // Безопасный вызов
    }

    std::cout << "\n3. С помощью isA():" << std::endl;
    if (obj1->isA("Derived")) {
        Derived* casted = static_cast<Derived*>(obj1);
        std::cout << "   obj1 можно привести к Derived" << std::endl;
    }
    else {
        std::cout << "   obj1 НЕЛЬЗЯ привести к Derived" << std::endl;
    }

    std::cout << "\n4. typeid (RTTI):" << std::endl;
    std::cout << "   typeid(*obj1).name() = " << typeid(*obj1).name() << std::endl;
    std::cout << "   typeid(*obj2).name() = " << typeid(*obj2).name() << std::endl;

    delete obj1;
    delete obj2;
}

void funcByValue(Base obj) {
    std::cout << "  funcByValue: получил объект #" << obj.getId() << std::endl;
}

void funcByPointer(Base* obj) {
    std::cout << "  funcByPointer: получил указатель на объект #" << obj->getId() << std::endl;
}

void funcByReference(Base& obj) {
    std::cout << "  funcByReference: получил ссылку на объект #" << obj.getId() << std::endl;
}

void testParameterPassing() {
    std::cout << "\n=== ТЕСТ 5: Передача объектов как параметров ===" << std::endl;

    Base baseObj(1100);
    Derived derivedObj(1200, 5.55);

    std::cout << "\n1. Передача Base по значению:" << std::endl;
    funcByValue(baseObj);

    std::cout << "\n2. Передача Base по указателю:" << std::endl;
    funcByPointer(&baseObj);

    std::cout << "\n3. Передача Base по ссылке:" << std::endl;
    funcByReference(baseObj);

    std::cout << "\n4. Передача Derived как Base (срезка):" << std::endl;
    std::cout << "   funcByValue(derivedObj):" << std::endl;
    funcByValue(derivedObj); // СРЕЗКА! Теряется часть Derived

    std::cout << "\n5. Передача Derived по указателю (полиморфизм):" << std::endl;
    std::cout << "   funcByPointer(&derivedObj):" << std::endl;
    funcByPointer(&derivedObj);

    std::cout << "\n6. Передача Derived по ссылке (полиморфизм):" << std::endl;
    std::cout << "   funcByReference(derivedObj):" << std::endl;
    funcByReference(derivedObj);

    std::cout << "\n7. Проблема срезки (object slicing):" << std::endl;
    Base sliced = derivedObj; // Создаётся новый Base, копируются только поля Base
    std::cout << "   Base sliced = derivedObj; // Произошла срезка" << std::endl;
    std::cout << "   sliced.className() = " << sliced.className() << " (всегда Base)" << std::endl;
}


int main() {
    setlocale(LC_ALL, "Russian");
    testVirtualVsNonVirtual();
    testVirtualDestructors();
    testClassChecking();
    testTypeCasting();
    testParameterPassing();

    return 0;
}