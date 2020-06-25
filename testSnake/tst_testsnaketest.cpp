#include <QString>
#include <QtTest>

class TestSnakeTest : public QObject
{
    Q_OBJECT

public:
    TestSnakeTest();

private Q_SLOTS:
    void testCase1();
};

TestSnakeTest::TestSnakeTest()
{
}

void TestSnakeTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(TestSnakeTest)

#include "tst_testsnaketest.moc"
