#include <QCoreApplication>
#include "tableOfContentsGenerator.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    dataType inputDataType;
    QString inputData;
    QList<Header> headersList;
    QString tableOfContents;

    try
    {
        // Определить тип входных данных...
        inputDataType = defineInputDataType(argc, argv);

        // Если в качестве аргумента, переданного с запуском программы, был передан путь к файлу...
        if (inputDataType == FILE_TYPE)
        {
            // Выгрузить содержимое файла в inputData
            readInputDataFromFile(argv[1], inputData);
        }

        // Если в качестве аргумента, переданного с запуском программы, был передан URL-адрес...
        if (inputDataType == URL_TYPE)
        {
            // Выгрузить HTML-код страницы в inputData
            uploadHtmlCodeByUrl(argv[1], inputData);
        }

        // Найти в HTML-коде h заголовки...
        findHeaders(inputData, headersList);

        // Проверить контейнер с найденными h заголовками на пустое...
        isListEmpty(headersList);

        // Сгенерировать оглавление HTML-страницы...
        generateTableOfContents(headersList, tableOfContents);

        // Сохранить сгенерированное оглавление в файл...
        saveDataToFile(tableOfContents);
    }
    catch (QString exceptionMessage)
    {
        // Вывести пользователю сообщение об ошибке
        cout << exceptionMessage.toStdString() << endl;
    }

    return a.exec();
}
