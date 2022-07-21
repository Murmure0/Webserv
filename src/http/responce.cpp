

#include "responce.hpp"

responce::responce(void)
{
}

responce::~responce(void)
{
}

responce::responce(responce const &to_copy) : _mime(to_copy._mime), _config(to_copy._config) {}

responce &responce::operator=(responce const &rhs)
{
	this->_mime = rhs._mime;
	this->_config = rhs._config;
	return *this;
}
