#include <QtTest>
#include <../tableOfContentsGenerator_main/findHeaders.h>

class findSeperateCloseTagHeaders_tests : public QObject
{
    Q_OBJECT

private slots:
    void headerWithoutClosingTag();
    void headerWithoutOpeningTag();
    void correctHeader();
    void nestedHeaderWithoutClosingTag();
    void nestedHeaderWithoutOpeningTag();
    void nestedCorrectHeader();
    void fewHeadersWithoutOpeningTag();
    void commentedHeaderWithoutOpeningTag();
};

void findSeperateCloseTagHeaders_tests::headerWithoutClosingTag()
{
    QString htmlCode = "<html><h1>H1</html>";
    QList<Header> headersList = {};
    QList<int> closeTagHeadersPos = {};

    QList<int> expectedCloseTagHeadersPos = {};

    findSeperateCloseTagHeaders(htmlCode, headersList, closeTagHeadersPos);

    QCOMPARE(closeTagHeadersPos, expectedCloseTagHeadersPos);
}

void findSeperateCloseTagHeaders_tests::headerWithoutOpeningTag()
{
    QString htmlCode = "<html>H1</h1></html>";
    QList<Header> headersList = {};
    QList<int> closeTagHeadersPos = {};

    QList<int> expectedCloseTagHeadersPos = {12};

    findSeperateCloseTagHeaders(htmlCode, headersList, closeTagHeadersPos);

    QCOMPARE(closeTagHeadersPos, expectedCloseTagHeadersPos);
}

void findSeperateCloseTagHeaders_tests::correctHeader()
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
    QList<int> closeTagHeadersPos = {};

    QList<int> expectedCloseTagHeadersPos = {};

    findSeperateCloseTagHeaders(htmlCode, headersList, closeTagHeadersPos);

    QCOMPARE(closeTagHeadersPos, expectedCloseTagHeadersPos);
}

void findSeperateCloseTagHeaders_tests::nestedHeaderWithoutClosingTag()
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
    QList<int> closeTagHeadersPos = {};

    QList<int> expectedCloseTagHeadersPos = {};

    findSeperateCloseTagHeaders(htmlCode, headersList, closeTagHeadersPos);

    QCOMPARE(closeTagHeadersPos, expectedCloseTagHeadersPos);
}

void findSeperateCloseTagHeaders_tests::nestedHeaderWithoutOpeningTag()
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
    QList<int> closeTagHeadersPos = {};

    QList<int> expectedCloseTagHeadersPos = {19};

    findSeperateCloseTagHeaders(htmlCode, headersList, closeTagHeadersPos);

    QCOMPARE(closeTagHeadersPos, expectedCloseTagHeadersPos);
}

void findSeperateCloseTagHeaders_tests::nestedCorrectHeader()
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
    QList<int> closeTagHeadersPos = {};

    QList<int> expectedCloseTagHeadersPos = {};

    findSeperateCloseTagHeaders(htmlCode, headersList, closeTagHeadersPos);

    QCOMPARE(closeTagHeadersPos, expectedCloseTagHeadersPos);
}

void findSeperateCloseTagHeaders_tests::fewHeadersWithoutOpeningTag()
{
    QString htmlCode = "<html>H1</h1>H2</h2>H3</h3></html>";
    QList<Header> headersList = {};
    QList<int> closeTagHeadersPos = {};

    QList<int> expectedCloseTagHeadersPos = {12, 19, 26};

    findSeperateCloseTagHeaders(htmlCode, headersList, closeTagHeadersPos);

    QCOMPARE(closeTagHeadersPos, expectedCloseTagHeadersPos);
}

void findSeperateCloseTagHeaders_tests::commentedHeaderWithoutOpeningTag()
{
    QString htmlCode = "<html><!--H1</h1>-->H2</h2>H3</h3></html>";
    QList<Header> headersList = {};
    QList<int> closeTagHeadersPos = {};

    QList<int> expectedCloseTagHeadersPos = {16, 26, 33};

    findSeperateCloseTagHeaders(htmlCode, headersList, closeTagHeadersPos);

    QCOMPARE(closeTagHeadersPos, expectedCloseTagHeadersPos);
}

QTEST_APPLESS_MAIN(findSeperateCloseTagHeaders_tests)

#include "tst_findseperateclosetagheaders_tests.moc"
