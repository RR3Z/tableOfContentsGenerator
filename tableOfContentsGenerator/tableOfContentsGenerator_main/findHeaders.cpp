/*!
*\file
*\brief Данный  файл содержит в себе реализацию функций, которые используются в findHeaders.
*/

#include "findHeaders.h"

QRegularExpression correctHeader("<h([1-6])[^>]*>(.*?)</h\\1>", QRegularExpression::DotMatchesEverythingOption);
QRegularExpression openTagHeader("<h([1-6])[^>]*>");
QRegularExpression closeTagHeader("</h([1-6])>");
QRegularExpression comment("<!--(.*?)-->", QRegularExpression::DotMatchesEverythingOption);

void findCorrectHeaders(const QString& htmlCode, QList<Header>& headersList)
{
    Header header;
    QList<int> tagHeadersPos;
    static QRegularExpression commentedOpenTagHeader("<!--\\s*<h([1-6])[^>]*>\\s*-->");
    static QRegularExpression commentedCloseTagHeader("<!--\\s*</h([1-6])>\\s*-->");

    // Найти все корректно заданные h заголовки в HTML-коде
    QRegularExpressionMatchIterator matchIterator = correctHeader.globalMatch(htmlCode);
    QRegularExpressionMatch match;

    // Для каждого найденного корректно заданного h заголовка...
    while (matchIterator.hasNext())
    {
        match = matchIterator.next();
        // Получить информацию о заголовке
        header.level = match.captured(1).toInt();
        header.rawData = match.captured();
        header.content = match.captured(2);
        header.startPos = match.capturedStart();
        header.endPos = match.capturedEnd() - 1;
        // Сохранить заголовок в контейнер
        headersList.append(header);
    }

    // Найти все закомментированные открывающие h заголовки теги в HTML-коде
    matchIterator = commentedOpenTagHeader.globalMatch(htmlCode);

    // Для каждого закомментированного открывающего h заголовок тега...
    while (matchIterator.hasNext())
    {
        match = matchIterator.next();
        // Сохранить позицию найденного тега в контейнер tagHeadersPos
        tagHeadersPos.append(match.capturedStart() + match.captured().indexOf(openTagHeader));
    }

    // Найти все закомментированные закрывающие h заголовки теги в HTML-коде
    matchIterator = commentedCloseTagHeader.globalMatch(htmlCode);

    // Для каждого закомментированного закрывающего h заголовок тега...
    while (matchIterator.hasNext())
    {
        match = matchIterator.next();
        // Сохранить позицию найденного тега в контейнер tagHeadersPos
        tagHeadersPos.append(match.capturedStart() + match.captured().indexOf(closeTagHeader) + 4);
    }

    // Для каждого заголовка из контейнера headersList...
    for (QList<Header>::iterator currentHeader = headersList.begin(); currentHeader != headersList.end(); )
    {
        // Если был найден корректно заданный h заголовок с закомментированным тегом открытия/закрытия...
        if (tagHeadersPos.contains(currentHeader->startPos) || tagHeadersPos.contains(currentHeader->endPos))
        {
            // Удалить текущий заголовок из контейнера headersList
            currentHeader = headersList.erase(currentHeader);
        }
        // Иначе перейти к следующему заголовку
        else
        {
            ++currentHeader;
        }
    }
}

