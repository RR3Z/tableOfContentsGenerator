#include <QtTest>
#include <../tableOfContentsGenerator_main/tableOfContentsGenerator.h>

class generateTableOfContents_tests : public QObject
{
    Q_OBJECT
private slots:
    void headersAreAvailable();
    void noHeaders();
    void allHeadersAreSameLevel();
    void allHeadersAreDifferentLevel();
    void headersRepetitionWithDifferentLevels();
    void headerWithAttributeInContent();
    void headerWithoutContent();
    void headerWithDifferentAttributesInContent();
    void tableOfContentsBeginWithThirdLevelHeader();
    void headersWithSameContent();
};

void generateTableOfContents_tests::headersAreAvailable()
{
    QList<Header> headersList;
    Header header = {1, "<h1>Header 1.0</h1>", "Header 1.0", 0, 0};
    headersList.append(header);
    header = {2, "<h2>Header 1.1</h2>", "Header 1.1", 0, 0};
    headersList.append(header);
    header = {1, "<h1>Header 2.0</h1>", "Header 2.0", 0, 0};
    headersList.append(header);
    header = {2, "<h2>Header 2.1</h2>", "Header 2.1", 0, 0};
    headersList.append(header);
    header = {3, "<h3>Header 2.2</h3>", "Header 2.2", 0, 0};
    headersList.append(header);

    QString expectedTableOfContents = "<ul>\n<li>Header 1.0</li>\n<ul>\n<li>Header 1.1</li>\n</ul>\n<li>Header 2.0</li>\n<ul>\n<li>Header 2.1</li>\n<ul>\n<li>Header 2.2</li>\n</ul>\n</ul>\n</ul>\n";

    QString tableOfContents;

    generateTableOfContents(headersList, tableOfContents);

    QCOMPARE(tableOfContents, expectedTableOfContents);
}

void generateTableOfContents_tests::noHeaders()
{
    QList<Header> headersList = {};

    QString expectedTableOfContents = "";

     QString tableOfContents;

    generateTableOfContents(headersList, tableOfContents);

    QCOMPARE(tableOfContents, expectedTableOfContents);
}

void generateTableOfContents_tests::allHeadersAreSameLevel()
{
    QList<Header> headersList;
    Header header = {1, "<h1>Header 1.0</h1>", "Header 1.0", 0, 0};
    headersList.append(header);
    header = {1, "<h1>Header 2.0</h1>", "Header 2.0", 0, 0};
    headersList.append(header);
    header = {1, "<h1>Header 3.0</h1>", "Header 3.0", 0, 0};
    headersList.append(header);

    QString expectedTableOfContents = "<ul>\n<li>Header 1.0</li>\n<li>Header 2.0</li>\n<li>Header 3.0</li>\n</ul>\n";

    QString tableOfContents;

    generateTableOfContents(headersList, tableOfContents);

    QCOMPARE(tableOfContents, expectedTableOfContents);
}

void generateTableOfContents_tests::allHeadersAreDifferentLevel()
{
    QList<Header> headersList;
    Header header = {1, "<h1>Header 1.0</h1>", "Header 1.0", 0, 0};
    headersList.append(header);
    header = {2, "<h2>Header 1.1</h2>", "Header 1.1", 0, 0};
    headersList.append(header);
    header = {3, "<h3>Header 1.2</h3>", "Header 1.2", 0, 0};
    headersList.append(header);

    QString expectedTableOfContents = "<ul>\n<li>Header 1.0</li>\n<ul>\n<li>Header 1.1</li>\n<ul>\n<li>Header 1.2</li>\n</ul>\n</ul>\n</ul>\n";

    QString tableOfContents;

    generateTableOfContents(headersList, tableOfContents);

    QCOMPARE(tableOfContents, expectedTableOfContents);
}

