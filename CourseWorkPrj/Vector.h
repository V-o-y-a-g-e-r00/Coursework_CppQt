#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED


// Vector.h==================================
#include <utility> //для вариативного шаблона
#include <iostream>

template <typename T>
class Vector
{
private:
    T* data;
    size_t size;
    size_t capasity;

public:
/*  Итератор*/
    class Iterator
    {
    private:
        Vector* v;
        size_t i;
    public:
        /*  Конструкторы по умолчанию, с параметром, копирования*/
        Iterator();
        Iterator(Vector& r);
        Iterator(const Iterator& r) = default; //конструктор копирования будет создан компилятором автоматически.

        /*  Перегрузка операторов присваивания, инкрементов, сложения_вычитания, сравнения */
        Iterator& operator=(const Iterator& r) = default; //оператор присваивания будет перегружен компилятором автоматически.
        Iterator& operator++();  //prefix
        Iterator operator++(int);//postfix
        Iterator operator+(size_t i)const; //константные методы size_t беззнаковый тип предназначенный для хранения размера массива, индексации массивов и для адресной арифметики. Возвращаемое значение ф-ии sizeof() имеет такой тип.
        Iterator operator-(size_t i)const;
        bool operator==(const Iterator& r);
        bool operator!=(const Iterator& r);
        T& operator*()const;

        friend Vector; //чтобы класс Vector имел доступ к закрытым членам класса Iterator. Обращу внимание, что Vector только включает в себя класс Iterator, но не наследует его, поэтому protected  здесь не сработает.
    };
/*  Константный итератор*/
    class ConstIterator //для временных объектов и константного контейнера.
    {
    private:
        const Vector* v;
        size_t i;
    public:
        /*  Тут все то же самое, что и для обычного итератора, кроме конструктора с параметром и типа возвращаемого значения при разыменовании (и const Vector* v; т.е. указателем на константный вектор). Нужен для работы с константным контейнером*/
        ConstIterator();
        ConstIterator(const Vector& r);
        ConstIterator(const ConstIterator& r) = default;

        ConstIterator& operator=(const ConstIterator& r) = default;
        ConstIterator& operator++();  //prefix
        ConstIterator operator++(int);//postfix
        ConstIterator operator+(size_t i)const;
        ConstIterator operator-(size_t i)const;
        bool operator==(const ConstIterator& r);
        bool operator!=(const ConstIterator& r);
        const T& operator*()const;

        friend Vector;

    };
/*  Конструкторы по-умолчанию, копирования, перемещения. Деструктор*/
    Vector();
    Vector(const Vector& r);
    Vector(Vector&& r) noexcept; //noexcept спецификация исключения. Т.е. сообщаем компилятору, что функция не будет выбрасывать исключения. Нам это малополезно. Это конструктор перемещения. Принимает ссылку на rvalue. Эта ссылка позволяет получать доступ к неконстантным временным объектам. ссылка lvalue на временный объект может быть только константной и не позволяет изменять временный объект. термин "константная ссылка" следует понимать как "ссылка на константу". Этот термин - этакая идиома, поскольку ссылку в любом случае нельзя изменять, т.е. она не может быть не константной.
    ~Vector();

    void pushBack(const T& el); //помещаем в конец вектора элемент el путем вызова конструктора копирования (а именно, с помощью Placement new)
    template <typename ...Args> //variadic temlate (начиная с C++11) вариативный шаблон или шаблон с переменным числом аргументов. где ...Args - пакет типов, args - пакет параметров, типы которых задаются пакетом типов Args. По сути, этот метод принимает набор аргументов, из которых можно построить объект el, этими аргументами могут являтся отсутствие аргументов, тогда сработает конструктор по умолчанию, аргументы конструктора с параметрами или готовый объект. Во всех случаях метод будет использовать семантику перемещения(с этой целью здесь и берется ссылка на rvalue для каждого аргумента из пакета параметров). Т.е. после его работы исходные параметры могут стать недействительными.
    void emplaceBack(Args&&... args);
    void reserve(size_t new_capasity); //Тут выделяем новый кусок памяти под data, если new_capasity больше capasity. При этом мы используем семантику перемещения. Тут важно, чтобы конструктор перемещения класса T ставил nullptr там, где это необходимо. Иначе этот метод во время вызова деструктора может освободить динамическую память, которая уже передана в пользование другому объекту.
    void erase(size_t begin, size_t end); //стираем элементы с begin включительно по end (не включая end).
    void clear(); //вызывает деструкторы всех элементов, оставляя прежнюю вместимость.
    size_t getSize() const;

    Vector& operator=(const Vector& r);

    Iterator begin();
    Iterator end();

    ConstIterator begin()const; //константные методы. Перегрузка 2х методов выше по константности. Для const Vector<someclass> vector1 будет вызываться этот метод, а для Vector<someclass> vector2 будет вызываться метод выше. "выбор делается в соответствии с частью "Best viable function" ( 13.3.3 ) стандарта C++, в которой, короче говоря, говорится, что лучшая функция-это та, которая требует наименьшего количества преобразований для своих аргументов". На практике, можно было бы обойтись без 2х векторов сверху. Однако считается, что каждый метод должен быть в 4х экземплярах foo();foo() const;foo() volatile;foo() const volatile;
    ConstIterator end()const;

    ConstIterator cbegin()const; //А эти методы полностью совпадают с 2мя методами выше.
    ConstIterator cend()const;

    T& operator[](size_t i);
    const T& operator[](size_t i) const; //для работы с     const Vector<someclass> vector1

};
#include "Vector.inl"


#endif // VECTOR_H_INCLUDED
