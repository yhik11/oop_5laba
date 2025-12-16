#include <iostream>
#include "base.h"
#include "derived.h"
#include <typeinfo>
#include <memory>

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

Base returnByValue() {
    Base local(1300);
    std::cout << "  returnByValue: создал локальный объект #" << local.getId() << std::endl;
    return local; // Возможна RVO (Return Value Optimization)
}

Base* returnByPointer() {
    Base* obj = new Base(1400);
    std::cout << "  returnByPointer: создал динамический объект #" << obj->getId() << std::endl;
    return obj;
}

Base& returnByReference() {
    static Base staticObj(1500); // static для демонстрации
    std::cout << "  returnByReference: возвращаю ссылку на static объект #" << staticObj.getId() << std::endl;
    return staticObj;
}

Base* returnBadPointer() {
    Base local(1600);
    std::cout << "  returnBadPointer: создал ЛОКАЛЬНЫЙ объект #" << local.getId() << std::endl;
    return &local; // ОПАСНО! Возвращаем указатель на локальную переменную
}
Base* createDerived()
{

    return new Derived(1700, 7.77);
}

void testReturnFromFunctions() {
    std::cout << "\n=== ТЕСТ 6: Возврат объектов из функций ===" << std::endl;

    std::cout << "\n1. Возврат по значению (RVO):" << std::endl;
    Base obj1 = returnByValue();
    std::cout << "   Получили объект #" << obj1.getId() << std::endl;

    std::cout << "\n2. Возврат по указателю (динамическая память):" << std::endl;
    Base* obj2 = returnByPointer();
    std::cout << "   Получили указатель на объект #" << obj2->getId() << std::endl;
    delete obj2; // НЕ ЗАБЫТЬ удалить!

    std::cout << "\n3. Возврат по ссылке (static переменная):" << std::endl;
    Base& obj3 = returnByReference();
    std::cout << "   Получили ссылку на объект #" << obj3.getId() << std::endl;

    std::cout << "\n4. ОПАСНО: возврат указателя на локальную переменную:" << std::endl;
    Base* badPtr = returnBadPointer();
    std::cout << "   Получили указатель, но объект уже уничтожен!" << std::endl;
    // НЕ ИСПОЛЬЗОВАТЬ badPtr!

    std::cout << "\n5. Возврат полиморфного объекта:" << std::endl;
    

    Base* polyObj = createDerived();
    std::cout << "   Создан полиморфный объект #" << polyObj->getId() << std::endl;
    polyObj->print(); // Вызовется Derived::print()
    delete polyObj;
}

void testSmartPointers() {
    std::cout << "\n=== ТЕСТ 7: Умные указатели (unique_ptr) ===" << std::endl;

    std::cout << "\n1. Создание unique_ptr:" << std::endl;
    std::unique_ptr<Base> unique1(new Base(1800));
    std::cout << "   Создан unique_ptr с объектом #" << unique1->getId() << std::endl;

    std::cout << "\n2. make_unique (C++14):" << std::endl;
    auto unique2 = std::make_unique<Derived>(1900, 8.88);
    std::cout << "   Создан unique_ptr через make_unique" << std::endl;
    unique2->print();

    std::cout << "\n3. Перемещение unique_ptr:" << std::endl;
    std::unique_ptr<Base> unique3 = std::move(unique1);
    std::cout << "   unique_ptr перемещён, оригинал теперь nullptr" << std::endl;
    if (!unique1) {
        std::cout << "   unique1 теперь nullptr" << std::endl;
    }

    std::cout << "\n4. НЕЛЬЗЯ копировать unique_ptr:" << std::endl;
    // std::unique_ptr<Base> unique4 = unique3; // Ошибка компиляции!
    std::cout << "   Копирование запрещено" << std::endl;

    std::cout << "\n5. Освобождение при выходе из области видимости:" << std::endl;
    {
        std::unique_ptr<Base> localUnique(new Base(2000));
        std::cout << "   Создан локальный unique_ptr" << std::endl;
        // При выходе из блока вызовется деструктор автоматически
    }
    std::cout << "   Локальный unique_ptr автоматически уничтожен" << std::endl;

    std::cout << "\n6. Полиморфизм с unique_ptr:" << std::endl;
    std::unique_ptr<Base> polyUnique = std::make_unique<Derived>(2100, 9.99);
    polyUnique->print(); // Работает полиморфизм

    std::cout << "\n7. Ручное освобождение:" << std::endl;
    std::unique_ptr<Base> manualUnique(new Base(2200));
    manualUnique.reset(); // Явное освобождение
    std::cout << "   Объект явно освобождён" << std::endl;
}

