# enum_traits

## Motivation

Нужно конвертировать значения enum-а в строку, получать список значений и пр. Единственное найденное [решение](https://github.com/aantron/better-enums), которое не выглядит как чей-то личный велосипед меня не устраивает по нескольким причинам. Главная:

> The biggest limitation is that the BETTER_ENUM macro can't be used inside a class. This seems difficult to remove.

QMetaEnum тоже немного не так выглядит, как хотелось.

## Dependencies

boost

## Usage

Добавить путь до папки `include` в `include directories` проекта.

Пример использования совместно с `Q_ENUM`:

```c++
// enumtraitstest.h

#ifndef ENUMTRAITSTEST_H
#define ENUMTRAITSTEST_H

#include <QObject>
#include <utils/enum_traits.hpp>

class EnumTraitsTest : public QObject
{
    Q_OBJECT
public:
    explicit EnumTraitsTest(QObject *parent = nullptr);

    // Можно внутри нэймспейсов/классов/функций/и т.п.
    ENUM(TestEnum, int, ValueOne, ValueTwo, ValueThree)
    Q_ENUM(TestEnum)

signals:

public slots:
};

// Нельзя внутри нэймспейсов/классов/функций/и т.п.
ENUM_REG(EnumTraitsTest::, TestEnum)

#endif // ENUMTRAITSTEST_H
```

```c++
// enumtraitstest.cpp

#include "enumtraitstest.h"
#include <QDebug>

EnumTraitsTest::EnumTraitsTest(QObject *parent) : QObject(parent)
{
    qDebug() << utils::enum_traits::to_string(TestEnum::ValueOne);
    for (auto val : utils::enum_traits::values<TestEnum>()) {
        qDebug() << utils::enum_traits::to_string(val) << val;
    }
}
```
