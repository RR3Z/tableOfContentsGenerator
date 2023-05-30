#include <QtTest>
#include <../tableOfContentsGenerator_main/findHeaders.h>

class getRidOfCommentedHeadersWithoutOpeningTag_tests : public QObject
{
    Q_OBJECT

private slots:
    void commentedHeadersWithoutOpeningTagAreAvailable();
    void commentedHeaderWithoutClosingTag();
    void commentedCorrectHeader();
    void noCommentsInHtmlCodeButHeadersAreAvailable();
    void noHeadersInHtmlCodeButCommentsAreAvailable();
    void commentedNestedCorrectHeader();
    void commentedNestedHeaderWithoutOpeningTag();
    void commentedNestedHeaderWithoutClosingTag();
    void complexTest();
};

void getRidOfCommentedHeadersWithoutOpeningTag_tests::commentedHeadersWithoutOpeningTagAreAvailable()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--H2</h2>-->", 11, 24};
    commentsList.append(comment);
    comment = {"<!--H3</h3>-->", 25, 38};
    commentsList.append(comment);

    QList<int> closeTagHeadersPos = {0, 21, 35};

    QList<int> expectedCloseTagHeadersPos = {0};

    getRidOfCommentedHeadersWithoutOpeningTag(commentsList, closeTagHeadersPos);

    QCOMPARE(closeTagHeadersPos, expectedCloseTagHeadersPos);
}

void getRidOfCommentedHeadersWithoutOpeningTag_tests::commentedHeaderWithoutClosingTag()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h2>H2-->", 11, 23};
    commentsList.append(comment);

    QList<int> closeTagHeadersPos = {28, 37};

    QList<int> expectedCloseTagHeadersPos = closeTagHeadersPos;

    getRidOfCommentedHeadersWithoutOpeningTag(commentsList, closeTagHeadersPos);

    QCOMPARE(closeTagHeadersPos, expectedCloseTagHeadersPos);
}

void getRidOfCommentedHeadersWithoutOpeningTag_tests::commentedCorrectHeader()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h2>H2</h2>-->", 11, 28};
    commentsList.append(comment);

    QList<int> closeTagHeadersPos = {25, 29, 39};

    QList<int> expectedCloseTagHeadersPos = {29, 39};

    getRidOfCommentedHeadersWithoutOpeningTag(commentsList, closeTagHeadersPos);

    QCOMPARE(closeTagHeadersPos, expectedCloseTagHeadersPos);
}

void getRidOfCommentedHeadersWithoutOpeningTag_tests::noCommentsInHtmlCodeButHeadersAreAvailable()
{
    QList<Comment> commentsList = {};

    QList<int> closeTagHeadersPos = {15, 28, 37};

    QList<int> expectedCloseTagHeadersPos = closeTagHeadersPos;

    getRidOfCommentedHeadersWithoutOpeningTag(commentsList, closeTagHeadersPos);

    QCOMPARE(closeTagHeadersPos, expectedCloseTagHeadersPos);
}

void getRidOfCommentedHeadersWithoutOpeningTag_tests::noHeadersInHtmlCodeButCommentsAreAvailable()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h2>H2-->", 11, 23};
    commentsList.append(comment);
    comment = {"<!--<h3>H3-->", 24, 36};
    commentsList.append(comment);

    QList<int> closeTagHeadersPos = {};

    QList<int> expectedCloseTagHeadersPos = closeTagHeadersPos;

    getRidOfCommentedHeadersWithoutOpeningTag(commentsList, closeTagHeadersPos);

    QCOMPARE(closeTagHeadersPos, expectedCloseTagHeadersPos);
}

void getRidOfCommentedHeadersWithoutOpeningTag_tests::commentedNestedCorrectHeader()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h1>H1<h2>H2</h2></h1>-->", 0, 28};
    commentsList.append(comment);

    QList<int> closeTagHeadersPos = {20, 25};

    QList<int> expectedCloseTagHeadersPos = {};

    getRidOfCommentedHeadersWithoutOpeningTag(commentsList, closeTagHeadersPos);

    QCOMPARE(closeTagHeadersPos, expectedCloseTagHeadersPos);
}

void getRidOfCommentedHeadersWithoutOpeningTag_tests::commentedNestedHeaderWithoutOpeningTag()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h1>H1 H2</h2></h1>-->", 0, 25};
    commentsList.append(comment);

    QList<int> closeTagHeadersPos = {17, 22};

    QList<int> expectedCloseTagHeadersPos = {};

    getRidOfCommentedHeadersWithoutOpeningTag(commentsList, closeTagHeadersPos);

    QCOMPARE(closeTagHeadersPos, expectedCloseTagHeadersPos);
}

void getRidOfCommentedHeadersWithoutOpeningTag_tests::commentedNestedHeaderWithoutClosingTag()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h1>H1<h2>H2</h1>-->", 0, 23};
    commentsList.append(comment);

    QList<int> closeTagHeadersPos = {20};

    QList<int> expectedCloseTagHeadersPos = {};

    getRidOfCommentedHeadersWithoutOpeningTag(commentsList, closeTagHeadersPos);

    QCOMPARE(closeTagHeadersPos, expectedCloseTagHeadersPos);
}

void getRidOfCommentedHeadersWithoutOpeningTag_tests::complexTest()
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

    QList<int> closeTagHeadersPos = {58, 76, 97};

    QList<int> expectedCloseTagHeadersPos = {97};

    getRidOfCommentedHeadersWithoutOpeningTag(commentsList, closeTagHeadersPos);

    QCOMPARE(closeTagHeadersPos, expectedCloseTagHeadersPos);
}

QTEST_APPLESS_MAIN(getRidOfCommentedHeadersWithoutOpeningTag_tests)

#include "tst_tests.moc"
