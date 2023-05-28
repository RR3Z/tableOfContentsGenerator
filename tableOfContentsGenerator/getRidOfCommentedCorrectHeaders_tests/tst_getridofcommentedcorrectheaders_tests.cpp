#include <QtTest>
#include <../tableOfContentsGenerator_main/tableOfContentsGenerator.h>

class getRidOfCommentedCorrectHeaders_tests : public QObject
{
    Q_OBJECT
private slots:
    void commentedCorrectHeadersAreAvailable();
    void commentedHeaderWithoutOpeningTag();
    void commentedHeaderWithoutClosingTag();
    void noCommentsInHtmlCodeButHeadersAreAvailable();
    void noHeadersInHtmlCodeButCommentsAreAvailable();
    void complexTest();
};

void getRidOfCommentedCorrectHeaders_tests::commentedCorrectHeadersAreAvailable()
{

    QList<Header> headersList = {};
    Header header = {1,"<h1>H1</h1>", "H1", 0, 10};
    headersList.append(header);
    header = {2, "<h2>H2</h2>", "H2", 16, 26};
    headersList.append(header);
    header = {3, "<h3>H3</h3", "H3", 38, 48};
    headersList.append(header);

    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h2>H2</h2>-->", 12, 29};
    commentsList.append(comment);
    comment = {"<!--<h3>H3</h3>-->", 34, 51};
    commentsList.append(comment);

    QList<Comment> expectedCommentsList = {};
    comment = {"<!--<h2>H2</h2>-->", 12, 29, true};
    expectedCommentsList.append(comment);
    comment = {"<!--<h3>H3</h3>-->", 34, 51, true};
    expectedCommentsList.append(comment);

    QList<Header> expectedHeadersList = {};
    header = {1,"<h1>H1</h1>", "H1", 0, 10};
    expectedHeadersList.append(header);

    getRidOfCommentedCorrectHeaders(commentsList, headersList);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersList, expectedHeadersList);
}

void getRidOfCommentedCorrectHeaders_tests::commentedHeaderWithoutOpeningTag()
{
    QList<Header> headersList = {};
    Header header = {1,"<h1>H1</h1>", "H1", 0, 10};
    headersList.append(header);

    QList<Comment> commentsList = {};
    Comment comment = {"<!--H2</h2>-->", 11, 24};
    commentsList.append(comment);

    QList<Comment> expectedCommentsList = commentsList;

    QList<Header> expectedHeadersList = headersList;

    getRidOfCommentedCorrectHeaders(commentsList, headersList);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersList, expectedHeadersList);
}

void getRidOfCommentedCorrectHeaders_tests::commentedHeaderWithoutClosingTag()
{
    QList<Header> headersList = {};
    Header header = {1,"<h1>H1</h1>", "H1", 0, 10};
    headersList.append(header);

    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h2>H2-->", 11, 23};
    commentsList.append(comment);

    QList<Comment> expectedCommentsList = commentsList;

    QList<Header> expectedHeadersList = headersList;

    getRidOfCommentedCorrectHeaders(commentsList, headersList);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersList, expectedHeadersList);
}

void getRidOfCommentedCorrectHeaders_tests::noCommentsInHtmlCodeButHeadersAreAvailable()
{

    QList<Header> headersList = {};
    Header header = {1,"<h1>H1</h1>", "H1", 0, 10};
    headersList.append(header);
    header = {2, "<h2>H2</h2>", "H2", 11, 21};
    headersList.append(header);
    header = {3, "<h3>H3</h3", "H3", 22, 32};
    headersList.append(header);

    QList<Comment> commentsList = {};

    QList<Comment> expectedCommentsList = {};

    QList<Header> expectedHeadersList = headersList;

    getRidOfCommentedCorrectHeaders(commentsList, headersList);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersList, expectedHeadersList);
}

void getRidOfCommentedCorrectHeaders_tests::noHeadersInHtmlCodeButCommentsAreAvailable()
{

    QList<Header> headersList = {};

    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h2>H2</h2>-->", 0, 17};
    commentsList.append(comment);
    comment = {"<!--<h3>H3</h3>-->", 18, 25};
    commentsList.append(comment);

    QList<Comment> expectedCommentsList = {};
    comment = {"<!--<h2>H2</h2>-->", 0, 17, true};
    expectedCommentsList.append(comment);
    comment = {"<!--<h3>H3</h3>-->", 18, 25, true};
    expectedCommentsList.append(comment);

    QList<Header> expectedHeadersList = {};

    getRidOfCommentedCorrectHeaders(commentsList, headersList);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersList, expectedHeadersList);
}

void getRidOfCommentedCorrectHeaders_tests::complexTest()
{

    QList<Header> headersList = {};
    Header header = {1,"<h1>H1</h1>", "H1", 0, 10};
    headersList.append(header);
    header = {2, "<h2>H2</h2>", "H2", 16, 26};
    headersList.append(header);
    header = {3, "<h3>H3</h3", "H3", 38, 48};
    headersList.append(header);

    QList<Comment> commentsList = {};
    Comment comment = {"<!--<h2>H2</h2>-->", 12, 29};
    commentsList.append(comment);
    comment = {"<!--<h3>H3</h3>-->", 34, 51};
    commentsList.append(comment);
    comment = {"<!--H4</h4>-->", 52, 65};
    commentsList.append(comment);
    comment = {"<!--<h5>H5-->", 66, 78};
    commentsList.append(comment);

    QList<Comment> expectedCommentsList = {};
    comment = {"<!--<h2>H2</h2>-->", 12, 29, true};
    expectedCommentsList.append(comment);
    comment = {"<!--<h3>H3</h3>-->", 34, 51, true};
    expectedCommentsList.append(comment);
    comment = {"<!--H4</h4>-->", 52, 65};
    expectedCommentsList.append(comment);
    comment = {"<!--<h5>H5-->", 66, 78};
    expectedCommentsList.append(comment);

    QList<Header> expectedHeadersList = {};
    header = {1,"<h1>H1</h1>", "H1", 0, 10};
    expectedHeadersList.append(header);

    getRidOfCommentedCorrectHeaders(commentsList, headersList);

    QCOMPARE(commentsList, expectedCommentsList);
    QCOMPARE(headersList, expectedHeadersList);
}

QTEST_APPLESS_MAIN(getRidOfCommentedCorrectHeaders_tests)

#include "tst_getridofcommentedcorrectheaders_tests.moc"
