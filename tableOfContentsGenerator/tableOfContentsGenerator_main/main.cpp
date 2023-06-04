/*!
*\file
*\brief Данный файл содержит главную управляющую функцию программы
*\mainpage Документация для программы "Table of Contents Generator"
Программа предназначена для сокращения автоматической генерации оглавления HTML-страницы.
Для функционирования программы необходима операционная система Windows 7 или выше.
Программа разработана на языке С++ с использованием библиотеки Qt.
Стандарт языка ISO C++17 (/std:c++17).
Программа должна получать один аргумент командной строки: имя входного файла в формате html.

Пример команды запуска программы:
*\code
tableOfContentsGenerator_main.exe C:\input.html
*\endcode
или
*\code
tableOfContentsGenerator_main.exe ./input.html
*\endcode
*\author Chernobaev Egor
*\date May 2023
*\version 1.0
*/

#include "tableOfContentsGenerator.h"

/*!
*\brief Главная управляющая функция программы
*\param[in] argv[0]- путь к программе
*\param[in] argv[1] - путь к файлу с входными данными
*\return 0 - запуск программы прошел успешно
*/
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    setlocale(LC_ALL, "Russian");

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

        // Если контейнер с h заголовками пустой...
        if (isListEmpty(headersList))
        {
            // Выкинуть ошибку: "В заданном HTML-коде отсутствую h заголовки"
            throw QString("В заданном HTML-коде отсутствую h заголовки");
        }

        // Сгенерировать оглавление HTML-страницы...
        generateTableOfContents(headersList, tableOfContents);

        // Сохранить сгенерированное оглавление в файл...
        saveDataToFile(tableOfContents);

        // Вывести пользователю сообщение о завершении работы программы
        qDebug() << "Работа программы успешно завершена!";
    }
    catch (QString exceptionMessage)
    {
        // Вывести пользователю сообщение об ошибке
        qDebug() << exceptionMessage;
    }

    return a.exec();
}
