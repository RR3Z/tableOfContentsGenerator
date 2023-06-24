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
    void nestedHeaderWithCommentedOpeningTag();
    void nestedHeaderWithCommentedClosingTag();
    void nestedHeaderWithCommentedOpeningAndClosingTag();
    void commentedNestedHeader();
    void complexTest();
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
        QCOMPARE(exceptionMessage, "Для заголовка '<h1>H1<h2>H2</h2>1H</h1>', который начинается с позиции '1', имеется вложенный заголовок '<h2>H2</h2>'");
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

void checkForNestedHeaders_tests::nestedHeaderWithCommentedOpeningTag()
{
    QList<Header> headersList = {};
    Header header = {1, "<h1>H1<!--<h1>-->Nested Header</h1></h1>", "H1<!--<h1>-->Nested Header</h1>", 0, 39};
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

void checkForNestedHeaders_tests::nestedHeaderWithCommentedClosingTag()
{
    QList<Header> headersList = {};
    Header header = {1, "<h1>H1<h1>Nested Header<!--</h1>--></h1>", "H1<h1>Nested Header<!--</h1>-->", 0, 39};
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

void checkForNestedHeaders_tests::nestedHeaderWithCommentedOpeningAndClosingTag()
{
    QList<Header> headersList = {};
    Header header = {1, "<h1>H1<!--<h1>-->Nested Header<!--</h1>--></h1>", "H1<!--<h1>-->Nested Header<!--</h1>-->", 0, 46};
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

void checkForNestedHeaders_tests::commentedNestedHeader()
{
    QList<Header> headersList = {};
    Header header = {1, "<h1>H1<!--<h1>Nested Header</h1>--></h1>", "H1<!--<h1>Nested Header</h1>-->", 0, 39};
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

void checkForNestedHeaders_tests::complexTest()
{
    QList<Header> headersList = {};
    Header header = {1, "<h1>H1<!--<h1>Nested Header</h1>--><!--<h2>-->Nested Header 2</h2><h3>Nested Header 3<!--</h3>--><h6>Real nested header</h6></h1>", "H1<!--<h1>Nested Header</h1>--><!--<h2>-->Nested Header 2</h2><h3>Nested Header 3<!--</h3>--><h6>Real nested header</h6>", 0, 0};
    headersList.append(header);

    try
    {
        checkForNestedHeaders(headersList);
    }
    catch (QString exceptionMessage)
    {
        QCOMPARE(exceptionMessage, "Для заголовка '<h1>H1<!--<h1>Nested Header</h1>--><!--<h2>-->Nested Header 2</h2><h3>Nested Header 3<!--</h3>--><h6>Real nested header</h6></h1>', который начинается с позиции '1', имеется вложенный заголовок '<h6>Real nested header</h6>'");
    }
}

QTEST_APPLESS_MAIN(checkForNestedHeaders_tests)

#include "tst_checkForNestedHeaders_tests.moc"
