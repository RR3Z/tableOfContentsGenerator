#include <QtTest>
#include <../tableOfContentsGenerator_main/tableOfContentsGenerator.h>

class isListEmpty_tests : public QObject
{
    Q_OBJECT
private slots:
    void listIsEmpty();
    void listIsNotEmpty();
};

void isListEmpty_tests::listIsNotEmpty()
{
    Header header;
    QList<Header> headersList = {header, header};
    bool expectedResult = false;
    bool functionResult = isListEmpty(headersList);
    QCOMPARE(functionResult,expectedResult);
}

void isListEmpty_tests::listIsEmpty()
{
    QList<Header> headersList = {};
    bool expectedResult = true;
    bool functionResult = isListEmpty(headersList);
    QCOMPARE(functionResult,expectedResult);
}

QTEST_APPLESS_MAIN(isListEmpty_tests)

#include "tst_islistempty_tests.moc"
