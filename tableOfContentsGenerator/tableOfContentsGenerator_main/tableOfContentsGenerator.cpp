#include "tableOfContentsGenerator.h"

void findCorrectHeaders(const QString& htmlCode, QList<Header>& headersList)
{
    Header header;
    Header nestedHeader;
    static QRegularExpression correctHeaderRegex("<h([1-6])[^>]*>(.*?)</h\\1>", QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatchIterator matchIterator = correctHeaderRegex.globalMatch(htmlCode);
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

void findSeperateOpenTagHeaders(const QString& htmlCode, const QList<Header>& headersList, QList<int>& openTagHeadersPos)
{
    static QRegularExpression openTagHeader("<h([1-6])[^>]*>.*?(?!(?:<h([1-6])[^>]*>))", QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatchIterator matchIterator = openTagHeader.globalMatch(htmlCode);
    QRegularExpressionMatch match;

    // Для каждого найденного открывающего h заголовок тега...
    matchIterator = openTagHeader.globalMatch(htmlCode);
    while (matchIterator.hasNext())
    {
        // Сохранить позицию найденного открывающего h заголовок тега в контейнер
        match = matchIterator.next();
        openTagHeadersPos.append(match.capturedStart());
    }

    // Для всех корректно заданных h заголовков...
    for(int i = 0; i < headersList.count(); i++)
    {
        // Если позиция открывающего корректно заданного h заголовка тега совпадает с позицией найденного открывающего h заголовок тега...
        if(openTagHeadersPos.contains(headersList.at(i).startPos))
        {
            // Удалить позицию найденного открывающего h заголовок тега из контейнера с найденными позициями открывающих h заголовки тегов
            openTagHeadersPos.removeAt(openTagHeadersPos.indexOf(headersList.at(i).startPos));
        }
    }
}

void findSeperateCloseTagHeaders(const QString& htmlCode, const QList<Header>& headersList, QList<int>& closeTagHeadersPos)
{
    static QRegularExpression closeTagHeader("</h[1-6]>.*?(?!(?:<h/[1-6]>))", QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatchIterator matchIterator = closeTagHeader.globalMatch(htmlCode);
    QRegularExpressionMatch match;

    // Для каждого найденного закрывающего h заголовок тега...
    matchIterator = closeTagHeader.globalMatch(htmlCode);
    while (matchIterator.hasNext())
    {
        // Сохранить позицию найденного закрывающего h заголовок тега в контейнер
        match = matchIterator.next();
        closeTagHeadersPos.append(match.capturedEnd() - 1);
    }

    // Для всех корректно заданных h заголовков...
    for(int i = 0; i < headersList.count(); i++)
    {
        // Если позиция закрывающего корректно заданного h заголовка тега совпадает с позицией найденного закрывающего h заголовок тега...
        if(closeTagHeadersPos.contains(headersList.at(i).endPos))
        {
            // Удалить позицию найденного закрывающего h заголовок тега из контейнера с найденными позициями закрывающих h заголовки тегов
            closeTagHeadersPos.removeAt(closeTagHeadersPos.indexOf(headersList.at(i).endPos));
        }
    }
}

void findAllComments(const QString& htmlCode, QList<Comment>& commentsList)
{
    static QRegularExpression commentsRegex("<!--(.*?)-->", QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatchIterator matchIterator = commentsRegex.globalMatch(htmlCode);
    QRegularExpressionMatch match;
    Comment comment;

    // Для каждого найденного комментария...
    while (matchIterator.hasNext())
    {
        match = matchIterator.next();
        // Запомнить информацию об найденном комментарии
        comment.rawData = match.captured();
        comment.startPos = match.capturedStart();
        comment.endPos = match.capturedEnd() - 1;
        // Сохранить найденный комментарий в контейнер
        commentsList.append(comment);
    }
}

void findHeaders (const QString& htmlCode, QList<Header>& headersList)
{

}
