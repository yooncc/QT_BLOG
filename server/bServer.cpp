#include <iostream>
#include <sys/types.h> // socket
#include <sys/socket.h> // socket
#include <netinet/in.h> // sockaddr_in
#include <string.h> // memset
#include <fcntl.h> // fcntl
#include <unistd.h> // close
#include <vector>
#include <pthread.h>
#include <fstream> // file
#include <nlohmann/json.hpp> // json

#define TCP_PORT 8001

using json = nlohmann::json;

class Server
{
private:
    int ssock, csock;
    socklen_t clen;
    struct sockaddr_in servaddr, cliaddr;
    std::vector<int> csocks;
    pthread_t st;
    pthread_rwlock_t userlock;
    pthread_rwlock_t postlock;
    int post_num;

public:
    Server(int port = 8001);
    ~Server();
    // server
    int mkSock();
    void mkThread();
    // tool
    void buftok(char*, int, std::vector<std::string> &);
    json readj(int);
    std::ofstream writej(int);
    void wclosej(int, std::ofstream &);
    int check(int);
    int check(int, std::string);
    // main func
    void mySend(int, std::string);
    int login(std::string, std::string);
    int signUp(std::string, std::string, std::string, std::string);
    int createP(std::string, std::string, std::string);
    int modifyP(std::string, std::string, std::string);
    int deleteP(std::string);
    int createC(std::string, std::string, std::string);
    int modifyC(std::string, std::string, std::string);
    int deleteC(std::string, std::string);
    void resign(int);

};

void* start(void* fdp);

static Server bServer;

int main()
{
    
    if (-1 == bServer.mkSock())
        exit(1);
    
    while (1)
    {
        bServer.mkThread();
    }
    
    return 0;
}

