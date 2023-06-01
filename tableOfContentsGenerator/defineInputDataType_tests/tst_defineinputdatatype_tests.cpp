#include <QtTest>
#include <../tableOfContentsGenerator_main/tableOfContentsGenerator.h>

class defineInputDataType_tests : public QObject
{
    Q_OBJECT
private slots:
    void inputDataIsFile();
    void inputDataIsURL();
    void unsupportedInputFileFormat();
    void specifiedFileIsMissing();
    void inputDataIsMissing();
    void httpSupportedUrlProtocol();
    void unsupportedUrlProtocol();
    void extraCharactersInArgument();
    void invalidNumberOfArguments();
};

void defineInputDataType_tests::inputDataIsFile()
{
    int argc = 2;
    char* inputArgs[2];
    char arg1[] = "generateTableOfContents.exe";
    char arg2[] = "../../testFiles/defineInputDataType_tests/inputDataIsFile.html";
    inputArgs[0] = arg1;
    inputArgs[1] = arg2;
    dataType expectedResult = FILE_TYPE;
    dataType functionResult = defineInputDataType(argc, inputArgs);
    QCOMPARE(functionResult,expectedResult);
}

void defineInputDataType_tests::inputDataIsURL()
{
    int argc = 2;
    char* inputArgs[2];
    char arg1[] = "generateTableOfContents.exe";
    char arg2[] = "https://example.com";
    inputArgs[0] = arg1;
    inputArgs[1] = arg2;
    dataType expectedResult = URL_TYPE;
    dataType functionResult = defineInputDataType(argc, inputArgs);
    QCOMPARE(functionResult,expectedResult);
}

void defineInputDataType_tests::unsupportedInputFileFormat()
{
    int argc = 2;
    char* inputArgs[2];
    char arg1[] = "generateTableOfContents.exe";
    char arg2[] = "../../testFiles/defineInputDataType_tests/unsupportedInputFileFormat.txt";
    inputArgs[0] = arg1;
    inputArgs[1] = arg2;
    try
    {
        dataType functionResult = defineInputDataType(argc, inputArgs);
    }
    catch (QString exceptionMessage)
    {
        QCOMPARE(exceptionMessage,"Формат входного файла по пути '../../testFiles/defineInputDataType_tests/unsupportedInputFileFormat.txt' не соответствует требованиям ПО (должен быть 'html')");
    }
}

void defineInputDataType_tests::specifiedFileIsMissing()
{
    int argc = 2;
    char* inputArgs[2];
    char arg1[] = "generateTableOfContents.exe";
    char arg2[] = "../../testFiles/defineInputDataType_tests/noSuchFile.exe";
    inputArgs[0] = arg1;
    inputArgs[1] = arg2;
    try
    {
        dataType functionResult = defineInputDataType(argc, inputArgs);
    }
    catch (QString exceptionMessage)
    {
        QCOMPARE(exceptionMessage,"По пути '../../testFiles/defineInputDataType_tests/noSuchFile.exe' нет заданного файла");
    }

}

void defineInputDataType_tests::inputDataIsMissing()
{
    int argc = 1;
    char* inputArgs[1];
    char arg1[] = "generateTableOfContents.exe";
    inputArgs[0] = arg1;
    try
    {
        dataType functionResult = defineInputDataType(argc, inputArgs);
    }
    catch (QString exceptionMessage)
    {
        QCOMPARE(exceptionMessage,"Отсутствует аргумент с входными данными");
    }

}

void defineInputDataType_tests::httpSupportedUrlProtocol()
{
    int argc = 2;
    char* inputArgs[2];
    char arg1[] = "generateTableOfContents.exe";
    char arg2[] = "http://example.com";
    inputArgs[0] = arg1;
    inputArgs[1] = arg2;
    dataType expectedResult = URL_TYPE;
    dataType functionResult = defineInputDataType(argc, inputArgs);
    QCOMPARE(functionResult,expectedResult);
}

void defineInputDataType_tests::unsupportedUrlProtocol()
{
    int argc = 2;
    char* inputArgs[2];
    char arg1[] = "generateTableOfContents.exe";
    char arg2[] = "file:///C:/Users/student/Downloads/4d6.jpeg";
    inputArgs[0] = arg1;
    inputArgs[1] = arg2;
    try
    {
        dataType functionResult = defineInputDataType(argc, inputArgs);
    }
    catch (QString exceptionMessage)
    {
        QCOMPARE(exceptionMessage,"Неподдерживаемый  протокол URL-адреса (должен быть 'http://' или 'https://'): file:///C:/Users/student/Downloads/4d6.jpeg");
    }
}

void defineInputDataType_tests::extraCharactersInArgument()
{
    int argc = 2;
    char* inputArgs[2];
    char arg1[] = "generateTableOfContents.exe";
    char arg2[] = "    ../testFiles/defineInputDataType_tests/extraCharactersInArgument.html";
    inputArgs[0] = arg1;
    inputArgs[1] = arg2;
    try
    {
        dataType functionResult = defineInputDataType(argc, inputArgs);
    }
    catch (QString exceptionMessage)
    {
        QCOMPARE(exceptionMessage,"Аргумент, переданный с запуском программы, содержит недопустимые пробелы в начале");
    }
}

void defineInputDataType_tests::invalidNumberOfArguments()
{
    int argc = 3;
    char* inputArgs[3];
    char arg1[] = "generateTableOfContents.exe";
    char arg2[] = "a";
    char arg3[] = "b";
    inputArgs[0] = arg1;
    inputArgs[1] = arg2;
    inputArgs[2] = arg3;
    try
    {
        dataType functionResult = defineInputDataType(argc, inputArgs);
    }
    catch (QString exceptionMessage)
    {
        QCOMPARE(exceptionMessage,"Неверное количество переданных аргументов (больше 2)");
    }
}

QTEST_APPLESS_MAIN(defineInputDataType_tests)

#include "tst_defineinputdatatype_tests.moc"
