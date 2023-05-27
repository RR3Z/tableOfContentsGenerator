#include "tableOfContentsGenerator.h"

void findCorrectHeaders(const QString& htmlCode, QList<Header>& headersList)
{
    Header header;
    Header nestedHeader;
    static QRegularExpression headerRegex("<h([1-6])[^>]*>(.*?)</h\\1>", QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatchIterator matchIterator = headerRegex.globalMatch(htmlCode);
    QRegularExpressionMatch match;
    // Для каждого найденного корректно заданного h заголовка...
    while (matchIterator.hasNext())
    {
        // Получить информацию о заголовке
        match = matchIterator.next();
        header.level = match.captured(1).toInt();
        header.rawData = match.captured();
        header.content = match.captured(2);
        header.startPos = match.capturedStart();
        header.endPos = match.capturedEnd() - 1;
        // Сохранить заголовок в контейнер
        headersList.append(header);
    }

}