void findSeperateOpenTagHeaders(const QString& htmlCode, const QList<Header>& headersList, QList<int>& openTagHeadersPos)
{
    // Найти в HTML-коде все открывающие h заголовки теги
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
    // Найти в HTML-коде все закрывающие h заголовки теги
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
    // Найти в HTML-коде все комментарии
    QRegularExpressionMatchIterator matchIterator = comment.globalMatch(htmlCode);
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

void getRidOfCommentedCorrectHeaders(const QList<Comment>& commentsList, QList<Header>& headersList)
{
    QRegularExpressionMatch match;
    QList<int> commentedHeadersPos;

    // Для каждого комментария из контейнера commentsList...
    for (QList<Comment>::const_iterator currentComment = commentsList.begin(); currentComment != commentsList.end(); )
    {
        // Найти в текущем комментарии корректно заданный h заголовок
        match = correctHeader.match(currentComment->rawData);
        // Если текущий комментарий содержит в себе корректно заданный h заголовок...
        if(match.hasMatch())
        {
            // Сохранить позицию открывающего корректно заданный h заголовок тега в контейнер
            commentedHeadersPos.append(currentComment->startPos + match.capturedStart());
        }
        // Перейти к следующему комментарию
        ++currentComment;
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

void getRidOfCommentedHeadersWithoutClosingTag(const QList<Comment>& commentsList, QList<int>& openTagHeadersPos)
{
    QRegularExpressionMatchIterator matchIterator;
    QRegularExpressionMatch match;

    // Если имеется хотя бы один открывающий h заголовок тег в контейнере openTagHeadersPos...
    if (openTagHeadersPos.count() > 0)
    {
        // Для каждого комментария из контейнера commentsList...
        for (QList<Comment>::const_iterator currentComment = commentsList.begin(); currentComment != commentsList.end(); )
        {
            // Найти в текущем комментарии все открывающие h заголовок теги
            matchIterator = openTagHeader.globalMatch(currentComment->rawData);
            // Пока не будут обработаны все открывающие h заголовк теги в текущем комментарии...
            while(matchIterator.hasNext())
            {
                match = matchIterator.next();

                // Если найденный открывающий h заголовок тег имеется в контейнере openTagHeadersPos...
                if (openTagHeadersPos.contains(currentComment->startPos + match.capturedStart()))
                {
                    // Удалить закомментированный открывающий h заголовок тег из контейнера openTagHeadersPos
                    openTagHeadersPos.removeAt(openTagHeadersPos.indexOf(currentComment->startPos + match.capturedStart()));
                }
            }

            // Перейти к следующему комментарию
            ++currentComment;
        }
    }
}

void getRidOfCommentedHeadersWithoutOpeningTag(const QList<Comment>& commentsList, QList<int>& closeTagHeadersPos)
{
    QRegularExpressionMatchIterator matchIterator;
    QRegularExpressionMatch match;

    // Если имеется хотя бы один открывающий h заголовок тег в контейнере closeTagHeadersPos...
    if (closeTagHeadersPos.count() > 0)
    {
        // Для каждого комментария из контейнера commentsList...
        for (QList<Comment>::const_iterator currentComment = commentsList.begin(); currentComment != commentsList.end(); )
        {
            // Найти в текущем комментарии все закрывающие h заголовок теги
            matchIterator = closeTagHeader.globalMatch(currentComment->rawData);
            // Пока не будут обработаны все закрывающие h заголовк теги в текущем комментарии...
            while(matchIterator.hasNext())
            {
                match = matchIterator.next();

                // Если найденный закрывающий h заголовок тег имеется в контейнере closeTagHeadersPos...
                if (closeTagHeadersPos.contains(currentComment->startPos + match.capturedEnd() - 1))
                {
                    // Удалить закомментированный закрывающий h заголовок тег из контейнера closeTagHeadersPos
                    closeTagHeadersPos.removeAt(closeTagHeadersPos.indexOf(currentComment->startPos + match.capturedEnd() - 1));
                }
            }

            // Перейти к следующему комментарию
            ++currentComment;
        }

    }
}

void checkForNestedHeaders(const QList<Header>& headersList)
{
    QRegularExpressionMatchIterator matchIterator;
    QRegularExpressionMatch match;
    QList<int> commentsInHeaderList;

    // Для каждого заголовка из контейнера headersList...
    for(QList<Header>::const_iterator currentHeader = headersList.begin(); currentHeader != headersList.end(); )
    {
        // Найти все комментарии в содержимом текущего h заголовка
        matchIterator = comment.globalMatch(currentHeader->content);
        // Для каждого найденного комментария...
        while (matchIterator.hasNext())
        {
            match = matchIterator.next();
            // Если в текущем комментарии содержится открывающий h заголовок тег...
            if(match.captured().contains(openTagHeader))
            {
                // Сохранить позицию открывающего h заголовок тега найденного комментария в контейнер commentsInHeaderList
                commentsInHeaderList.append(match.capturedStart() + match.captured().indexOf(openTagHeader));
            }
            // Если в текущем комментарии содержится закрывающий h заголовок тег...
            if(match.captured().contains(closeTagHeader))
            {
                // Сохранить позицию закрывающего h заголовок тега найденного комментария в контейнер commentsInHeaderList
                commentsInHeaderList.append(match.capturedStart() + match.captured().indexOf(closeTagHeader) + 4);
            }
        }

        // Найти в содержимом текущего заголовка корректно заданный h заголовок
        matchIterator = correctHeader.globalMatch(currentHeader->content);
        // Для каждого найденного корректно заданного h заголовка...
        while (matchIterator.hasNext())
        {
            match = matchIterator.next();
            // Если в контейнере с комментариями содержится позиция какого-либо тега найденного заголовка...
            if (!commentsInHeaderList.contains(match.capturedStart()) && !commentsInHeaderList.contains(match.capturedEnd() - 1))
            {
                // Выкинуть ошибку: "В заголовке: '#' имеется вложенный заголовок '#'"
                throw QString("Для заголовка '" + currentHeader->rawData + "', который начинается с позиции '" + QString::number(currentHeader->startPos + 1) + "', имеется вложенный заголовок '" + match.captured() + "'");
            }
        }

        // Очистить содержимое контейнера commentsInHeaderList
        commentsInHeaderList.clear();

        // Перейти к следующему заголовку в контейнере headersList
        ++currentHeader;
    }
}

void findHeaders (const QString& htmlCode, QList<Header>& headersList)
{
    QList<int> closeTagHeadersPos;
    QList<int> openTagHeadersPos;
    QList<Comment> commentsList;

    // Найти все комментарии в HTML-коде...
    findAllComments(htmlCode, commentsList);
    // Найти корректно заданные h заголовки в HTML-коде...
    findCorrectHeaders(htmlCode, headersList);
    // Найти h заголовки в HTML-коде, для которых отсутствует закрывающий тег...
    findSeperateOpenTagHeaders(htmlCode, headersList, openTagHeadersPos);
    // Найти h заголовки в HTML-коде, для которых отсутствует открывающий тег...
    findSeperateCloseTagHeaders(htmlCode, headersList, closeTagHeadersPos);
    // Удалить закомментированные корректно заданные h заголовки из контейнера с найденными h заголовками...
    getRidOfCommentedCorrectHeaders(commentsList, headersList);
    // Проверить найденные корректно заданные h заголовки на вложенность в них других корректно заданных h заголовков...
    checkForNestedHeaders(headersList);
    // Удалить закомментированные h заголовки, для которых отсутствует закрывающий их тег, из контейнера openTagHeadersPos...
    getRidOfCommentedHeadersWithoutClosingTag(commentsList, openTagHeadersPos);
    // Удалить закомментированные h заголовки, для которых отсутствует открывающий их тег, из контейнера closeTagHeadersPos...
    getRidOfCommentedHeadersWithoutOpeningTag(commentsList, closeTagHeadersPos);

    // Если был найден хотя бы один h заголовок, без закрывающего его тега...
    if(openTagHeadersPos.count() > 0)
    {
        // Выкинуть ошибку: "Для заголовка, который начинается на позиции '#', отсутствует закрывающий тег"
        throw QString("Для заголовка, который начинается на позиции '" + QString::number(openTagHeadersPos.at(0) + 1) + "', отсутствует закрывающий тег");
    }

    // Если был найден хотя бы один h заголовок, без открывающего его тега...
    if(closeTagHeadersPos.count() > 0)
    {
        // Выкинуть ошибку: "Для заголовка, который заканчивается на позиции '#', отсутствует открывающий тег"
        throw QString("Для заголовка, который заканчивается на позиции '" + QString::number(closeTagHeadersPos.at(0) + 1) + "', отсутствует открывающий тег");
    }
}
