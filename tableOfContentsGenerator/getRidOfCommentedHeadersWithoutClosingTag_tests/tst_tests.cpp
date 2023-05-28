#include <QtTest>
#include <../tableOfContentsGenerator_main/tableOfContentsGenerator.h>

class getRidOfCommentedHeadersWithoutClosingTag_tests : public QObject
{
    Q_OBJECT

private slots:
    void commentedHeadersWithoutClosingTagAreAvailable();
    void commentedHeaderWithoutOpeningTag();
    void commentedCorrectHeader();
    void noCommentsInHtmlCodeButHeadersAreAvailable();
    void noHeadersInHtmlCodeButCommentsAreAvailable();
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

    QList<int> headersPosWithoutOpeningTag = {15, 28, 37};

    QList<int> expectedHeadersPosWithoutOpeningTag = {37};

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, headersPosWithoutOpeningTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutOpeningTag, expectedHeadersPosWithoutOpeningTag);
}

void getRidOfCommentedHeadersWithoutClosingTag_tests::commentedHeaderWithoutOpeningTag()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--H2</h2>-->", 11, 24};
    commentsList.append(comment);

    QList<Comment> expectedCommentsList = commentsList;

    QList<int> headersPosWithoutOpeningTag = {15, 28, 37};

    QList<int> expectedHeadersPosWithoutOpeningTag = headersPosWithoutOpeningTag;

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, headersPosWithoutOpeningTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutOpeningTag, expectedHeadersPosWithoutOpeningTag);
}

void getRidOfCommentedHeadersWithoutClosingTag_tests::commentedCorrectHeader()
{
    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h2>H2</h2>-->", 11, 28, true};
    commentsList.append(comment);

    QList<Comment> expectedCommentsList = commentsList;

    QList<int> headersPosWithoutOpeningTag = {29, 39};

    QList<int> expectedHeadersPosWithoutOpeningTag = headersPosWithoutOpeningTag;

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, headersPosWithoutOpeningTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutOpeningTag, expectedHeadersPosWithoutOpeningTag);
}

void getRidOfCommentedHeadersWithoutClosingTag_tests::noCommentsInHtmlCodeButHeadersAreAvailable()
{
    QList<Comment> commentsList = {};

    QList<Comment> expectedCommentsList = commentsList;

    QList<int> headersPosWithoutOpeningTag = {15, 28, 37};

    QList<int> expectedHeadersPosWithoutOpeningTag = headersPosWithoutOpeningTag;

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, headersPosWithoutOpeningTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutOpeningTag, expectedHeadersPosWithoutOpeningTag);
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

    QList<int> headersPosWithoutOpeningTag = {};

    QList<int> expectedHeadersPosWithoutOpeningTag = headersPosWithoutOpeningTag;

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, headersPosWithoutOpeningTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutOpeningTag, expectedHeadersPosWithoutOpeningTag);
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

    QList<int> headersPosWithoutOpeningTag = {15, 28, 97};

    QList<int> expectedHeadersPosWithoutOpeningTag = {97};

    getRidOfCommentedHeadersWithoutClosingTag(commentsList, headersPosWithoutOpeningTag);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersPosWithoutOpeningTag, expectedHeadersPosWithoutOpeningTag);
}

QTEST_APPLESS_MAIN(getRidOfCommentedHeadersWithoutClosingTag_tests)

#include "tst_tests.moc"
