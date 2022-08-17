#include "../../includes/webserv.hpp"
#ifndef REQUEST_CONFIG
#define REQUEST_CONFIG


class request_config
{
    public:
    request_config();
    ~request_config();
    request_config(request_config const &copy);
    request_config &operator=(request_config const &rhs);

    void set_methode(std::string meth);
    void set_url(std::string url);
    void set_transfert_encoding(std::string trf);
    void set_v_http(std::string http);
    void set_content_length(size_t content_lgt);

    std::string get_methode(void) const;
    std::string get_url(void) const;
    std::string get_transfert_encoding(void) const;
    std::string get_v_http(void) const;
    size_t get_content_length(void) const;

    private:
    std::string _methode; //methode implementee ? permise a cet endroit ?
    std::string _url; //check si c'est trop long ? quelle limite ?
    std::string _transfer_encoding;
    std::string _v_http;
    size_t      _content_length; //ds le cas d'un requete POST : doit etre present & ne doit pas etre + grand que precisé dans le fichier de config
    std::string _transfert_encoding;

    
};

#endif
