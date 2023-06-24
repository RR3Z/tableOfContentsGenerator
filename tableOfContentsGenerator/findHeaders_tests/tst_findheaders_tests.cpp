#include <QtTest>
#include <../tableOfContentsGenerator_main/findHeaders.h>

class findHeaders_tests : public QObject
{
    Q_OBJECT

private slots:
    void headersAreAvailable();
    void headersAreMissing();
    void nestedHeaderIsAvailable();
    void headerWithoutOpeningTag();
    void headerWithoutClosingTag();
    void fewCommentedCorrectHeaders();
    void fewCommentedHeadersWithoutOpeningTag();
    void fewCommentedHeadersWithoutClosingTag();
    void commentedCorrectAndUncorrectHeaders();
    void firstRealSite();
    void secondRealSite();
    void coupleOfHeaders();
    void headerOpeningTagWithAttributes();
    void headerWithLinkInContent();
    void openingTagSeparatedFromTheRestOfTheHeader();
    void closingTagSeparatedFromTheRestOfTheHeader();
    void headerContentIsSeparatedFromTheTags();
    void nestedHeaderWithoutClosingTag();
    void nestedHeaderWithoutOpeningTag();
    void nestedHeaderWithoutOpeningTagInNestedHeader();
    void complexTest();
    void nestedCorrectHeaderInComment();
    void correctHeaderAndHeaderWithoutOpeningTag();
    void correctHeaderAndHeaderWithoutClosingTag();
    void correctHeaderWithAttrubutes();
    void correctHeaderWithCommentedOpeningTag();
    void correctHeaderWithCommentedClosingTag();
    void correctHeaderWithCommentedOpeningAndClosingTag();
    void commentInCorrectHeaderContent();
    void commentedNestedHeaderOpeningTag();
    void commentedNestedHeaderClosingTag();
};

