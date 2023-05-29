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

    QList<Comment> expectedCommentsList = {};
    comment = {"<!--H2</h2>-->", 11, 24, true};
    expectedCommentsList.append(comment);
    comment = {"<!--H3</h3>-->", 25, 38, true};
    expectedCommentsList.append(comment);

    QList<int> headersPosWithoutOpeningTag = {15, 21, 35};

    QList<int> expectedHeadersPosWithoutOpeningTag = {15};

    getRidOfCommentedHeadersWithoutOpeningTag(commentsList, headersPosWithoutOpeningTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutOpeningTag, expectedHeadersPosWithoutOpeningTag);
}

void getRidOfCommentedHeadersWithoutOpeningTag_tests::commentedHeaderWithoutClosingTag()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h2>H2-->", 11, 23};
    commentsList.append(comment);

    QList<Comment> expectedCommentsList = commentsList;

    QList<int> headersPosWithoutOpeningTag = {28, 37};

    QList<int> expectedHeadersPosWithoutOpeningTag = headersPosWithoutOpeningTag;

    getRidOfCommentedHeadersWithoutOpeningTag(commentsList, headersPosWithoutOpeningTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutOpeningTag, expectedHeadersPosWithoutOpeningTag);
}

void getRidOfCommentedHeadersWithoutOpeningTag_tests::commentedCorrectHeader()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h2>H2</h2>-->", 11, 28, true};
    commentsList.append(comment);

    QList<Comment> expectedCommentsList = commentsList;

    QList<int> headersPosWithoutOpeningTag = {29, 39};

    QList<int> expectedHeadersPosWithoutOpeningTag = headersPosWithoutOpeningTag;

    getRidOfCommentedHeadersWithoutOpeningTag(commentsList, headersPosWithoutOpeningTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutOpeningTag, expectedHeadersPosWithoutOpeningTag);
}

void getRidOfCommentedHeadersWithoutOpeningTag_tests::noCommentsInHtmlCodeButHeadersAreAvailable()
{
    QList<Comment> commentsList = {};

    QList<Comment> expectedCommentsList = commentsList;

    QList<int> headersPosWithoutOpeningTag = {15, 28, 37};

    QList<int> expectedHeadersPosWithoutOpeningTag = headersPosWithoutOpeningTag;

    getRidOfCommentedHeadersWithoutOpeningTag(commentsList, headersPosWithoutOpeningTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutOpeningTag, expectedHeadersPosWithoutOpeningTag);
}

void getRidOfCommentedHeadersWithoutOpeningTag_tests::noHeadersInHtmlCodeButCommentsAreAvailable()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h2>H2-->", 11, 23, true};
    commentsList.append(comment);
    comment = {"<!--<h3>H3-->", 24, 36, true};
    commentsList.append(comment);

    QList<Comment> expectedCommentsList = commentsList;

    QList<int> headersPosWithoutOpeningTag = {};

    QList<int> expectedHeadersPosWithoutOpeningTag = headersPosWithoutOpeningTag;

    getRidOfCommentedHeadersWithoutOpeningTag(commentsList, headersPosWithoutOpeningTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutOpeningTag, expectedHeadersPosWithoutOpeningTag);
}

void getRidOfCommentedHeadersWithoutOpeningTag_tests::commentedNestedCorrectHeader()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h1>H1<h2>H2</h2></h1>-->", 0, 28, true};
    commentsList.append(comment);

    QList<Comment> expectedCommentsList = commentsList;

    QList<int> headersPosWithoutOpeningTag = {};

    QList<int> expectedHeadersPosWithoutOpeningTag = headersPosWithoutOpeningTag;

    getRidOfCommentedHeadersWithoutOpeningTag(commentsList, headersPosWithoutOpeningTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutOpeningTag, expectedHeadersPosWithoutOpeningTag);
}

void getRidOfCommentedHeadersWithoutOpeningTag_tests::commentedNestedHeaderWithoutOpeningTag()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h1>H1 H2</h2></h1>-->", 0, 25, true};
    commentsList.append(comment);

    QList<Comment> expectedCommentsList = commentsList;

    QList<int> headersPosWithoutOpeningTag = {};

    QList<int> expectedHeadersPosWithoutOpeningTag = headersPosWithoutOpeningTag;

    getRidOfCommentedHeadersWithoutOpeningTag(commentsList, headersPosWithoutOpeningTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutOpeningTag, expectedHeadersPosWithoutOpeningTag);
}

void getRidOfCommentedHeadersWithoutOpeningTag_tests::commentedNestedHeaderWithoutClosingTag()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h1>H1<h2>H2</h1>-->", 0, 23, true};
    commentsList.append(comment);

    QList<Comment> expectedCommentsList = commentsList;

    QList<int> headersPosWithoutOpeningTag = {};

    QList<int> expectedHeadersPosWithoutOpeningTag = headersPosWithoutOpeningTag;

    getRidOfCommentedHeadersWithoutOpeningTag(commentsList, headersPosWithoutOpeningTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutOpeningTag, expectedHeadersPosWithoutOpeningTag);
}

void getRidOfCommentedHeadersWithoutOpeningTag_tests::complexTest()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h2>H2-->", 11, 23, true};
    commentsList.append(comment);
    comment = {"<!--<h3>H3-->", 24, 36, true};
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
    comment = {"<!--H4</h4>-->", 48, 61, true};
    expectedCommentsList.append(comment);
    comment = {"<!--<h5>H5</h5>-->", 62, 79, true};
    expectedCommentsList.append(comment);
    comment = {"<!--Text-->", 80, 90};
    expectedCommentsList.append(comment);

    QList<int> headersPosWithoutOpeningTag = {58, 97};

    QList<int> expectedHeadersPosWithoutOpeningTag = {97};

    getRidOfCommentedHeadersWithoutOpeningTag(commentsList, headersPosWithoutOpeningTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutOpeningTag, expectedHeadersPosWithoutOpeningTag);
}

QTEST_APPLESS_MAIN(getRidOfCommentedHeadersWithoutOpeningTag_tests)

#include "tst_tests.moc"
