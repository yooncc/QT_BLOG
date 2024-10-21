#ifndef JSONPARSING_H
#define JSONPARSING_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include "clieninfo.h"
#include "post_info.h"

class JsonParsing : public QObject
{
    Q_OBJECT
public:
    explicit JsonParsing(QObject *parent = nullptr);
    Post_info *parsePost(const QByteArray &data);
    Info parseCliInfo(const QByteArray &data);

signals:
};

#endif // JSONPARSING_H
