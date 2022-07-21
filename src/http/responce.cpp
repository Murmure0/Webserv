

#include "responce.hpp"

responce::responce(void)
{
}

responce::~responce(void)
{
}

responce::responce(responce const &to_copy) : _mime(to_copy._mime), _config(to_copy._config), _current_mime(to_copy._current_mime) {}

responce &responce::operator=(responce const &rhs)
{
	this->_mime = rhs._mime;
	this->_config = rhs._config;
	this->_current_mime = rhs._current_mime;
	return *this;
}
