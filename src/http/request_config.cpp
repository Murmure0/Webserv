#include "request_config.hpp"

request_config::request_config()
{
    _methode = "";
    _url = "";
    _host = "";
    _port = 0;
    _content_lenght = 0;

}

request_config::~request_config()
{
}


void request_config::set_methode(std::string meth)
{
    _methode = meth;
   // std::cout << "||Methode is : " << _methode << "||" <<std::endl;
}


void request_config::set_url(std::string url)
{
    _url = url; 
   // std::cout << "||URL is : " << _url << "||" <<std::endl;
}

void request_config::set_host(std::string host)
{
    _host = host;
   //std::cout << "||host is : " << _host << "||" <<std::endl;
}

void request_config::set_port(size_t port)
{
    _port = port;
   // std::cout << "||port is : " << _port << "||" <<std::endl;
}

void request_config::set_content_lenght(size_t content_lgt)
{
    _content_lenght = content_lgt;
   // std::cout << "||Content lenght is : " << _content_lenght << "||" <<std::endl;
}