void testSharedPointers() {
    std::cout << "\n=== ТЕСТ 8: Умные указатели (shared_ptr) ===" << std::endl;

    std::cout << "\n1. Создание shared_ptr:" << std::endl;
    std::shared_ptr<Base> shared1(new Base(2300));
    std::cout << "   Создан shared_ptr, use_count = " << shared1.use_count() << std::endl;

    std::cout << "\n2. make_shared:" << std::endl;
    auto shared2 = std::make_shared<Derived>(2400, 10.10);
    std::cout << "   Создан shared_ptr через make_shared, use_count = " << shared2.use_count() << std::endl;

    std::cout << "\n3. Копирование shared_ptr:" << std::endl;
    std::shared_ptr<Base> shared3 = shared2;
    std::cout << "   Скопирован shared_ptr, use_count = " << shared2.use_count() << std::endl;

    std::cout << "\n4. Несколько владельцев:" << std::endl;
    {
        std::shared_ptr<Base> shared4 = shared2;
        std::cout << "   Ещё один владелец, use_count = " << shared2.use_count() << std::endl;
        // При выходе из блока shared4 уничтожится, счётчик уменьшится
    }
    std::cout << "   Один владелец уничтожен, use_count = " << shared2.use_count() << std::endl;

    std::cout << "\n5. Циклические ссылки (проблема):" << std::endl;
    class Node {
    public:
        std::shared_ptr<Node> next;
        int id;

        Node(int i) : id(i) {
            std::cout << "     Создан Node #" << id << std::endl;
        }

        ~Node() {
            std::cout << "     Уничтожен Node #" << id << std::endl;
        }
    };

    auto node1 = std::make_shared<Node>(1);
    auto node2 = std::make_shared<Node>(2);

    node1->next = node2;
    node2->next = node1; // ЦИКЛИЧЕСКАЯ ССЫЛКА!

    std::cout << "   Создана циклическая ссылка, use_count node1 = " << node1.use_count() << std::endl;
    std::cout << "   Объекты НЕ будут уничтожены автоматически!" << std::endl;

    std::cout << "\n6. weak_ptr для разрыва циклических ссылок:" << std::endl;
    class SafeNode {
    public:
        std::weak_ptr<SafeNode> next; // weak_ptr вместо shared_ptr!
        int id;

        SafeNode(int i) : id(i) {
            std::cout << "     Создан SafeNode #" << id << std::endl;
        }

        ~SafeNode() {
            std::cout << "     Уничтожен SafeNode #" << id << std::endl;
        }
    };

    auto safeNode1 = std::make_shared<SafeNode>(3);
    auto safeNode2 = std::make_shared<SafeNode>(4);

    safeNode1->next = safeNode2;
    safeNode2->next = safeNode1; // weak_ptr не увеличивает use_count

    std::cout << "   Используем weak_ptr, use_count safeNode1 = " << safeNode1.use_count() << std::endl;
    std::cout << "   Объекты будут корректно уничтожены" << std::endl;
}


int main() {
    setlocale(LC_ALL, "Russian");
    testVirtualVsNonVirtual();
    testVirtualDestructors();
    testClassChecking();
    testTypeCasting();
    testParameterPassing();
    testReturnFromFunctions();
    testSmartPointers();
    testSharedPointers();

    return 0;
}