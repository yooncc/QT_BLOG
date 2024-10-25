#include "post_info.h"

Post_info::Post_info(QObject *parent)
    : QObject{parent}
{}

void Post_info::initPost(std::vector<QString> fileNames,
                         int id,
                         QString nick,
                         QString title,
                         QString contents,
                         QString rtime)
{
    this->fileNames = fileNames;
    this->id = id;
    this->nick = nick;
    this->title = title;
    this->contents = contents;
    this->rtime = rtime;
}
