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

    //! Оператор перегрузки, для сравнения двух Header (используется при тестировании)
    bool operator == (const Header& other) const
    {
        return level == other.level &&
               rawData == other.rawData &&
               content == other.content &&
               startPos == other.startPos &&
               endPos == other.endPos;
    }
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

/*!
* \Найти h заголовки, для которых отсутствует закрывающий тег (в том числе задокумментированные)
* \param[in] htmlCode - строка с HTML-кодом
* \param[in] headersList - контейнер с h заголовками
* \param[in,out] missingClosingTagHeadersPos - контейнер, в котором хранятся позиции заголовков, для которых отсутствует закрывающий их тег
*/
void findHeadersWithoutClosingTag(const QString& htmlCode, const QList<Header>& headersList, QList<int>& missingClosingTagHeadersPos);

/*!
* \Найти h заголовки, для которых отсутствует открывающий тег (в том числе задокумментированные)
* \param[in] htmlCode - строка с HTML-кодом
* \param[in] headersList - контейнер с h заголовками
* \param[in,out] missingOpeningTagHeadersPos - контейнер, в котором хранятся позиции заголовков, для которых отсутствует открывающий их тег
*/
void findHeadersWithoutOpeningTag(const QString& htmlCode, const QList<Header>& headersList, QList<int>& missingOpeningTagHeadersPos);

/*!
* \Найти все комментарии в HTML-коде
* \param[in] htmlCode - строка с HTML-кодом
* \param[in,out] commentsList - контейнер с найденными комментариями
*/
void findAllComments(const QString& htmlCode, QList<Comment>& commentsList);

/*!
* \Удалить задокументированные корректно заданные h заголовки из контейнера с найденными h заголовками
* \param[in,out] comments - контейнер с комментариями
* \param[in,out] headers - контейнер c найденными h заголовками, который чистят от задокументированных корректно заданных h заголовков
*/
void removeCommentedCorrectHeaders(QList<Comment>& comments, QList<Header>& headers);
