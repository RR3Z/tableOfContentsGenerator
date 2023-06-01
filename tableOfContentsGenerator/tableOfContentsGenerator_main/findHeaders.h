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

    //! Оператор перегрузки, для сравнения двух Comment (используется при тестировании)
    bool operator == (const Comment& other) const
    {
        return rawData == other.rawData &&
               startPos == other.startPos &&
               endPos == other.endPos;
    }
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
* \Найти h заголовки, для которых отсутствует закрывающий тег (в том числе закомментированные)
* \param[in] htmlCode - строка с HTML-кодом
* \param[in] headersList - контейнер с h заголовками
* \param[in,out] openTagHeadersPos - контейнер, в котором хранятся позиции h заголовков без закрывающих тегов
*/
void findSeperateOpenTagHeaders(const QString& htmlCode, const QList<Header>& headersList, QList<int>& openTagHeadersPos);

/*!
* \Найти h заголовки, для которых отсутствует открывающий тег (в том числе закомментированные)
* \param[in] htmlCode - строка с HTML-кодом
* \param[in] headersList - контейнер с h заголовками
* \param[in,out] closeTagHeadersPos - контейнер, в котором хранятся позиции h заголовков без открывающих тегов
*/
void findSeperateCloseTagHeaders(const QString& htmlCode, const QList<Header>& headersList, QList<int>& closeTagHeadersPos);

/*!
* \Найти все комментарии в HTML-коде
* \param[in] htmlCode - строка с HTML-кодом
* \param[in,out] commentsList - контейнер с найденными комментариями
*/
void findAllComments(const QString& htmlCode, QList<Comment>& commentsList);

/*!
* \Избавиться от закомментированных корректно заданных h заголовков
* \param[in] commentsList - контейнер с комментариями
* \param[in,out] headersList - контейнер c найденными h заголовками, который чистят от закомментированных корректно заданных h заголовков
*/
void getRidOfCommentedCorrectHeaders(QList<Comment> commentsList, QList<Header>& headersList);

/*!
* \Избавиться от закомментированных h заголовков без закрывающего их тега из контейнера с позициями открывающих h заголовки тегов
* \param[in] commentsList - контейнер с комментариями
* \param[in,out] openTagHeadersPos - контейнер c позициями открывающих h заголовки тегов, для которых отсутствуют закрывающие h заголовки теги
*/
void getRidOfCommentedHeadersWithoutClosingTag(QList<Comment> commentsList, QList<int>& openTagHeadersPos);

/*!
* \Избавиться от закомментированных h заголовков без открывающего их тега из контейнера с позициями закрывающих h заголовки тегов
* \param[in] commentsList - контейнер с комментариями
* \param[in,out] closeTagHeadersPos - контейнер c позициями закрывающих h заголовки тегов, для которых отсутствуют открывающие h заголовки теги
*/
void getRidOfCommentedHeadersWithoutOpeningTag(QList<Comment> commentsList, QList<int>& closeTagHeadersPos);

/*!
* \Проверить найденные h заголовки на вложенные в них h заголовки
* \param[in] headersList - контейнер с найденными h заголовками
* \throw - выбрасывает исключения в случае ошибок
*/
void checkForNestedHeaders(const QList<Header>& headersList);
