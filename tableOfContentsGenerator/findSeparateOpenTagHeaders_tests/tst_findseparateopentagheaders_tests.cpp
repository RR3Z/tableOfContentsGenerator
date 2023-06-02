#include <QtTest>
#include <../tableOfContentsGenerator_main/findHeaders.h>

class findSeparateOpenTagHeaders_tests : public QObject
{
    Q_OBJECT
private slots:
    void headerWithoutClosingTag();
    void headerWithoutOpeningTag();
    void correctHeader();
    void nestedHeaderWithoutClosingTag();
    void nestedHeaderWithoutOpeningTag();
    void nestedCorrectHeader();
    void fewHeadersWithoutClosingTag();
    void fewCorrectHeaders();
    void headerWithoutClosingTagWithAttribute();
    void commentedHeaderWithoutClosingTag();
};

void findSeparateOpenTagHeaders_tests::headerWithoutClosingTag()
{
    QString htmlCode = "<html><h1>H1</html>";
    QList<Header> headersList = {};
    QList<int> openTagHeadersPos = {};

    QList<int> expectedOpenTagHeadersPos = {6};

    findSeperateOpenTagHeaders(htmlCode, headersList, openTagHeadersPos);

    QCOMPARE(openTagHeadersPos, expectedOpenTagHeadersPos);
}

void findSeparateOpenTagHeaders_tests::headerWithoutOpeningTag()
{
    QString htmlCode = "<html>H1</h1></html>";
    QList<Header> headersList = {};
    QList<int> openTagHeadersPos = {};

    QList<int> expectedOpenTagHeadersPos = {};

    findSeperateOpenTagHeaders(htmlCode, headersList, openTagHeadersPos);

    QCOMPARE(openTagHeadersPos, expectedOpenTagHeadersPos);
}

void findSeparateOpenTagHeaders_tests::correctHeader()
{
    QString htmlCode = "<html><h1>H1</h1></html>";
    QList<Header> headersList = {};
    Header header;
    header.content = "H1";
    header.rawData = "<h1>H1</h1>";
    header.level = 1;
    header.startPos = 6;
    header.endPos = 16;
    headersList.append(header);
    QList<int> openTagHeadersPos = {};

    QList<int> expectedOpenTagHeadersPos = {};

    findSeperateOpenTagHeaders(htmlCode, headersList, openTagHeadersPos);

    QCOMPARE(openTagHeadersPos, expectedOpenTagHeadersPos);
}

void findSeparateOpenTagHeaders_tests::nestedHeaderWithoutClosingTag()
{
    QString htmlCode = "<html><h1>H1<h2>H2</h1></html>";
    QList<Header> headersList = {};
    Header header;
    header.content = "H1<h2>H2";
    header.rawData = "<h1>H1<h2>H2</h1>";
    header.level = 1;
    header.startPos = 6;
    header.endPos = 22;
    headersList.append(header);
    QList<int> openTagHeadersPos = {};

    QList<int> expectedOpenTagHeadersPos = {12};

    findSeperateOpenTagHeaders(htmlCode, headersList, openTagHeadersPos);

    QCOMPARE(openTagHeadersPos, expectedOpenTagHeadersPos);
}

void findSeparateOpenTagHeaders_tests::nestedHeaderWithoutOpeningTag()
{
    QString htmlCode = "<html><h1>H1 H2</h2></h1></html>";
    QList<Header> headersList = {};
    Header header;
    header.content = "H1 H2</h2>";
    header.rawData = "<h1>H1 H2</h2></h1>";
    header.level = 1;
    header.startPos = 6;
    header.endPos = 24;
    headersList.append(header);
    QList<int> openTagHeadersPos = {};

    QList<int> expectedOpenTagHeadersPos = {};

    findSeperateOpenTagHeaders(htmlCode, headersList, openTagHeadersPos);

    QCOMPARE(openTagHeadersPos, expectedOpenTagHeadersPos);
}

void findSeparateOpenTagHeaders_tests::nestedCorrectHeader()
{
    QString htmlCode = "<html><h1>H1<h2>H2</h2></h1></html>";
    QList<Header> headersList = {};
    Header header;
    header.content = "H1<h2>H2</h2>";
    header.rawData = "<h1>H1<h2>H2</h2></h1>";
    header.level = 1;
    header.startPos = 6;
    header.endPos = 27;
    headersList.append(header);
    header.content = "H2";
    header.rawData = "<h2>H2</h2>";
    header.level = 2;
    header.startPos = 12;
    header.endPos = 22;
    headersList.append(header);
    QList<int> openTagHeadersPos = {};

    QList<int> expectedOpenTagHeadersPos = {};

    findSeperateOpenTagHeaders(htmlCode, headersList, openTagHeadersPos);

    QCOMPARE(openTagHeadersPos, expectedOpenTagHeadersPos);
}

void findSeparateOpenTagHeaders_tests::fewHeadersWithoutClosingTag()
{
    QString htmlCode = "<html><h1>H1<h2>H2<h3>H3</html>";
    QList<Header> headersList = {};
    QList<int> openTagHeadersPos = {};

    QList<int> expectedOpenTagHeadersPos = {6, 12, 18};

    findSeperateOpenTagHeaders(htmlCode, headersList, openTagHeadersPos);

    QCOMPARE(openTagHeadersPos, expectedOpenTagHeadersPos);
}

void findSeparateOpenTagHeaders_tests::fewCorrectHeaders()
{
    QString htmlCode = "<html><h1>H1</h1><h2>H2</h2><h3>H3</h3></html>";
    QList<Header> headersList = {};
    Header header;
    header.content = "H1";
    header.rawData = "<h1>H1</h1>";
    header.level = 1;
    header.startPos = 6;
    header.endPos = 16;
    headersList.append(header);
    header.content = "H2";
    header.rawData = "<h2>H2</h2>";
    header.level = 2;
    header.startPos = 17;
    header.endPos = 27;
    headersList.append(header);
    header.content = "H3";
    header.rawData = "<h3>H3</h3>";
    header.level = 3;
    header.startPos = 28;
    header.endPos = 38;
    headersList.append(header);
    QList<int> openTagHeadersPos = {};

    QList<int> expectedOpenTagHeadersPos = {};

    findSeperateOpenTagHeaders(htmlCode, headersList, openTagHeadersPos);

    QCOMPARE(openTagHeadersPos, expectedOpenTagHeadersPos);
}

void findSeparateOpenTagHeaders_tests::headerWithoutClosingTagWithAttribute()
{
    QString htmlCode = "<html><h1 class=\"my-heading\">H1</html>";
    QList<Header> headersList = {};
    QList<int> openTagHeadersPos = {};

    QList<int> expectedOpenTagHeadersPos = {6};

    findSeperateOpenTagHeaders(htmlCode, headersList, openTagHeadersPos);

    QCOMPARE(openTagHeadersPos, expectedOpenTagHeadersPos);
}

void findSeparateOpenTagHeaders_tests::commentedHeaderWithoutClosingTag()
{
    QString htmlCode = "<html><!--<h1>H1--></html>";
    QList<Header> headersList = {};
    QList<int> openTagHeadersPos = {};

    QList<int> expectedOpenTagHeadersPos = {10};

    findSeperateOpenTagHeaders(htmlCode, headersList, openTagHeadersPos);

    QCOMPARE(openTagHeadersPos, expectedOpenTagHeadersPos);
}

QTEST_APPLESS_MAIN(findSeparateOpenTagHeaders_tests)

#include "tst_findseparateopentagheaders_tests.moc"
