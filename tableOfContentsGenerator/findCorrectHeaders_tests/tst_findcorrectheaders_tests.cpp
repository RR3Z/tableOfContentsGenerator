#include <QtTest>
#include <../tableOfContentsGenerator_main/tableOfContentsGenerator.h>

class findCorrectHeaders_tests : public QObject
{
    Q_OBJECT

private slots:
    void noCorrectHeaders();
    void correctHeadersAreAvailable();
    void correctHeaderAndHeaderWithoutOpeningTag();
    void correctHeaderAndHeaderWithoutClosingTag();
    void commentedCorrectHeader();
    void commentedText();
    void commentedHeaderWithoutOpeningTag();
    void commentedHeaderWithoutClosingTag();
    void correctHeaderWithAttribute();
};

void findCorrectHeaders_tests::noCorrectHeaders()
{
    QString htmlCode = "<html></html>";
    QList<Header> headersList = {};
    QList<Header> expectedHeadersList = {};

    findCorrectHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findCorrectHeaders_tests::correctHeadersAreAvailable()
{
    QString htmlCode = "<html><h1>H1</h1><h2>H2</h2></html>";
    QList<Header> headersList = {};

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 1;
    header.content = "H1";
    header.rawData = "<h1>H1</h1>";
    header.startPos = 6;
    header.endPos = 16;
    expectedHeadersList.append(header);
    header.level = 2;
    header.content = "H2";
    header.rawData = "<h2>H2</h2>";
    header.startPos = 17;
    header.endPos = 27;
    expectedHeadersList.append(header);

    findCorrectHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findCorrectHeaders_tests::correctHeaderAndHeaderWithoutOpeningTag()
{
    QString htmlCode = "<html><h1>H1</h1>H1</h1></html>";
    QList<Header> headersList = {};

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 1;
    header.content = "H1";
    header.rawData = "<h1>H1</h1>";
    header.startPos = 6;
    header.endPos = 16;
    expectedHeadersList.append(header);

    findCorrectHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findCorrectHeaders_tests::correctHeaderAndHeaderWithoutClosingTag()
{
    QString htmlCode = "<html><h1>H1</h1><h1>H1</html>";
    QList<Header> headersList = {};

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 1;
    header.content = "H1";
    header.rawData = "<h1>H1</h1>";
    header.startPos = 6;
    header.endPos = 16;
    expectedHeadersList.append(header);

    findCorrectHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findCorrectHeaders_tests::commentedCorrectHeader()
{
    QString htmlCode = "<html><h1>H1</h1><!--<h1>H2</h1>--></html>";
    QList<Header> headersList = {};

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 1;
    header.content = "H1";
    header.rawData = "<h1>H1</h1>";
    header.startPos = 6;
    header.endPos = 16;
    expectedHeadersList.append(header);
    header.level = 1;
    header.content = "H2";
    header.rawData = "<h1>H2</h1>";
    header.startPos = 21;
    header.endPos = 31;
    expectedHeadersList.append(header);

    findCorrectHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findCorrectHeaders_tests::commentedText()
{
    QString htmlCode = "<html><h1>H1</h1><!--Comment--></html>";
    QList<Header> headersList = {};

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 1;
    header.content = "H1";
    header.rawData = "<h1>H1</h1>";
    header.startPos = 6;
    header.endPos = 16;
    expectedHeadersList.append(header);

    findCorrectHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findCorrectHeaders_tests::commentedHeaderWithoutOpeningTag()
{
    QString htmlCode = "<html><h1>H1</h1><!--H2</h1>--></html>";
    QList<Header> headersList = {};

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 1;
    header.content = "H1";
    header.rawData = "<h1>H1</h1>";
    header.startPos = 6;
    header.endPos = 16;
    expectedHeadersList.append(header);

    findCorrectHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findCorrectHeaders_tests::commentedHeaderWithoutClosingTag()
{
    QString htmlCode = "<html><h1>H1</h1><!--<h1>H2--></html>";
    QList<Header> headersList = {};

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 1;
    header.content = "H1";
    header.rawData = "<h1>H1</h1>";
    header.startPos = 6;
    header.endPos = 16;
    expectedHeadersList.append(header);

    findCorrectHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findCorrectHeaders_tests::correctHeaderWithAttribute()
{
    QString htmlCode = "<html><h1 class=\"my-heading\">H1</h1></html>";
    QList<Header> headersList = {};

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 1;
    header.content = "H1";
    header.rawData = "<h1 class=\"my-heading\">H1</h1>";
    header.startPos = 6;
    header.endPos = 35;
    expectedHeadersList.append(header);

    findCorrectHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

QTEST_APPLESS_MAIN(findCorrectHeaders_tests)

#include "tst_findcorrectheaders_tests.moc"