void generateTableOfContents_tests::headersRepetitionWithDifferentLevels()
{
    QList<Header> headersList;
    Header header = {1, "<h1>Header 1.0</h1>", "Header 1.0", 0, 0};
    headersList.append(header);
    header = {2, "<h2>Header 1.1</h2>", "Header 1.1", 0, 0};
    headersList.append(header);
    header = {1, "<h1>Header 2.0</h1>", "Header 2.0", 0, 0};
    headersList.append(header);
    header = {2, "<h2>Header 2.1</h2>", "Header 2.1", 0, 0};
    headersList.append(header);

    QString expectedTableOfContents = "<ul>\n<li>Header 1.0</li>\n<ul>\n<li>Header 1.1</li>\n</ul>\n<li>Header 2.0</li>\n<ul>\n<li>Header 2.1</li>\n</ul>\n</ul>\n";

    QString tableOfContents;

    generateTableOfContents(headersList, tableOfContents);

    QCOMPARE(tableOfContents, expectedTableOfContents);
}

void generateTableOfContents_tests::headerWithAttributeInContent()
{
    QList<Header> headersList;
    Header header = {1, "<h1>Header 1.0<span style=\"color: red;\">красный</span></h1>", "Header 1.0<span style=\"color: red;\">красный</span>", 0, 0};
    headersList.append(header);

    QString expectedTableOfContents = "<ul>\n<li>Header 1.0<span style=\"color: red;\">красный</span></li>\n</ul>\n";

    QString tableOfContents;

    generateTableOfContents(headersList, tableOfContents);

    QCOMPARE(tableOfContents, expectedTableOfContents);
}

void generateTableOfContents_tests::headerWithoutContent()
{
    QList<Header> headersList;
    Header header = {1, "<h1></h1>", "", 0, 0};
    headersList.append(header);

    QString expectedTableOfContents = "<ul>\n<li></li>\n</ul>\n";

    QString tableOfContents;

    generateTableOfContents(headersList, tableOfContents);

    QCOMPARE(tableOfContents, expectedTableOfContents);
}

void generateTableOfContents_tests::headerWithDifferentAttributesInContent()
{
    QList<Header> headersList;
    Header header = {1, "<h1>Это <span style=\"color: blue;\">синий</span> и <strong>жирный</strong></h1>", "Это <span style=\"color: blue;\">синий</span> и <strong>жирный</strong>", 0, 0};
    headersList.append(header);

    QString expectedTableOfContents = "<ul>\n<li>Это <span style=\"color: blue;\">синий</span> и <strong>жирный</strong></li>\n</ul>\n";

    QString tableOfContents;

    generateTableOfContents(headersList, tableOfContents);

    QCOMPARE(tableOfContents, expectedTableOfContents);
}

void generateTableOfContents_tests::tableOfContentsBeginWithThirdLevelHeader()
{
    QList<Header> headersList;
    Header header = {3, "<h3>Header 1.3</h3>", "Header 1.3", 0, 0};
    headersList.append(header);
    header = {1, "<h1>Header 2.0</h1>", "Header 2.0", 0, 0};
    headersList.append(header);

    QString expectedTableOfContents = "<ul>\n<ul>\n<ul>\n<li>Header 1.3</li>\n</ul>\n</ul>\n<li>Header 2.0</li>\n</ul>\n";

    QString tableOfContents;

    generateTableOfContents(headersList, tableOfContents);

    QCOMPARE(tableOfContents, expectedTableOfContents);
}

void generateTableOfContents_tests::headersWithSameContent()
{
    QList<Header> headersList;
    Header header = {1, "<h1>Header 1.0</h1>", "Header 1.0", 0, 0};
    headersList.append(header);
    header = {1, "<h1>Header 1.0</h1>", "Header 1.0", 0, 0};
    headersList.append(header);

    QString expectedTableOfContents = "<ul>\n<li>Header 1.0</li>\n<li>Header 1.0</li>\n</ul>\n";

    QString tableOfContents;

    generateTableOfContents(headersList, tableOfContents);

    QCOMPARE(tableOfContents, expectedTableOfContents);
}

QTEST_APPLESS_MAIN(generateTableOfContents_tests)

#include "tst_generatetableofcontents_tests.moc"
