#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QImage>
#include <QLabel>
#include <QObject>
#include <QPixmap>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

class ImageLoader : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager *manager;
    QLabel *imageLabel;

public:
    explicit ImageLoader(QObject *parent = nullptr, QLabel *imageLabel = nullptr);
    void loadImage(const QUrl &url);

public slots:
    void onImageDownloaded(QNetworkReply *reply);

signals:
};

#endif // IMAGELOADER_H
