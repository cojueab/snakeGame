#include "testclass.h"
#include <QtTest/QTest>
#include <windowgame.h>

TestClass::TestClass(QObject *parent)
{
}
\

void TestClass::toUpper(){
    QString str = "Hello";
    QVERIFY(str.toUpper() == "HELLO");
}
