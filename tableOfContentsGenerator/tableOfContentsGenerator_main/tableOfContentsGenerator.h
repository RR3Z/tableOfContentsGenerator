#include "findHeaders.h"
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>

/*!
*\file
*\brief Данный заголовочный файл содержит в себе описание основных функций, которые используются в программе.
*/

/*!
* \brief Перечисление типов входных данных
*/
enum dataType{
    FILE_TYPE = 0,
    URL_TYPE = 1,
    WRONG_TYPE = 2
};

/*!
* \brief Определить тип входных данных
* \param[in] argsCounter - количество аргументов, переданных с запуском программы
* \param[in] inputArgs – аргументы, переданные с запуском программы
* \return тип входных данных (FILE_TYPE - файл, URL_TYPE - url)
* \throw выбрасывает исключения в случае ошибок
*/
dataType defineInputDataType (const int& argsCounter, char* inputArgs[]);

/*!
* \brief Выгрузить HTML-код страницы
* \param[in] url - строка с URL-адресом
* \param[in,out] inputData – строка с выгруженным HTML-кодом страницы
* \throw выбрасывает исключения в случае ошибок
*/
void uploadHtmlCodeByUrl (const QString& url, QString& inputData);

/*!
* \brief Считать входные данные из файла
* \param[in] inputPath - строка с путем к файлу
* \param[in,out] inputData - строка с содержимым файла
* \throw выбрасывает исключения в случае ошибок
*/
void readInputDataFromFile (const QString& inputPath, QString& inputData);

/*!
* \brief Сгенерировать оглавление HTML-страницы
* \param[in] headersList - контейнер с h заголовками
* \param[in,out] tableOfContents - строка с созданным оглавлением
*/
void generateTableOfContents (const QList<Header>& headersList, QString& tableOfContents);

/*!
* \brief Сохранить данные в файл
* \param[in] outputData - строка с данными, которые требуется сохранить в файл
* \throw выбрасывает исключения в случае ошибок
*/
void saveDataToFile (const QString& outputData);

/*!
* \brief Проверить контейнер на пустое
* \param[in] headersList - контейнер с h заголовками
* \return результат выполнения функции (false – в контейнере имеются какие-либо элементы, true – в контейнере отсутствуют какие-либо элементы)
*/
bool isListEmpty (const QList<Header>& headersList);
