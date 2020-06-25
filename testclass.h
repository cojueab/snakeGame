#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <QObject>
#include <QTest>
class TestClass : public QObject
{
    Q_OBJECT

public:
    explicit TestClass(QObject *parent=0);

private slots:
    void toUpper();
};
//QTEST_MAIN(TestClass)
#endif // TESTCLASS_H
