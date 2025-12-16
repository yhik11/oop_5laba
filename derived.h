#ifndef DERIVED_H
#define DERIVED_H

#include "base.h"

class Derived : public Base {
private:
    double extra;

public:
    Derived();
    Derived(int val, double extraVal);
    Derived(const Derived& other);
    Derived(Derived* other);
    Derived(Derived& other);
    ~Derived() override;

    void print() const override;        // Переопределяем виртуальный
    void nonVirtualPrint() const;       // Перекрываем невиртуальный

    std::string className() const override;
    bool isA(const std::string& className) const override;

    void derivedOnly() const;

    double getExtra() const { return extra; }
};

#endif // DERIVED_H