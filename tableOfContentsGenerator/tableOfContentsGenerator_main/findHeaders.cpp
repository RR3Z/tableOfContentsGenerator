#include "findHeaders.h"

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

void getRidOfCommentedCorrectHeaders(QList<Comment>& commentsList, QList<Header>& headersList)
{
    static QRegularExpression correctHeaderRegex("<h([1-6])[^>]*>(.*?)</h\\1>", QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatch match;
    QList<int> commentedHeadersPos;

    // Для каждого комментария из контейнера commentsList...
    for (QList<Comment>::iterator currentComment = commentsList.begin(); currentComment != commentsList.end(); )
    {
        // Если текущий комментарий содержит в себе корректно заданный h заголовок и не был обработан...
        match = correctHeaderRegex.match(currentComment->rawData);
        if(match.hasMatch() && currentComment->isProccessed == false)
        {
            // Сохранить позицию открывающего корректно заданный h заголовок тега в контейнер
            commentedHeadersPos.append(currentComment->startPos + match.capturedStart());
            // Считать, что текущий комментарий обработан
            currentComment->isProccessed = true;
        }
        // Иначе перейти к следующему комментарию
        else {
            ++currentComment;
        }
    }

    // Если нашелся хотя бы один комментарий с корректно заданным h заголовком...
    if(commentedHeadersPos.count() > 0)
    {
        // Для каждого заголовка из контейнера headersList...
        for (QList<Header>::iterator currentHeader = headersList.begin(); currentHeader != headersList.end(); )
        {
            // Если текущий заголовок закомменитрован...
            if(commentedHeadersPos.contains(currentHeader->startPos))
            {
                // Удалить текущий заголовок из контейнера headersList
                currentHeader = headersList.erase(currentHeader);
            }
            // Иначе перейти к следующему заголовку
            else {
                ++currentHeader;
            }
        }
    }
}

void getRidOfCommentedHeadersWithoutClosingTag(QList<Comment>& commentsList, QList<int>& headersPosWithoutClosingTag)
{
    static QRegularExpression openTagHeader("<h([1-6])[^>]*>", QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatch match;
    QList<int> commentedHeadersWithoutClosingTagPos;

    // Для каждого комментария из контейнера commentsList...
    for (QList<Comment>::iterator currentComment = commentsList.begin(); currentComment != commentsList.end(); )
    {
        // Если текущий комментарий содержит в себе открывающий h заголовок тег и не был обработан...
        match = openTagHeader.match(currentComment->rawData);
        if(match.hasMatch() && currentComment->isProccessed == false)
        {
            // Сохранить позицию текущего открывающего h заголовок тега в HTML-коде в контейнер
            commentedHeadersWithoutClosingTagPos.append(currentComment->startPos + match.capturedStart());
            // Считать, что текущий комментарий обработан
            currentComment->isProccessed = true;
        }
        // Иначе перейти к следующему комментарию
        else {
            ++currentComment;
        }
    }

    // Если имеется хотя бы один h заголовок, для которого отсутствует закрывающий его тег...
    if(headersPosWithoutClosingTag.count() > 0)
    {
        // Для каждого h заголовка, у которого отсутствует закрывающий его тег...
        for (QList<int>::iterator currentHeaderWithoutClosingTagPos = headersPosWithoutClosingTag.begin(); currentHeaderWithoutClosingTagPos != headersPosWithoutClosingTag.end(); )
        {
            // Если текущий h заголовок закомментирован...
            if (commentedHeadersWithoutClosingTagPos.contains(*currentHeaderWithoutClosingTagPos))
            {
                // Удалить текущий h заголовок из контейнера headersPosWithoutClosingTag
                currentHeaderWithoutClosingTagPos = headersPosWithoutClosingTag.erase(currentHeaderWithoutClosingTagPos);
            }
            // Иначе перейти к следующему h заголовку...
            else
            {
                ++currentHeaderWithoutClosingTagPos;
            }
        }
    }
}

void getRidOfCommentedHeadersWithoutOpeningTag(QList<Comment>& commentsList, QList<int>& headersPosWithoutOpeningTag)
{
    static QRegularExpression closeTagHeader("</h([1-6])>", QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatch match;
    QList<int> commentedHeadersWithoutOpeningTagPos;

    // Для каждого комментария из контейнера commentsList...
    for (QList<Comment>::iterator currentComment = commentsList.begin(); currentComment != commentsList.end(); )
    {
        // Если текущий комментарий содержит в себе закрывающий h заголовок тег...
        match = closeTagHeader.match(currentComment->rawData);
        if(match.hasMatch() && currentComment->isProccessed == false)
        {
            // Сохранить позицию текущего закрывающего h заголовок тега в HTML-коде в контейнер
            commentedHeadersWithoutOpeningTagPos.append(currentComment->startPos + match.capturedEnd() - 1);
            // Считать, что текущий комментарий обработан
            currentComment->isProccessed = true;
        }
        // Иначе перейти к следующему комментарию
        else {
            ++currentComment;
        }
    }

    // Если имеется хотя бы один h заголовок, для которого отсутствует открывающий его тег...
    if(headersPosWithoutOpeningTag.count() > 0)
    {
        // Для каждого h заголовка, с отсутствующим открывающим его тегом...
        for (QList<int>::iterator currentHeaderWithoutOpeningTagPos = headersPosWithoutOpeningTag.begin(); currentHeaderWithoutOpeningTagPos != headersPosWithoutOpeningTag.end(); )
        {
            // Если текущий h заголовок без открывающего его тега закоментирован...
            if (commentedHeadersWithoutOpeningTagPos.contains(*currentHeaderWithoutOpeningTagPos))
            {
                // Удалить текущий h заголовок из контейнера headersPosWithoutOpeningTag
                currentHeaderWithoutOpeningTagPos = headersPosWithoutOpeningTag.erase(currentHeaderWithoutOpeningTagPos);
            }
            // Иначе перейти к следующему элементу
            else
            {
                ++currentHeaderWithoutOpeningTagPos;
            }
        }
    }
}

void checkForNestedHeaders(const QList<Header>& headersList)
{
    static QRegularExpression correctHeaderRegex("<h([1-6])[^>]*>(.*?)</h\\1>", QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatch match;
    // Для всех найденных корректно заданных h заголовков...
    for(int i = 0; i<headersList.count(); i++)
    {
        match = correctHeaderRegex.match(headersList.at(i).content);
        // Если внутри текущего h заголовка нашелся вложенный h заголовок...
        if(match.hasMatch())
        {
            // Выкинуть ошибку: "В заголовке: '#' имеется вложенный заголовок '#'"
            throw QString("Для заголовка '" + headersList.at(i).rawData + "', который начинается с позиции '" + QString::number(headersList.at(i).startPos) + "', имеется вложенный заголовок '" + match.captured() + "'");
        }
    }
}

void findHeaders (const QString& htmlCode, QList<Header>& headersList)
{

}
