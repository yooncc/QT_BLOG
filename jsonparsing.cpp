#include "jsonparsing.h"


JsonParsing::JsonParsing(QObject *parent)
    : QObject{parent}
{}


Post_info* JsonParsing::parsePost(const QByteArray& data) {
    // 1. QByteArray 데이터를 QJsonDocument로 변환
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

    // 2. JSON이 유효한지 확인
    if (!jsonDoc.isNull() && jsonDoc.isObject()) {
        // 3. QJsonDocument에서 QJsonObject를 추출
        QJsonObject jsonObj = jsonDoc.object();

        // 4. 개별 필드 접근
        // QString id = QString::number(jsonObj["id"].toInt());
        int id = jsonObj["id"].toInt();
        QString nick = jsonObj["nick"].toString();
        QString text = jsonObj["text"].toString();
        QString title = jsonObj["title"].toString();
        QJsonArray commentsArray = jsonObj["comments"].toArray();

        qDebug() << "ID:" << id;
        qDebug() << "Nick:" << nick;
        qDebug() << "Text:" << text;
        qDebug() << "Title:" << title;

        // 5. "comments" 배열을 파싱
        if (jsonObj.contains("comments") && jsonObj["comments"].isArray()) {
            // QJsonArray commentsArray = jsonObj["comments"].toArray();
            // 배열 내 각 객체를 파싱
            for (int i = 0; i < commentsArray.size(); ++i) {
                QJsonObject commentObj = commentsArray[i].toObject();
                QString commentNick = commentObj["nick"].toString();
                QString commentText = commentObj["text"].toString();

                qDebug() << "Comment" << i << "Nick:" << commentNick;
                qDebug() << "Comment" << i << "Text:" << commentText;
            }
        }

        Post_info* postInfo = new Post_info;
        postInfo->initPost(id,nick,title,text,commentsArray);
        return postInfo;

    } else {
        qDebug() << "Invalid JSON data";
        return nullptr;
    }
}

Info JsonParsing::parseCliInfo(const QByteArray& data) {
    // 1. QByteArray 데이터를 QJsonDocument로 변환
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

    // 2. JSON이 유효한지 확인
    if (!jsonDoc.isNull() && jsonDoc.isObject()) {
        // 3. QJsonDocument에서 QJsonObject를 추출
        QJsonObject jsonObj = jsonDoc.object();

        // 4. 개별 필드 접근
        Info info;
        info.MemberId = jsonObj["id"].toString();
        info.MemberName = jsonObj["name"].toString();
        info.MemberNickName = jsonObj["nick"].toString();
        info.MemberPw = jsonObj["pw"].toString();
        info.rank = jsonObj["rank"].toInt();
        return info;
    } else {
        qDebug() << "Invalid JSON data";
        return info;
    }
}
