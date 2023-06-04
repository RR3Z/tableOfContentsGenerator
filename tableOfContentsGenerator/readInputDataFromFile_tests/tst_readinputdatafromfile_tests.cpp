#include <QtTest>
#include <../tableOfContentsGenerator_main/tableOfContentsGenerator.h>

class readInputDataFromFile_tests : public QObject
{
    Q_OBJECT

private slots:
    void fileIsAvailable();
    void fileIsNotAvailable();

};

void readInputDataFromFile_tests::fileIsAvailable()
{
    QString inputPath = "../../testFiles/readInputDataFromFile_tests/fileIsAvailable.html";
    QString inputData = "";

    QString expectedInputData = "<!DOCTYPE html>\r\n<html>\r\n<head>\r\n  <title>Страница с большим количеством заголовков</title>\r\n</head>\r\n<body>\r\n  <h1>Заголовок 1</h1>\r\n  <h2>Заголовок 2</h2>\r\n  <h3>Заголовок 3</h3>\r\n  <h4>Заголовок 4</h4>\r\n  <h5>Заголовок 5</h5>\r\n  <h6>Заголовок 6</h6>\r\n  <h1>Еще один заголовок 1</h1>\r\n  <h2>Еще один заголовок 2</h2>\r\n  <h3>Еще один заголовок 3</h3>\r\n  <h4>Еще один заголовок 4</h4>\r\n  <h5>Еще один заголовок 5</h5>\r\n  <h6>Еще один заголовок 6</h6>\r\n  \r\n  <h1>Заголовок 1</h1>\r\n  <h2>Заголовок 2</h2>\r\n  <h3>Заголовок 3</h3>\r\n  <h4>Заголовок 4</h4>\r\n  <h5>Заголовок 5</h5>\r\n  <h6>Заголовок 6</h6>\r\n  <h1>Еще один заголовок 1</h1>\r\n  <h2>Еще один заголовок 2</h2>\r\n  <h3>Еще один заголовок 3</h3>\r\n  <h4>Еще один заголовок 4</h4>\r\n  <h5>Еще один заголовок 5</h5>\r\n  <h6>Еще один заголовок 6</h6>\r\n  \r\n  <h1>Заголовок 1</h1>\r\n  <h2>Заголовок 2</h2>\r\n  <h3>Заголовок 3</h3>\r\n  <h4>Заголовок 4</h4>\r\n  <h5>Заголовок 5</h5>\r\n  <h6>Заголовок 6</h6>\r\n  <h1>Еще один заголовок 1</h1>\r\n  <h2>Еще один заголовок 2</h2>\r\n  <h3>Еще один заголовок 3</h3>\r\n  <h4>Еще один заголовок 4</h4>\r\n  <h5>Еще один заголовок 5</h5>\r\n  <h6>Еще один заголовок 6</h6>\r\n</body>\r\n</html>";

    readInputDataFromFile(inputPath, inputData);

    QCOMPARE(inputData, expectedInputData);
}

void readInputDataFromFile_tests::fileIsNotAvailable()
{
    QString inputPath = "../../testFiles/readInputDataFromFile_tests/fileIsNotAvailable.html";
    QString inputData = "";

    try
    {
        readInputDataFromFile(inputPath, inputData);
    }
    catch (QString exceptionMessage)
    {
        QCOMPARE(exceptionMessage, "Отсутствует доступ к файлу '../../testFiles/readInputDataFromFile_tests/fileIsNotAvailable.html' (возможно, недостаточно прав).");
    }

    QCOMPARE(inputData, "");
}

QTEST_APPLESS_MAIN(readInputDataFromFile_tests)

#include "tst_readinputdatafromfile_tests.moc"