Server::Server(int port): ssock(0), csock(0), clen(0), post_num(1)
{
    // wrlock
    pthread_rwlock_init(&userlock, NULL);
    pthread_rwlock_init(&postlock, NULL);

    // for server
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(TCP_PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
}

Server::~Server()
{
    pthread_rwlock_destroy(&userlock);
    pthread_rwlock_destroy(&postlock);

    for (auto x: csocks)
        close(x);
    close(ssock);
}

int Server::mkSock()
{
    ssock = socket(AF_INET, SOCK_STREAM, 0);
    if (ssock == -1)
    {
        perror("socket()");
        return -1;
    }

    // 포트 중복 문제 해결
    int on = 1;
    if (setsockopt(ssock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
    {
        perror("setsockopt()");
        return -1;
    }

    // 서버 소켓은 non-blocking으로 설정
    // int flag = fcntl(ssock, F_GETFL, 0);
    // fcntl(ssock, F_SETFL, flag | O_NONBLOCK);

    if (bind(ssock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind()");
        return -1;
    }

    if (listen(ssock, 10) < 0)
    {
        perror("listen()");
        return -1;
    }

    return 0;
}

void Server::mkThread()
{
    csock = accept(ssock, (struct sockaddr*)&cliaddr, &clen);
    if (csock != -1)
    {
        csocks.push_back(csock);
        // 스레드 생성
        pthread_create(&st, NULL, start, (void*)&csock);
        pthread_detach(st);
    }
}

void Server::buftok(char* buf, int count, std::vector<std::string> &tokens)
{
    if (count < 0)
        return;
        
    // 1:id:pw
    strtok(buf, ":"); // 맨 앞의 숫자 버리기

    for (int i = 0; i < count; i++)
    {
        char* temp = new char[BUFSIZ];
        strcpy(temp, strtok(NULL, ":"));
        std::string stemp(temp);
        tokens.push_back(stemp);
        delete[] temp;
    }
}

// 1:userdata, 2:postdata
json Server::readj(int select)
{
    json jf;
    switch (select)
    {
        case 1:
        {
            pthread_rwlock_rdlock(&userlock);
            std::ifstream rf("./userdata.json");
            rf >> jf;
            rf.close();
            pthread_rwlock_unlock(&userlock);
            break;
        }

        case 2:
        {
            pthread_rwlock_rdlock(&postlock);
            std::ifstream rf("./postdata.json");
            rf >> jf;
            rf.close();
            pthread_rwlock_unlock(&postlock);
            break;
        }
    }

    return jf;
}

// 1:userdata, 2:postdata
std::ofstream Server::writej(int select)
{
    std::ofstream rf;
    switch (select)
    {
        case 1:
        {
            pthread_rwlock_wrlock(&userlock);
            rf.open("./userdata.json");
            break;
        }

        case 2:
        {
            pthread_rwlock_wrlock(&postlock);
            rf.open("./postdata.json");
            break;
        }
    }

    return rf;
}

void Server::wclosej(int select, std::ofstream &file)
{
    switch (select)
    {
        case 1:
        {
            file.close();
            pthread_rwlock_unlock(&userlock);
            break;
        }

        case 2:
        {
            file.close();
            pthread_rwlock_unlock(&postlock);
            break;
        }
    }
}

int Server::check(int value)
{
    int idx = 0;
    json jf = readj(2);
    for (auto x: jf["posts"])
    {
        if (x["id"] == value)
            return idx;
        idx += 1;
    }
    return -1;
}

// 1:id, 2:nick
int Server::check(int select, std::string value)
{
    int idx = 0;
    json jf = readj(1);
    for (auto x: jf["users"])
    {
        switch (select)
        {
            case 1:
            {
                if (x["id"] == value)
                    return idx;
                break;
            }

            case 2:
            {
                if (x["nick"] == value)
                    return idx;
                break;
            }
        }
        idx += 1;
    }
    return -1;
}

void Server::mySend(int fd, std::string text)
{
    send(fd, text.c_str(), text.length(), 0);
}

int Server::login(std::string id, std::string pw)
{
    int id_flag = 0, pw_flag = 0;
    json jf = readj(1);

    int idx = check(1, id);
    if (idx != -1)
    {
        id_flag = 1;
        if (jf["users"][idx]["pw"] == pw)
        {
            pw_flag = 1;
        }
    }

    if (id_flag == 0)
        return -1;
    else if (pw_flag == 0)
        return -2;
        
    return idx;
}

int Server::signUp(std::string id, std::string name, std::string nick, std::string pw)
{
    json jf = readj(1);
    jf["users"].push_back(json::object({ {"id", id}, {"name", name}, {"nick", nick}, {"pw", pw}, {"rank", 2} }));

    int fnum = 1;
    std::ofstream temp = writej(fnum);
    temp << jf.dump(4);
    wclosej(fnum, temp);
    
    return 1;
}

int Server::createP(std::string title, std::string nick, std::string text)
{
    json jf = readj(2);
    jf["posts"].push_back(json::object({ {"id", post_num}, {"title", title}, {"nick", nick}, {"text", text}}));
    jf["posts"][post_num]["comments"] = json::array();

    int fnum = 2;
    std::ofstream temp = writej(fnum);
    temp << jf.dump(4);
    wclosej(fnum, temp);

    post_num += 1;

    return jf["posts"][post_num - 1]["id"].template get<int>();
}

int Server::modifyP(std::string id, std::string title, std::string text)
{
    int idx = check(std::stoi(id));
    if (idx == -1)
        return 0;

    json jf = readj(2);
    jf["posts"][idx]["title"] = title;
    jf["posts"][idx]["text"] = text;

    int fnum = 2;
    std::ofstream temp = writej(fnum);
    temp << jf.dump(4);
    wclosej(fnum, temp);

    return 1;
}

int Server::deleteP(std::string id)
{
    int idx = check(std::stoi(id));
    if (idx == -1)
        return 0;

    json jf = readj(2);
    jf["posts"].erase(idx);

    int fnum = 2;
    std::ofstream temp = writej(fnum);
    temp << jf.dump(4);
    wclosej(fnum, temp);

    return 1;
}

int Server::createC(std::string id, std::string nick, std::string text)
{
    int idx = check(std::stoi(id));
    if (idx == -1)
        return 0;

    json jf = readj(2);
    auto comment = json::object({ {"nick", nick}, {"text", text} });
    jf["posts"][idx]["comments"].push_back(comment);

    int fnum = 2;
    std::ofstream temp = writej(fnum);
    temp << jf.dump(4);
    wclosej(fnum, temp);

    return 1;
}

int Server::modifyC(std::string id, std::string index, std::string text)
{
    int idx = check(std::stoi(id));
    if (idx == -1)
        return 0;

    json jf = readj(2);
    jf["posts"][idx]["comments"][std::stoi(index)]["text"] = text;

    int fnum = 2;
    std::ofstream temp = writej(fnum);
    temp << jf.dump(4);
    wclosej(fnum, temp);

    return 1;
}

int Server::deleteC(std::string id, std::string index)
{
    int idx = check(std::stoi(id));
    if (idx == -1)
        return 0;

    json jf = readj(2);
    jf["posts"][idx]["comments"].erase(std::stoi(index));

    int fnum = 2;
    std::ofstream temp = writej(fnum);
    temp << jf.dump(4);
    wclosej(fnum, temp);

    return 1;
}

void Server::resign(int idx)
{
    json jf = readj(1);
    jf["users"].erase(idx);

    int fnum = 1;
    std::ofstream temp = writej(fnum);
    temp << jf.dump(4);
    wclosej(fnum, temp);
}

void* start(void* fdp)
{
    char buf[100];
    int fd = *(int*)fdp;

    while (1)
    {
        memset(buf, 0, sizeof(buf));
        if (recv(fd, buf, sizeof(buf), 0) <= 0)
            continue;

        std::string bflag(buf);
        bflag = bflag.substr(0, bflag.find(':'));
        int flag = std::stoi(bflag);
        std::cout << flag << "\n";

        switch (flag)
        {
            case 1:
            {
                // buf = 1:id:pw
                std::vector<std::string> tokens;
                bServer.buftok(buf, 2, tokens);
                int result = bServer.login(tokens[0], tokens[1]);

                if (result >= 0) // 로그인 성공
                {
                    json jf = bServer.readj(1);
                    bServer.mySend(fd, to_string(jf["users"][result]));
                }
                else if (result == -1) // 아이디 틀림
                    bServer.mySend(fd, "-1");
                else if (result == -2) // 비밀번호 틀림
                    bServer.mySend(fd, "-2");
                break;
            }

            case 2:
            {
                // buf = 2:id:name:nick:pw
                std::vector<std::string> tokens;
                bServer.buftok(buf, 4, tokens);
                
                if (bServer.check(1, tokens[0]) != -1 || bServer.check(2, tokens[2]) != -1)
                {
                    bServer.mySend(fd, "0");
                    break;
                }

                if (bServer.signUp(tokens[0], tokens[1], tokens[2], tokens[3]))
                    bServer.mySend(fd, "1");
                break;
            }

            case 3:
            {
                // buf = 3
                json jf = bServer.readj(2);
                for (auto x: jf["posts"])
                {
                    bServer.mySend(fd, to_string(x));
                }
                bServer.mySend(fd, "1");
                break;
            }

            case 4:
            {
                // buf = 4:id
                std::vector<std::string> tokens;
                bServer.buftok(buf, 1, tokens);

                int idx = bServer.check(std::stoi(tokens[0]));
                if (idx != -1)
                {
                    json jf = bServer.readj(2);
                    bServer.mySend(fd, to_string(jf["posts"][idx]));
                }
                else
                    bServer.mySend(fd, "0");
                break;
            }

            case 5:
            {
                // buf = 5:title:nick:text
                std::vector<std::string> tokens;
                bServer.buftok(buf, 3, tokens);
                if (int id = bServer.createP(tokens[0], tokens[1], tokens[2]))
                {   
                    std::string number = std::to_string(id);
                    bServer.mySend(fd, number);
                }
                else
                {
                    bServer.mySend(fd, "0");
                }
                break;
            }

            case 6:
            {
                // buf = 6:id:title:text
                std::vector<std::string> tokens;
                bServer.buftok(buf, 3, tokens);
                if (bServer.modifyP(tokens[0], tokens[1], tokens[2]))
                {   
                    bServer.mySend(fd, "1");
                }
                else
                {
                    bServer.mySend(fd, "0");
                }
                break;
            }

            case 7:
            {
                // buf = 7:id
                std::vector<std::string> tokens;
                bServer.buftok(buf, 1, tokens);

                if (bServer.deleteP(tokens[0]))
                {
                    bServer.mySend(fd, "1");
                }
                else
                {
                    bServer.mySend(fd, "0");
                }
                break;
            }

            case 8:
            {
                // buf = 8:id:nick:text
                std::vector<std::string> tokens;
                bServer.buftok(buf, 3, tokens);

                if (bServer.createC(tokens[0], tokens[1], tokens[2]))
                {   
                    bServer.mySend(fd, "1");
                }
                else
                {
                    bServer.mySend(fd, "0");
                }
                break;
            }

            case 9:
            {
                // buf = 9:id:index:text
                std::vector<std::string> tokens;
                bServer.buftok(buf, 3, tokens);

                if (bServer.modifyC(tokens[0], tokens[1], tokens[2]))
                {   
                    bServer.mySend(fd, "1");
                }
                else
                {
                    bServer.mySend(fd, "0");
                }
                break;
            }

            case 10:
            {
                // buf = 10:id:index
                std::vector<std::string> tokens;
                bServer.buftok(buf, 2, tokens);

                if (bServer.deleteC(tokens[0], tokens[1]))
                {   
                    bServer.mySend(fd, "1");
                }
                else
                {
                    bServer.mySend(fd, "0");
                }
                break;
            }

            case 11:
            {
                // buf = 11:id:pw
                std::vector<std::string> tokens;
                bServer.buftok(buf, 2, tokens);

                int result = bServer.login(tokens[0], tokens[1]);
                if (result >= 0)
                {
                    bServer.resign(result);
                    bServer.mySend(fd, "0");
                }
                else if (result == -1)
                    bServer.mySend(fd, "-1");
                else if (result == -2)
                    bServer.mySend(fd, "-2");
                break;
            }

            default:
            {
                return NULL;
            }
        }
    }
}

