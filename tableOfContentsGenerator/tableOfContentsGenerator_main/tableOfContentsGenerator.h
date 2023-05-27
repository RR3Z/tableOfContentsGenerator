#include <QCoreApplication>
#include <QRegularExpression>
#include <iostream>
using namespace std;

/*!
* \Структура для хранения информации о заголовках
*/
struct Header
{
    int level;
    QString rawData;
    QString content;
    int startPos;
    int endPos;
};

/*!
* \Структура для хранения информации о комментариях
*/
struct Comment
{
    QString rawData;
    int startPos;
    int endPos;
};

/*!
* \Найти h заголовки в HTML-коде
* \param[in] htmlCode - строка с HTML-кодом
* \param[in,out] headersList - контейнер с h заголовками
* \throw - выбрасывает исключения в случае ошибок
*/
void findHeaders (const QString& htmlCode, QList<Header>& headersList);

/*!
* \Найти корректно заданные h заголовки (в том числе задокумментированные)
* \param[in] htmlCode - строка с HTML-кодом
* \param[in,out] headersList - контейнер, куда будут сохраняться найденные h заголовки
*/
void findCorrectHeaders(const QString& htmlCode, QList<Header>& headersList);
