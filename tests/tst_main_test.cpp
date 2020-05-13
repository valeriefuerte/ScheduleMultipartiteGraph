#include <QtTest>

// add necessary includes here

class main_test : public QObject
{
    Q_OBJECT

public:
    main_test();
    ~main_test();

private slots:
    void test_case1();

};

main_test::main_test()
{

}

main_test::~main_test()
{

}

void main_test::test_case1()
{

}

QTEST_APPLESS_MAIN(main_test)

#include "tst_main_test.moc"
