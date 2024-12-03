#include"../third_party/httplib.h"

std::string g_str;
std::mutex g_mutex;

void on_hello(const httplib::Request& req, httplib::Response& res)
{
    //使用互斥锁实现写保护
    g_mutex.lock();
    g_str = req.body;
    std::cout << "Hello From Client!" << std::endl;
    res.set_content("Hello From Server!", "text/plain");
    g_mutex.unlock();
}

int main(int argc, const char* argv[])
{
    httplib::Server server;
    //使用匿名函数的写法
    /*server.Post("/hello", [&](const httplib::Request& req, httplib::Response& res)
        {
            std::cout << "Hello From Client!" << std::endl;
            res.set_content("Hello From Server!", "text/plain");
        });*/
    server.Post("/hello", on_hello);
    server.listen("localhost", 25565);
    return 0;
}