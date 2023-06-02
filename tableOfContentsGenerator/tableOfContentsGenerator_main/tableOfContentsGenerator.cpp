#include "tableOfContentsGenerator.h"

dataType defineInputDataType (const int& argsCounter, char* inputArgs[])
{
    // Если с запуском программы не был передан аргумент c входными данными...
    if (argsCounter == 1)
    {
        // Выбросить исключение с ошибкой: "Отсутствует аргумент с входными данными"
        throw QString("Отсутствует аргумент с входными данными");
    }

    // Если с запуском программы было передано неверное количество аргументов (больше 2)...
    if (argsCounter > 2)
    {
        // Выбросить исключение с ошибкой: "Неверное количество переданных аргументов (больше 2)"
        throw QString("Неверное количество переданных аргументов (больше 2)");
    }

    QString inputPath = inputArgs[1];
    // Если второй аргумент, переданный с запуском программы, начинается не с начала строки...
    if (inputPath.at(0).isSpace())
    {
        // Выбросить ошибку: "Аргумент, переданный с запуском программы, содержит недопустимые пробелы в начале".
        throw QString("Аргумент, переданный с запуском программы, содержит недопустимые пробелы в начале");
    }

    // Если второй аргумент, переданный с запуском программы, содержит корректно заданный протокол URL-адреса...
    if (inputPath.startsWith("http://") || inputPath.startsWith("https://"))
    {
        // В качестве результата выполнения функции вернуть значение URL_TYPE
        return URL_TYPE;
    }

    // Если второй аргумент, переданный с запуском программы, содержит неверный протокол URL-адреса...
    if(inputPath.contains("://"))
    {
        // Выкинуть ошибку: "Неподдерживаемый  протокол URL-адреса (должен быть 'http://' или 'https://'): '#'"
        throw QString("Неподдерживаемый  протокол URL-адреса (должен быть 'http://' или 'https://'): " + inputPath);
    }

    QFileInfo file(inputPath);
    // Если файл по заданному пути, хранящемуся во втором аргументе, переданном с запуском программы, существует...
    if(file.exists())
    {
        // Если формат входного файла ".html"...
        QString fileFormat = file.suffix();
        if(fileFormat == "html")
        {
            // В качестве результата выполнения функции вернуть значение FILE_TYPE
            return FILE_TYPE;
        }
        // Иначе выбросить исключение с ошибкой: "Формат входного файла по пути '#' не соответствует требованиям ПО (должен быть 'html')".
        else
        {
            throw QString("Формат входного файла по пути '" + inputPath + "' не соответствует требованиям ПО (должен быть 'html')");
        }
    }
    // Иначе выбросить исключение с ошибкой: "По пути '#' нет заданного файла"...
    else
    {
        throw QString("По пути '" + inputPath + "' нет заданного файла");
    }
}

bool isListEmpty (const QList<Header>& headersList)
{
    // Если количество элементов в контейнере больше 0...
    if(headersList.count() > 0)
    {
        // Вернуть значение функции, которое означает, что контейнер не пустой
        return false;
    }
    // Вернуть значение функции, которое означает, что контейнер пустой
    return true;
}

void generateTableOfContents (const QList<Header>& headersList, QString& tableOfContents)
{
    // Считать, что уровень предыдущего заголовка неизвестен
    int prevLevel = 0;

    // Для всех найденных h заголовков...
    for(const auto& currentHeader: headersList)
    {
        // Пока уровень текущего заголовка меньше, чем уровень предыдущего заголовка...
        while (currentHeader.level < prevLevel) {
            // Добавить закрывающий список тег в оглавление
            tableOfContents.append("</ul>\n");
            // Уменьшить уровень предыдущего заголовка
            prevLevel--;
        }

        // Пока уровень текущего заголовка больше, чем уровень предыдущего заголовка...
        while (currentHeader.level > prevLevel) {
            // Добавить открывающий список тег в оглавление
            tableOfContents.append("<ul>\n");
            // Увеличить уровень предыдущего заголовка
            prevLevel++;
        }

        // Добавить содержимое текущего заголовка в список в таком виде, в каком оно есть
        tableOfContents += "<li>" + currentHeader.content + "</li>\n";
    }

    // Пока имеются незакрытые списки...
    while (prevLevel > 0) {
        // Добавить закрывающий список тег в оглавление
        tableOfContents.append("</ul>\n");
        // Уменьшить уровень предыдущего заголовка
        prevLevel--;
    }
}

void saveDataToFile (const QString& outputData)
{
    QString outputPath = "./Result/result.html";
    QFile outputFile(outputPath);
    // Если папки "Result" по пути "./" не существует...
    QDir outputDir = QFileInfo(outputPath).dir();
    if(!outputDir.exists())
    {
        // Если создать папку не удалось...
        if(!outputDir.mkpath(outputDir.absolutePath()))
        {
            // Выкинуть исключение: "Не удалось создать папку 'Result' по пути './' (возможно, недостаточно прав)"
            throw QString("Не удалось создать папку 'Result' по пути './' (возможно, недостаточно прав)");
        }
    }

    // Если не удалось получить доступ к файлу 'result.html'...
    if(!outputFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        // Выкинуть исключение: "Отсутствует доступ к файлу 'result.html', по пути 'ПОЛНЫЙ ПУТЬ К ФАЙЛУ'"
        throw QString("Отсутствует доступ к файлу 'result.html', по пути '" + outputFile.fileName());
    }

    // Сохранить данные в файл
    QTextStream out(&outputFile);
    out << outputData;

    // Закрыть доступ к файлу
    outputFile.close();

}

void readInputDataFromFile (const QString& inputPath, QString& inputData)
{
    QFile file(inputPath);

    // Если получить доступ к файлу по пути inputPath не удалось...
    if (!file.open(QIODevice::ReadOnly))
    {
        // Выкинуть ошибку: "Отсутствует доступ к файлу '#' (возможно, недостаточно прав)."
        throw QString("Отсутствует доступ к файлу '" + inputPath + "' (возможно, недостаточно прав).");
    }

    // Считать данные из файла в inputData
    QByteArray data = file.readAll();
    inputData = QString::fromUtf8(data).simplified();

    // Закрыть доступ к файлу
    file.close();
}

void uploadHtmlCodeByUrl (const QString& url, QString& inputData)
{
    QNetworkAccessManager manager;

    // Отправить запрос на сайт
    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(url)));

    // Ожидание завершения запроса
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    // Если сайт вернул ответ...
    if (reply->error() == QNetworkReply::NoError)
    {
        // Выгрузить HTML-код страницы в inputData
        inputData = reply->readAll().simplified();
    }
    // Иначе выкинуть ошибку: "Ошибка загрузки страницы '#'"
    else
    {
        throw QString("Ошибка загрузки страницы '" + reply->errorString() + "'");
    }

    // Освободить ресурсы
    reply->deleteLater();
}
