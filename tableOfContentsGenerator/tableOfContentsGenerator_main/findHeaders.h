#include <QCoreApplication>
#include <QRegularExpression>
#include <iostream>
using namespace std;

/*!
*\file
*\brief Данный  файл содержит в себе заголовки функций, которые используются в findHeaders.
*/

/*!
* \brief Структура для хранения информации о заголовках
* \param level - уровень заголовка
* \param rawData - заголовок в том виде, в каком он есть
* \param content - содержимое заголовка
* \param startPos - начальная позиция заголовка в HTML-коде
* \param endPos - конечная позиция заголовка в HTML-коде
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
* \brief Структура для хранения информации о комментариях
* \param rawData - комментарий в том виде, в каком он есть
* \param startPos - начальная позиция комментария в HTML-коде
* \param endPos - конечная позиция комментария в HTML-коде
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
* \brief Найти h заголовки в HTML-коде
* \param[in] htmlCode - строка с HTML-кодом
* \param[in,out] headersList - контейнер с h заголовками
* \throw выбрасывает исключения в случае ошибок
*/
void findHeaders (const QString& htmlCode, QList<Header>& headersList);

/*!
* \brief Найти корректно заданные h заголовки (в том числе закомментированные)
* \param[in] htmlCode - строка с HTML-кодом
* \param[in,out] headersList - контейнер, куда будут сохраняться найденные h заголовки
*/
void findCorrectHeaders(const QString& htmlCode, QList<Header>& headersList);

/*!
* \brief Найти h заголовки, для которых отсутствует закрывающий тег (в том числе закомментированные)
* \param[in] htmlCode - строка с HTML-кодом
* \param[in] headersList - контейнер с h заголовками
* \param[in,out] openTagHeadersPos - контейнер, в котором хранятся позиции h заголовков без закрывающих тегов
*/
void findSeperateOpenTagHeaders(const QString& htmlCode, const QList<Header>& headersList, QList<int>& openTagHeadersPos);

/*!
* \brief Найти h заголовки, для которых отсутствует открывающий тег (в том числе закомментированные)
* \param[in] htmlCode - строка с HTML-кодом
* \param[in] headersList - контейнер с h заголовками
* \param[in,out] closeTagHeadersPos - контейнер, в котором хранятся позиции h заголовков без открывающих тегов
*/
void findSeperateCloseTagHeaders(const QString& htmlCode, const QList<Header>& headersList, QList<int>& closeTagHeadersPos);

/*!
* \brief Найти все комментарии в HTML-коде
* \param[in] htmlCode - строка с HTML-кодом
* \param[in,out] commentsList - контейнер с найденными комментариями
*/
void findAllComments(const QString& htmlCode, QList<Comment>& commentsList);

/*!
* \brief Избавиться от закомментированных корректно заданных h заголовков
* \param[in] commentsList - контейнер с комментариями
* \param[in,out] headersList - контейнер c найденными h заголовками, который чистят от закомментированных корректно заданных h заголовков
*/
void getRidOfCommentedCorrectHeaders(const QList<Comment>& commentsList, QList<Header>& headersList);

/*!
* \brief Избавиться от закомментированных h заголовков без закрывающего их тега
* \param[in] commentsList - контейнер с комментариями
* \param[in,out] openTagHeadersPos - контейнер c позициями открывающих h заголовки тегов, для которых отсутствуют закрывающие h заголовки теги
*/
void getRidOfCommentedHeadersWithoutClosingTag(const QList<Comment>& commentsList, QList<int>& openTagHeadersPos);

/*!
* \brief Избавиться от закомментированных h заголовков без открывающего их тега
* \param[in] commentsList - контейнер с комментариями
* \param[in,out] closeTagHeadersPos - контейнер c позициями закрывающих h заголовки тегов, для которых отсутствуют открывающие h заголовки теги
*/
void getRidOfCommentedHeadersWithoutOpeningTag(const QList<Comment>& commentsList, QList<int>& closeTagHeadersPos);

/*!
* \brief Проверить найденные h заголовки на вложенные в них h заголовки
* \param[in] headersList - контейнер с найденными h заголовками
* \throw выбрасывает исключения в случае ошибок
*/
void checkForNestedHeaders(const QList<Header>& headersList);
