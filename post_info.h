#ifndef POST_INFO_H
#define POST_INFO_H

#include <QObject>
#include <QString>
#include <QList>
#include <QJsonArray>
#include "comment.h"



class Post_info : public QObject
{
    Q_OBJECT
public:
    explicit Post_info(QObject *parent = nullptr);
    int id;
    QString nick;
    QString title;
    QString contents;
    QList<comment> *comments;
    void initPost(int id,QString nick,QString title, QString contents,QJsonArray cmtArr);

signals:
};

#endif // POST_INFO_H
