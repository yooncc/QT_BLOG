#ifndef JSONPARSING_H
#define JSONPARSING_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "post_info.h"
#include "client.h"
struct Info {
    QString MemberId;
    QString MemberName;
    QString MemberNickName;
    QString MemberPw;
    int rank;
};
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
