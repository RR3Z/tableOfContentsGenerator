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

    QList<Comment> expectedCommentsList = {};
    comment = {"<!--<h2>H2-->", 11, 23, true};
    expectedCommentsList.append(comment);
    comment = {"<!--<h3>H3-->", 24, 36, true};
    expectedCommentsList.append(comment);

    QList<int> headersPosWithoutClosingTag = {15, 28, 37};

    QList<int> expectedHeadersPosWithoutClosingTag = {37};

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, headersPosWithoutClosingTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutClosingTag, expectedHeadersPosWithoutClosingTag);
}

void getRidOfCommentedHeadersWithoutClosingTag_tests::commentedHeaderWithoutOpeningTag()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--H2</h2>-->", 11, 24};
    commentsList.append(comment);

    QList<Comment> expectedCommentsList = commentsList;

    QList<int> headersPosWithoutClosingTag = {15, 28, 37};

    QList<int> expectedHeadersPosWithoutClosingTag = headersPosWithoutClosingTag;

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, headersPosWithoutClosingTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutClosingTag, expectedHeadersPosWithoutClosingTag);
}

void getRidOfCommentedHeadersWithoutClosingTag_tests::commentedCorrectHeader()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h2>H2</h2>-->", 11, 28, true};
    commentsList.append(comment);

    QList<Comment> expectedCommentsList = commentsList;

    QList<int> headersPosWithoutClosingTag = {29, 39};

    QList<int> expectedHeadersPosWithoutClosingTag = headersPosWithoutClosingTag;

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, headersPosWithoutClosingTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutClosingTag, expectedHeadersPosWithoutClosingTag);
}

void getRidOfCommentedHeadersWithoutClosingTag_tests::noCommentsInHtmlCodeButHeadersAreAvailable()
{
    QList<Comment> commentsList = {};

    QList<Comment> expectedCommentsList = commentsList;

    QList<int> headersPosWithoutClosingTag = {15, 28, 37};

    QList<int> expectedHeadersPosWithoutClosingTag = headersPosWithoutClosingTag;

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, headersPosWithoutClosingTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutClosingTag, expectedHeadersPosWithoutClosingTag);
}

void getRidOfCommentedHeadersWithoutClosingTag_tests::noHeadersInHtmlCodeButCommentsAreAvailable()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h2>H2-->", 11, 23};
    commentsList.append(comment);
    comment = {"<!--<h3>H3-->", 24, 36};
    commentsList.append(comment);

    QList<Comment> expectedCommentsList = {};
    comment = {"<!--<h2>H2-->", 11, 23, true};
    expectedCommentsList.append(comment);
    comment = {"<!--<h3>H3-->", 24, 36, true};
    expectedCommentsList.append(comment);

    QList<int> headersPosWithoutClosingTag = {};

    QList<int> expectedHeadersPosWithoutClosingTag = headersPosWithoutClosingTag;

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, headersPosWithoutClosingTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutClosingTag, expectedHeadersPosWithoutClosingTag);
}

void getRidOfCommentedHeadersWithoutClosingTag_tests::commentedNestedCorrectHeader()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h1>H1<h2>H2</h2></h1>-->", 0, 28, true};
    commentsList.append(comment);

    QList<Comment> expectedCommentsList = commentsList;

    QList<int> headersPosWithoutClosingTag = {};

    QList<int> expectedHeadersPosWithoutClosingTag = headersPosWithoutClosingTag;

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, headersPosWithoutClosingTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutClosingTag, expectedHeadersPosWithoutClosingTag);
}

void getRidOfCommentedHeadersWithoutClosingTag_tests::commentedNestedHeaderWithoutOpeningTag()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h1>H1 H2</h2></h1>-->", 0, 25, true};
    commentsList.append(comment);

    QList<Comment> expectedCommentsList = commentsList;

    QList<int> headersPosWithoutClosingTag = {};

    QList<int> expectedHeadersPosWithoutClosingTag = headersPosWithoutClosingTag;

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, headersPosWithoutClosingTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutClosingTag, expectedHeadersPosWithoutClosingTag);
}

void getRidOfCommentedHeadersWithoutClosingTag_tests::commentedNestedHeaderWithoutClosingTag()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h1>H1<h2>H2</h1>-->", 0, 23, true};
    commentsList.append(comment);

    QList<Comment> expectedCommentsList = commentsList;

    QList<int> headersPosWithoutClosingTag = {};

    QList<int> expectedHeadersPosWithoutClosingTag = headersPosWithoutClosingTag;

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, headersPosWithoutClosingTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutClosingTag, expectedHeadersPosWithoutClosingTag);
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
    comment = {"<!--<h5>H5</h5>-->", 62, 79, true};
    commentsList.append(comment);
    comment = {"<!--Text-->", 80, 90};
    commentsList.append(comment);

    QList<Comment> expectedCommentsList = {};
    comment = {"<!--<h2>H2-->", 11, 23, true};
    expectedCommentsList.append(comment);
    comment = {"<!--<h3>H3-->", 24, 36, true};
    expectedCommentsList.append(comment);
    comment = {"<!--H4</h4>-->", 48, 61};
    expectedCommentsList.append(comment);
    comment = {"<!--<h5>H5</h5>-->", 62, 79, true};
    expectedCommentsList.append(comment);
    comment = {"<!--Text-->", 80, 90};
    expectedCommentsList.append(comment);

    QList<int> headersPosWithoutClosingTag = {15, 28, 97};

    QList<int> expectedHeadersPosWithoutClosingTag = {97};

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, headersPosWithoutClosingTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutClosingTag, expectedHeadersPosWithoutClosingTag);
}

QTEST_APPLESS_MAIN(getRidOfCommentedHeadersWithoutClosingTag_tests)

#include "tst_tests.moc"
