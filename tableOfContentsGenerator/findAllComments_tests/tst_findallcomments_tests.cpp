#include <QtTest>
#include <../tableOfContentsGenerator_main/tableOfContentsGenerator.h>

class findAllComments_tests : public QObject
{
    Q_OBJECT
private slots:
    void commentsAreAvailable();
    void noComments();
    void commentWithText();
    void commentWithCorrectHeader();
    void commentWithHeaderWithoutClosingTag();
    void commentWithHeaderWithoutOpeningTag();
    void emptyComment();
    void complexTest();
};

void findAllComments_tests::commentsAreAvailable()
{
    QString htmlCode = "<html>\n<h1>H1</h1><!--<h2>H2</h2>--><!--Comment!-->\n</html>";
    QList<Comment> commentsList = {};

    QList<Comment> expectedCommentsList = {};
    Comment comment;
    comment.rawData = "<!--<h2>H2</h2>-->";
    comment.startPos = 18;
    comment.endPos = 35;
    expectedCommentsList.append(comment);
    comment.rawData = "<!--Comment!-->";
    comment.startPos = 36;
    comment.endPos = 50;
    expectedCommentsList.append(comment);

    findAllComments(htmlCode, commentsList);

    QCOMPARE(commentsList, expectedCommentsList);
}

void findAllComments_tests::noComments()
{
    QString htmlCode = "<html>\n<h1>H1</h1>\n</html>";
    QList<Comment> commentsList = {};

    QList<Comment> expectedCommentsList = {};

    findAllComments(htmlCode, commentsList);

    QCOMPARE(commentsList, expectedCommentsList);
}

void findAllComments_tests::commentWithText()
{
    QString htmlCode = "<html>\n<h1>H1</h1><!--Comment!-->\n</html>";
    QList<Comment> commentsList = {};

    QList<Comment> expectedCommentsList = {};
    Comment comment;
    comment.rawData = "<!--Comment!-->";
    comment.startPos = 18;
    comment.endPos = 32;
    expectedCommentsList.append(comment);

    findAllComments(htmlCode, commentsList);

    QCOMPARE(commentsList, expectedCommentsList);
}

void findAllComments_tests::commentWithCorrectHeader()
{
    QString htmlCode = "<html>\n<h1>H1</h1><!--<h2>H2</h2>-->\n</html>";
    QList<Comment> commentsList = {};

    QList<Comment> expectedCommentsList = {};
    Comment comment;
    comment.rawData = "<!--<h2>H2</h2>-->";
    comment.startPos = 18;
    comment.endPos = 35;
    expectedCommentsList.append(comment);

    findAllComments(htmlCode, commentsList);

    QCOMPARE(commentsList, expectedCommentsList);
}

void findAllComments_tests::commentWithHeaderWithoutClosingTag()
{
    QString htmlCode = "<html>\n<h1>H1</h1><!--<h2>H2-->\n</html>";
    QList<Comment> commentsList = {};

    QList<Comment> expectedCommentsList = {};
    Comment comment;
    comment.rawData = "<!--<h2>H2-->";
    comment.startPos = 18;
    comment.endPos = 30;
    expectedCommentsList.append(comment);

    findAllComments(htmlCode, commentsList);

    QCOMPARE(commentsList, expectedCommentsList);
}

void findAllComments_tests::commentWithHeaderWithoutOpeningTag()
{
    QString htmlCode = "<html>\n<h1>H1</h1><!--H2</h2>-->\n</html>";
    QList<Comment> commentsList = {};

    QList<Comment> expectedCommentsList = {};
    Comment comment;
    comment.rawData = "<!--H2</h2>-->";
    comment.startPos = 18;
    comment.endPos = 31;
    expectedCommentsList.append(comment);

    findAllComments(htmlCode, commentsList);

    QCOMPARE(commentsList, expectedCommentsList);
}

void findAllComments_tests::emptyComment()
{
    QString htmlCode = "<html>\n<h1>H1</h1><!---->\n</html>";
    QList<Comment> commentsList = {};

    QList<Comment> expectedCommentsList = {};
    Comment comment;
    comment.rawData = "<!---->";
    comment.startPos = 18;
    comment.endPos = 24;
    expectedCommentsList.append(comment);

    findAllComments(htmlCode, commentsList);

    QCOMPARE(commentsList, expectedCommentsList);
}

void findAllComments_tests::complexTest()
{
    QString htmlCode = "<html>\n<h1>H1</h1><!---->\n<!--<h2>H2</h2>-->\n<!--<h3>H3-->\n<!--H4</h4>-->\n\n\n<!--It is\tcomment!-->\n</html>";
    QList<Comment> commentsList = {};

    QList<Comment> expectedCommentsList = {};
    Comment comment;
    comment.rawData = "<!---->";
    comment.startPos = 18;
    comment.endPos = 24;
    expectedCommentsList.append(comment);
    comment.rawData = "<!--<h2>H2</h2>-->";
    comment.startPos = 26;
    comment.endPos = 43;
    expectedCommentsList.append(comment);
    comment.rawData = "<!--<h3>H3-->";
    comment.startPos = 45;
    comment.endPos = 57;
    expectedCommentsList.append(comment);
    comment.rawData = "<!--H4</h4>-->";
    comment.startPos = 59;
    comment.endPos = 72;
    expectedCommentsList.append(comment);
    comment.rawData = "<!--It is\tcomment!-->";
    comment.startPos = 76;
    comment.endPos = 96;
    expectedCommentsList.append(comment);

    findAllComments(htmlCode, commentsList);

    QCOMPARE(commentsList, expectedCommentsList);
}

QTEST_APPLESS_MAIN(findAllComments_tests)

#include "tst_findallcomments_tests.moc"
