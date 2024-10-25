#include "jsonparsing.h"

JsonParsing::JsonParsing(QObject *parent)
    : QObject{parent}
{}

Post_info *JsonParsing::parsePost(const QByteArray &data)
{
    // 1. QByteArray 데이터를 QJsonDocument로 변환
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

    // 2. JSON이 유효한지 확인
    if (!jsonDoc.isNull() && jsonDoc.isObject()) {
        // 3. QJsonDocument에서 QJsonObject를 추출
        QJsonObject jsonObj = jsonDoc.object();

        // 4. 개별 필드 접근
        QJsonArray filesArray = jsonObj["files"].toArray();
        int id = jsonObj["id"].toInt();
        QString nick = jsonObj["nick"].toString();
        QString text = jsonObj["text"].toString();
        QString title = jsonObj["title"].toString();
        QString rtime = jsonObj["time"].toString();
        QJsonArray commentsArray = jsonObj["comments"].toArray();
        Post_info *postInfo = new Post_info;
        // 5. "comments" 배열을 파싱
        std::vector<QString> fileNames;
        for (const QJsonValue &value : filesArray) {
            fileNames.push_back(value.toString());
        }

        if (jsonObj.contains("comments") && jsonObj["comments"].isArray()) {
            postInfo->comments = new QList<comment>;
            for (int i = 0; i < commentsArray.size(); ++i) {
                QJsonObject commentObj = commentsArray[i].toObject();
                QString commentNick = commentObj["nick"].toString();
                QString commentText = commentObj["text"].toString();

                struct comment cmt;
                cmt.nick = commentNick;
                cmt.contents = commentText;
                cmt.idx = i;
                postInfo->comments->append(cmt);
            }
        }
        postInfo->initPost(fileNames, id, nick, title, text, rtime);
        return postInfo;

    } else {
        qDebug() << "Invalid JSON data-1";
        return nullptr;
    }
}

Info JsonParsing::parseCliInfo(const QByteArray &data)
{
    // 1. QByteArray 데이터를 QJsonDocument로 변환
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

    // Info 구조체를 기본 값으로 초기화
    Info parseInfo = {"", "", "", "", 0};

    // 2. JSON이 유효한지 확인
    if (!jsonDoc.isNull() && jsonDoc.isObject()) {
        // 3. QJsonDocument에서 QJsonObject를 추출
        QJsonObject jsonObj = jsonDoc.object();

        // 4. 개별 필드 접근
        parseInfo.MemberId = jsonObj["id"].toString();
        parseInfo.MemberName = jsonObj["name"].toString();
        parseInfo.MemberNickName = jsonObj["nick"].toString();
        parseInfo.MemberPw = jsonObj["pw"].toString();
        parseInfo.rank = jsonObj["rank"].toInt();
    } else {
        qDebug() << "Invalid JSON data-2";
    }

    return parseInfo; // 초기화된 Info 구조체를 반환
}
