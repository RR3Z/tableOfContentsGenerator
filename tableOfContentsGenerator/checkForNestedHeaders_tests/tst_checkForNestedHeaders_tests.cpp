#include <QtTest>
#include <../tableOfContentsGenerator_main/findHeaders.h>

class checkForNestedHeaders_tests : public QObject
{
    Q_OBJECT
private slots:
    void nestedCorrectHeader();
    void nestedHeaderWithoutOpeningTag();
    void nestedHeaderWithoutClosingTag();
    void noNestedHeader();
};

void checkForNestedHeaders_tests::nestedCorrectHeader()
{
    QList<Header> headersList = {};
    Header header = {1, "<h1>H1<h2>H2</h2>1H</h1>", "H1<h2>H2</h2>1H", 0, 23};
    headersList.append(header);

    try
    {
        checkForNestedHeaders(headersList);
    }
    catch (QString exceptionMessage)
    {
        QCOMPARE(exceptionMessage, "Для заголовка '<h1>H1<h2>H2</h2>1H</h1>', который начинается с позиции '0', имеется вложенный заголовок '<h2>H2</h2>'");
    }
}

void checkForNestedHeaders_tests::nestedHeaderWithoutOpeningTag()
{
    QList<Header> headersList = {};
    Header header = {1, "<h1>H1 H2</h2>1H</h1>", "H1 H2</h2>1H", 0, 20};
    headersList.append(header);

    try
    {
        checkForNestedHeaders(headersList);
    }
    catch (QString exceptionMessage)
    {
        QCOMPARE(exceptionMessage, "");
    }
}

void checkForNestedHeaders_tests::nestedHeaderWithoutClosingTag()
{
    QList<Header> headersList = {};
    Header header = {1, "<h1>H1<h2>H2 1H</h1>", "H1<h2>H2 1H", 0, 19};
    headersList.append(header);

    try
    {
        checkForNestedHeaders(headersList);
    }
    catch (QString exceptionMessage)
    {
        QCOMPARE(exceptionMessage, "");
    }
}

void checkForNestedHeaders_tests::noNestedHeader()
{
    QList<Header> headersList = {};
    Header header = {1, "<h1>H1</h1>", "H1", 0, 10};
    headersList.append(header);

    try
    {
        checkForNestedHeaders(headersList);
    }
    catch (QString exceptionMessage)
    {
        QCOMPARE(exceptionMessage, "");
    }
}

QTEST_APPLESS_MAIN(checkForNestedHeaders_tests)

#include "tst_checkForNestedHeaders_tests.moc"