void findHeaders_tests::headersAreAvailable()
{
    QString htmlCode = "<html><h1>H1</h1><h2>H2</h2></html>";
    QList<Header> headersList;

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

    findHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findHeaders_tests::headersAreMissing()
{
    QString htmlCode = "<html></html>";
    QList<Header> headersList = {};

    QList<Header> expectedHeadersList = {};

    findHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findHeaders_tests::nestedHeaderIsAvailable()
{
    QString htmlCode = "<html><h1>H1<h2>H2</h2></h1></html>";
    QList<Header> headersList;

    try
    {
        findHeaders(htmlCode, headersList);
    }
    catch(QString exception)
    {
        QCOMPARE(exception, "Для заголовка '<h1>H1<h2>H2</h2></h1>', который начинается с позиции '7', имеется вложенный заголовок '<h2>H2</h2>'");
    }

    QCOMPARE(headersList.count(), 1);
}

void findHeaders_tests::headerWithoutOpeningTag()
{
    QString htmlCode = "<html>H1</h1></html>";
    QList<Header> headersList;

    try
    {
        findHeaders(htmlCode, headersList);
    }
    catch(QString exception)
    {
        QCOMPARE(exception, "Для заголовка, который заканчивается на позиции '13', отсутствует открывающий тег");
    }

    QCOMPARE(headersList.count(), 0);
}

void findHeaders_tests::headerWithoutClosingTag()
{
    QString htmlCode = "<html><h1>H1</html>";
    QList<Header> headersList;

    try
    {
        findHeaders(htmlCode, headersList);
    }
    catch(QString exception)
    {
        QCOMPARE(exception, "Для заголовка, который начинается на позиции '7', отсутствует закрывающий тег");
    }

    QCOMPARE(headersList.count(), 0);
}

void findHeaders_tests::correctHeaderAndHeaderWithoutOpeningTag()
{
    QString htmlCode = "<html><h1>Header</h1>H1</h1></html>";
    QList<Header> headersList;

    try
    {
        findHeaders(htmlCode, headersList);
    }
    catch(QString exception)
    {
        QCOMPARE(exception, "Для заголовка, который заканчивается на позиции '28', отсутствует открывающий тег");
    }

    QCOMPARE(headersList.count(), 1);
}

void findHeaders_tests::correctHeaderAndHeaderWithoutClosingTag()
{
    QString htmlCode = "<html><h1>Header</h1><h1>H1</html>";
    QList<Header> headersList;

    try
    {
        findHeaders(htmlCode, headersList);
    }
    catch(QString exception)
    {
        QCOMPARE(exception, "Для заголовка, который начинается на позиции '22', отсутствует закрывающий тег");
    }

    QCOMPARE(headersList.count(), 1);
}

void findHeaders_tests::fewCommentedCorrectHeaders()
{
    QString htmlCode = "<html><h1>H1</h1><!--<h2>H2</h2>--><!--<h3>H3</h3>--><!--<h4>H4</h4>--></html>";
    QList<Header> headersList;

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 1;
    header.content = "H1";
    header.rawData = "<h1>H1</h1>";
    header.startPos = 6;
    header.endPos = 16;
    expectedHeadersList.append(header);

    findHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findHeaders_tests::fewCommentedHeadersWithoutOpeningTag()
{
    QString htmlCode = "<html><h1>H1</h1><!--H2</h2>--><!--H3</h3>--><!--H4</h4>--></html>";
    QList<Header> headersList;

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 1;
    header.content = "H1";
    header.rawData = "<h1>H1</h1>";
    header.startPos = 6;
    header.endPos = 16;
    expectedHeadersList.append(header);

    findHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findHeaders_tests::fewCommentedHeadersWithoutClosingTag()
{
    QString htmlCode = "<html><h1>H1</h1><!--<h2>H2--><!--<h3>H3--><!--<h4>H4--></html>";
    QList<Header> headersList;

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 1;
    header.content = "H1";
    header.rawData = "<h1>H1</h1>";
    header.startPos = 6;
    header.endPos = 16;
    expectedHeadersList.append(header);

    findHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findHeaders_tests::commentedCorrectAndUncorrectHeaders()
{
    QString htmlCode = "<html><h1>H1</h1><!--<h2>H2</h2>--><!--<h3>H3--><!--H4</h4>--></html>";
    QList<Header> headersList;

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 1;
    header.content = "H1";
    header.rawData = "<h1>H1</h1>";
    header.startPos = 6;
    header.endPos = 16;
    expectedHeadersList.append(header);

    findHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findHeaders_tests::coupleOfHeaders()
{
    QString htmlCode;
    QList<Header> headersList;

    // Считать содержимое файла
    QFile file("../../testFiles/findHeaders_tests/coupleOfHeadersTest.html");
    QTextStream in(&file);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        htmlCode = in.readAll();
    }
    file.close();

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 1;
    header.content = "Заголовок уровня 1";
    header.rawData = "<h1>Заголовок уровня 1</h1>";
    header.startPos = 81;
    header.endPos = 107;
    expectedHeadersList.append(header);
    header.level = 2;
    header.content = "Заголовок уровня 2";
    header.rawData = "<h2>Заголовок уровня 2</h2>";
    header.startPos = 186;
    header.endPos = 212;
    expectedHeadersList.append(header);
    header.level = 3;
    header.content = "Заголовок уровня 3";
    header.rawData = "<h3>Заголовок уровня 3</h3>";
    header.startPos = 290;
    header.endPos = 316;
    expectedHeadersList.append(header);
    header.level = 4;
    header.content = "Заголовок уровня 4";
    header.rawData = "<h4>Заголовок уровня 4</h4>";
    header.startPos = 337;
    header.endPos = 363;
    expectedHeadersList.append(header);
    header.level = 5;
    header.content = "Заголовок уровня 5";
    header.rawData = "<h5>Заголовок уровня 5</h5>";
    header.startPos = 439;
    header.endPos = 465;
    expectedHeadersList.append(header);
    header.level = 6;
    header.content = "Заголовок уровня 6";
    header.rawData = "<h6>Заголовок уровня 6</h6>";
    header.startPos = 551;
    header.endPos = 577;
    expectedHeadersList.append(header);
    header.level = 2;
    header.content = "Другой заголовок уровня 2";
    header.rawData = "<h2>Другой заголовок уровня 2</h2>";
    header.startPos = 584;
    header.endPos = 617;
    expectedHeadersList.append(header);
    header.level = 3;
    header.content = "Еще один заголовок уровня 3";
    header.rawData = "<h3>Еще один заголовок уровня 3</h3>";
    header.startPos = 669;
    header.endPos = 704;
    expectedHeadersList.append(header);
    header.level = 6;
    header.content = "Заголовок уровня 6 в подвале";
    header.rawData = "<h6>Заголовок уровня 6 в подвале</h6>";
    header.startPos = 724;
    header.endPos = 760;
    expectedHeadersList.append(header);

    findHeaders(htmlCode, headersList);
    QCOMPARE(headersList, expectedHeadersList);
}

void findHeaders_tests::firstRealSite()
{
    QString htmlCode;
    QList<Header> headersList;

    // Считать содержимое файла
    QFile file("../../testFiles/findHeaders_tests/firstRealSiteTest.html");
    QTextStream in(&file);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        htmlCode = in.readAll();
    }
    file.close();

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 1;
    header.content = "Example Domain";
    header.rawData = "<h1>Example Domain</h1>";
    header.startPos = 42065;
    header.endPos = 42087;
    expectedHeadersList.append(header);

    findHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findHeaders_tests::secondRealSite()
{
    QString htmlCode;
    QList<Header> headersList;

    // Считать содержимое файла
    QFile file("../../testFiles/findHeaders_tests/secondRealSiteTest.html");
    QTextStream in(&file);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        htmlCode = in.readAll();
    }
    file.close();

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 3;
    header.content = "Thanks for stopping by!";
    header.rawData = "<h3>Thanks for stopping by!</h3>";
    header.startPos = 41516;
    header.endPos = 41547;
    expectedHeadersList.append(header);
    header.level = 3;
    header.content = "Looking to buy beta.com?";
    header.rawData = "<h3>Looking to buy beta.com?</h3>";
    header.startPos = 41702;
    header.endPos = 41734;
    expectedHeadersList.append(header);

    findHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findHeaders_tests::headerOpeningTagWithAttributes()
{
    QString htmlCode = "<h1 class=\"header-title\" style=\"color: red;\">Пример текста</h1>";
    QList<Header> headersList;

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 1;
    header.content = "Пример текста";
    header.rawData = "<h1 class=\"header-title\" style=\"color: red;\">Пример текста</h1>";
    header.startPos = 0;
    header.endPos = 62;
    expectedHeadersList.append(header);

    findHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findHeaders_tests::headerWithLinkInContent()
{
    QString htmlCode = "<h1><a href=\"https://www.example.com\">Заголовок с ссылкой</a></h1>";
    QList<Header> headersList;

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 1;
    header.content = "<a href=\"https://www.example.com\">Заголовок с ссылкой</a>";
    header.rawData = "<h1><a href=\"https://www.example.com\">Заголовок с ссылкой</a></h1>";
    header.startPos = 0;
    header.endPos = 65;
    expectedHeadersList.append(header);

    findHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findHeaders_tests::openingTagSeparatedFromTheRestOfTheHeader()
{
    QString htmlCode = "<h1>\nH1</h1>";
    QList<Header> headersList;

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 1;
    header.content = "\nH1";
    header.rawData = "<h1>\nH1</h1>";
    header.startPos = 0;
    header.endPos = 11;
    expectedHeadersList.append(header);

    findHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findHeaders_tests::closingTagSeparatedFromTheRestOfTheHeader()
{
    QString htmlCode = "<h1>H1\n</h1>";
    QList<Header> headersList;

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 1;
    header.content = "H1\n";
    header.rawData = "<h1>H1\n</h1>";
    header.startPos = 0;
    header.endPos = 11;
    expectedHeadersList.append(header);

    findHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findHeaders_tests::headerContentIsSeparatedFromTheTags()
{
    QString htmlCode = "<h1>\nH1\n</h1>";
    QList<Header> headersList;

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 1;
    header.content = "\nH1\n";
    header.rawData = "<h1>\nH1\n</h1>";
    header.startPos = 0;
    header.endPos = 12;
    expectedHeadersList.append(header);

    findHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findHeaders_tests::nestedHeaderWithoutClosingTag()
{
    QString htmlCode = "<h1>H1<h2>H2</h1>";
    QList<Header> headersList;

    try
    {
        findHeaders(htmlCode, headersList);
    }
    catch(QString exception)
    {
        QCOMPARE(exception, "Для заголовка, который начинается на позиции '7', отсутствует закрывающий тег");
    }

    QCOMPARE(headersList.count(), 1);
}

void findHeaders_tests::nestedHeaderWithoutOpeningTag()
{
    QString htmlCode = "<h1>H1 H2</h2></h1>";
    QList<Header> headersList;

    try
    {
        findHeaders(htmlCode, headersList);
    }
    catch(QString exception)
    {
        QCOMPARE(exception, "Для заголовка, который заканчивается на позиции '14', отсутствует открывающий тег");
    }

    QCOMPARE(headersList.count(), 1);
}

void findHeaders_tests::nestedHeaderWithoutOpeningTagInNestedHeader()
{
    QString htmlCode = "<h1>H1<h2>H3</h3>H2</h2></h1>";
    QList<Header> headersList;

    try
    {
        findHeaders(htmlCode, headersList);
    }
    catch(QString exception)
    {
        QCOMPARE(exception, "Для заголовка '<h1>H1<h2>H3</h3>H2</h2></h1>', который начинается с позиции '1', имеется вложенный заголовок '<h2>H3</h3>H2</h2>'");
    }

    QCOMPARE(headersList.count(), 1);
}

void findHeaders_tests::complexTest()
{
    QString htmlCode = "<html>\n<!-- Уровень 1: Заголовок первого уровня -->\n<h1>Заголовок первого уровня\n</h1>\n<!-- Уровень 2: Заголовок второго уровня -->\n<h2>\nЗаголовок второго уровня</h2>\n<h4>\nHELLO WWWOOOOOORLLLLD<strong>M</strong><i>lel</i>\n</h4>\n<!-- Уровень 5: Заголовок пятого уровня -->\n<h5>Заголовок пятого уровня</h5>\n<!-- Уровень 6: Заголовок шестого уровня -->\n<!--\n<h6>Задокуметированный заголовок</h6>\n-->\n<h1 id=\"title\">Это заголовок с атрибутом id</h1>\n<!--<h1>comented h1</h1>--> \n<!--<h1>comented h1</h1>\n-->\n<!--\n<h1>comented h1</h1>-->\n<!--\n<h1>comented h1</h1>\n-->\n<!--<h1>header without closing tag-->\n</html>";
    QList<Header> headersList;

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 1;
    header.content = "Заголовок первого уровня\n";
    header.rawData = "<h1>Заголовок первого уровня\n</h1>";
    header.startPos = 52;
    header.endPos = 85;
    expectedHeadersList.append(header);
    header.level = 2;
    header.content = "\nЗаголовок второго уровня";
    header.rawData = "<h2>\nЗаголовок второго уровня</h2>";
    header.startPos = 132;
    header.endPos = 165;
    expectedHeadersList.append(header);
    header.level = 4;
    header.content = "\nHELLO WWWOOOOOORLLLLD<strong>M</strong><i>lel</i>\n";
    header.rawData = "<h4>\nHELLO WWWOOOOOORLLLLD<strong>M</strong><i>lel</i>\n</h4>";
    header.startPos = 167;
    header.endPos = 226;
    expectedHeadersList.append(header);
    header.level = 5;
    header.content = "Заголовок пятого уровня";
    header.rawData = "<h5>Заголовок пятого уровня</h5>";
    header.startPos = 272;
    header.endPos = 303;
    expectedHeadersList.append(header);
    header.level = 1;
    header.content = "Это заголовок с атрибутом id";
    header.rawData = "<h1 id=\"title\">Это заголовок с атрибутом id</h1>";
    header.startPos = 397;
    header.endPos = 444;
    expectedHeadersList.append(header);

    findHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findHeaders_tests::nestedCorrectHeaderInComment()
{
    QString htmlCode = "<html><h1>Header</h1><!--<h2>H2<h3>H3</h3></h2>--></html>";
    QList<Header> headersList;

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 1;
    header.content = "Header";
    header.rawData = "<h1>Header</h1>";
    header.startPos = 6;
    header.endPos = 20;
    expectedHeadersList.append(header);

    findHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findHeaders_tests::correctHeaderWithAttrubutes()
{
    QString htmlCode = "<html><h6 class=\"subheader\" data=\"info\" style=\"color: red\">H6</h6></html>";
    QList<Header> headersList;

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 6;
    header.content = "H6";
    header.rawData = "<h6 class=\"subheader\" data=\"info\" style=\"color: red\">H6</h6>";
    header.startPos = 6;
    header.endPos = 65;
    expectedHeadersList.append(header);

    findHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findHeaders_tests::correctHeaderWithCommentedOpeningTag()
{
    QString htmlCode = "<html><!--<h1>-->H1</h1></html>";
    QList<Header> headersList;

    try
    {
        findHeaders(htmlCode, headersList);
    }
    catch(QString exception)
    {
        QCOMPARE(exception, "Для заголовка, который заканчивается на позиции '24', отсутствует открывающий тег");
    }

    QCOMPARE(headersList.count(), 0);
}

void findHeaders_tests::correctHeaderWithCommentedClosingTag()
{
    QString htmlCode = "<html><h1>H1<!--</h1>--></html>";
    QList<Header> headersList;

    try
    {
        findHeaders(htmlCode, headersList);
    }
    catch(QString exception)
    {
        QCOMPARE(exception, "Для заголовка, который начинается на позиции '7', отсутствует закрывающий тег");
    }

    QCOMPARE(headersList.count(), 0);
}

void findHeaders_tests::correctHeaderWithCommentedOpeningAndClosingTag()
{
    QString htmlCode = "<html><!--<h1>-->H1<!--</h1>--></html>";
    QList<Header> headersList;

    QList<Header> expectedHeadersList = {};

    findHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findHeaders_tests::commentInCorrectHeaderContent()
{
    QString htmlCode = "<html><h1><!--Text-->H1</h1></html>";
    QList<Header> headersList;

    QList<Header> expectedHeadersList = {};
    Header header;
    header.level = 1;
    header.content = "<!--Text-->H1";
    header.rawData = "<h1><!--Text-->H1</h1>";
    header.startPos = 6;
    header.endPos = 27;
    expectedHeadersList.append(header);

    findHeaders(htmlCode, headersList);

    QCOMPARE(headersList, expectedHeadersList);
}

void findHeaders_tests::commentedNestedHeaderOpeningTag()
{
    QString htmlCode = "<h1>Example Domain<!--<h2>-->H2</h2></h1>";
    QList<Header> headersList;

    try
    {
        findHeaders(htmlCode, headersList);
    }
    catch(QString exception)
    {
        QCOMPARE(exception, "Для заголовка, который заканчивается на позиции '36', отсутствует открывающий тег");
    }

    QCOMPARE(headersList.count(), 1);
}

void findHeaders_tests::commentedNestedHeaderClosingTag()
{
    QString htmlCode = "<h1>Example Domain<h2>H2<!--</h2>--></h1>";
    QList<Header> headersList;

    try
    {
        findHeaders(htmlCode, headersList);
    }
    catch(QString exception)
    {
        QCOMPARE(exception, "Для заголовка, который начинается на позиции '19', отсутствует закрывающий тег");
    }

    QCOMPARE(headersList.count(), 1);
}

QTEST_APPLESS_MAIN(findHeaders_tests)

#include "tst_findheaders_tests.moc"
