#ifndef JSONPARSING_H
#define JSONPARSING_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "post_info.h"
#include "clieninfo.h"

class JsonParsing : public QObject
{
    Q_OBJECT
public:
    explicit JsonParsing(QObject *parent = nullptr);
    Post_info* parsePost(const QByteArray& data);
    Info parseCliInfo(const QByteArray& data);

signals:
};

#endif // JSONPARSING_H
