#ifndef POST_INFO_H
#define POST_INFO_H

#include <QJsonArray>
#include <QList>
#include <QObject>
#include <QString>
#include "comment.h"

class Post_info : public QObject
{
    Q_OBJECT
public:
    explicit Post_info(QObject *parent = nullptr);
    std::vector<QString> fileNames;
    int id;
    QString nick;
    QString title;
    QString contents;
    QString rtime;
    QList<comment> *comments;
    bool commentExist;
    void initPost(std::vector<QString> fileNames, int id, QString nick, QString title, QString contents, QString rtime);

signals:
};

#endif // POST_INFO_H
