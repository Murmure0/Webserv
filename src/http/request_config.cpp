#include "request_config.hpp"

request_config::request_config()
{
    _methode = "";
    _url = "";
    _content_length = -1;
}

request_config::~request_config()
{
}


void request_config::set_methode(std::string meth)
{
    _methode = meth;
   //std::cout << "||Methode is : " << _methode << "||" <<std::endl;
}


void request_config::set_url(std::string url)
{
    _url = url; 
   std::cout << "||URL is : " << _url << "||" <<std::endl;
}

void request_config::set_v_http(std::string http)
{
    _v_http = http; 
   //std::cout << "||http is : " << _url << "||" <<std::endl;
}

void request_config::set_content_length(size_t content_lgt)
{
    _content_length = content_lgt;
    //std::cout << "||Content lenght is : " << _content_length << "||" <<std::endl;
}


std::string request_config::get_methode(void) const {
    return this->_methode;
}

std::string request_config::get_url(void) const{
    return this->_url;
}

std::string request_config::get_v_http(void) const{
    return this->_v_http;
}

size_t request_config::get_content_length(void) const{
    return this->_content_length;
}

