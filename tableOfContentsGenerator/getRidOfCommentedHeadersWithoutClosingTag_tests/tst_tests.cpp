#include <QtTest>
#include <../tableOfContentsGenerator_main/findHeaders.h>

class getRidOfCommentedHeadersWithoutClosingTag_tests : public QObject
{
    Q_OBJECT

private slots:
    void commentedHeadersWithoutClosingTagAreAvailable();
    void commentedHeaderWithoutOpeningTag();
    void commentedCorrectHeader();
    void noCommentsInHtmlCodeButHeadersAreAvailable();
    void noHeadersInHtmlCodeButCommentsAreAvailable();
    void commentedNestedCorrectHeader();
    void commentedNestedHeaderWithoutOpeningTag();
    void commentedNestedHeaderWithoutClosingTag();
    void complexTest();
};

void getRidOfCommentedHeadersWithoutClosingTag_tests::commentedHeadersWithoutClosingTagAreAvailable()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h2>H2-->", 11, 23};
    commentsList.append(comment);
    comment = {"<!--<h3>H3-->", 24, 36};
    commentsList.append(comment);

    QList<int> openTagHeadersPos = {15, 28, 37};

    QList<int> expectedOpenTagHeadersPos = {37};

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, openTagHeadersPos);

    QCOMPARE(openTagHeadersPos, expectedOpenTagHeadersPos);
}

void getRidOfCommentedHeadersWithoutClosingTag_tests::commentedHeaderWithoutOpeningTag()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--H2</h2>-->", 11, 24};
    commentsList.append(comment);

    QList<int> openTagHeadersPos = {28, 37};

    QList<int> expectedOpenTagHeadersPos = openTagHeadersPos;

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, openTagHeadersPos);

    QCOMPARE(openTagHeadersPos, expectedOpenTagHeadersPos);
}

void getRidOfCommentedHeadersWithoutClosingTag_tests::commentedCorrectHeader()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h2>H2</h2>-->", 11, 28};
    commentsList.append(comment);

    QList<int> openTagHeadersPos = {15, 29, 39};

    QList<int> expectedOpenTagHeadersPos = {29, 39};

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, openTagHeadersPos);

    QCOMPARE(openTagHeadersPos, expectedOpenTagHeadersPos);
}

void getRidOfCommentedHeadersWithoutClosingTag_tests::noCommentsInHtmlCodeButHeadersAreAvailable()
{
    QList<Comment> commentsList = {};

    QList<int> openTagHeadersPos = {15, 28, 37};

    QList<int> expectedOpenTagHeadersPos = openTagHeadersPos;

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, openTagHeadersPos);

    QCOMPARE(openTagHeadersPos, expectedOpenTagHeadersPos);
}

void getRidOfCommentedHeadersWithoutClosingTag_tests::noHeadersInHtmlCodeButCommentsAreAvailable()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h2>H2-->", 11, 23};
    commentsList.append(comment);
    comment = {"<!--<h3>H3-->", 24, 36};
    commentsList.append(comment);

    QList<int> openTagHeadersPos = {15, 28};

    QList<int> expectedOpenTagHeadersPos = {};

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, openTagHeadersPos);

    QCOMPARE(openTagHeadersPos, expectedOpenTagHeadersPos);
}

void getRidOfCommentedHeadersWithoutClosingTag_tests::commentedNestedCorrectHeader()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h1>H1<h2>H2</h2></h1>-->", 0, 28};
    commentsList.append(comment);

    QList<int> openTagHeadersPos = {4, 10};

    QList<int> expectedOpenTagHeadersPos = {};

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, openTagHeadersPos);

    QCOMPARE(openTagHeadersPos, expectedOpenTagHeadersPos);
}

void getRidOfCommentedHeadersWithoutClosingTag_tests::commentedNestedHeaderWithoutOpeningTag()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h1>H1 H2</h2></h1>-->", 0, 25};
    commentsList.append(comment);

    QList<int> openTagHeadersPos = {4};

    QList<int> expectedOpenTagHeadersPos = {};

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, openTagHeadersPos);

    QCOMPARE(openTagHeadersPos, expectedOpenTagHeadersPos);
}

void getRidOfCommentedHeadersWithoutClosingTag_tests::commentedNestedHeaderWithoutClosingTag()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h1>H1<h2>H2</h1>-->", 0, 23};
    commentsList.append(comment);

    QList<int> openTagHeadersPos = {4, 10};

    QList<int> expectedOpenTagHeadersPos = {};

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, openTagHeadersPos);

    QCOMPARE(openTagHeadersPos, expectedOpenTagHeadersPos);
}

void getRidOfCommentedHeadersWithoutClosingTag_tests::complexTest()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h2>H2-->", 11, 23};
    commentsList.append(comment);
    comment = {"<!--<h3>H3-->", 24, 36};
    commentsList.append(comment);
    comment = {"<!--H4</h4>-->", 48, 61};
    commentsList.append(comment);
    comment = {"<!--<h5>H5</h5>-->", 62, 79};
    commentsList.append(comment);
    comment = {"<!--Text-->", 80, 90};
    commentsList.append(comment);

    QList<int> openTagHeadersPos = {15, 28, 66, 97};

    QList<int> expectedOpenTagHeadersPos = {97};

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, openTagHeadersPos);

    QCOMPARE(openTagHeadersPos, expectedOpenTagHeadersPos);
}

QTEST_APPLESS_MAIN(getRidOfCommentedHeadersWithoutClosingTag_tests)

#include "tst_tests.moc"
