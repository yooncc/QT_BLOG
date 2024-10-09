#include "imageloader.h"

ImageLoader::ImageLoader(QObject *parent, QLabel *imageLabel)
    : QObject{parent}
{
    this->imageLabel = imageLabel;
    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &ImageLoader::onImageDownloaded);

}


void ImageLoader::loadImage(const QUrl& url) {
    QNetworkRequest request(url);
    manager->get(request);  // 이미지 다운로드 요청
}

void ImageLoader::onImageDownloaded(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QImage image;
        image.loadFromData(reply->readAll());  // 받은 데이터로 이미지 로드
        if (!image.isNull()) {
            this->imageLabel->setPixmap(QPixmap::fromImage(image));  // QLabel에 이미지 표시
        }
    }
    reply->deleteLater();
}
