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
struct CommentedString
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
* \Проверить на вложенность в друг друга h заголовки
* \param[in] headerForCheck - заголовок для проверки
* \param[in] nestedHeader - заголовок, куда будут сохраняться данные об вложенном заголовке
* \return - результат выполнения функции (false - вложенные в друг друга заголовки не были найдены, true - вложенные в друг друга заголовки были найдены)
*/
bool checkForNestedHeaders (const Header& headerForCheck, Header& nestedHeader);
