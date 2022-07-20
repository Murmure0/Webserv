

#include "responce.hpp"

responce::responce(void)
{
}

responce::~responce(void)
{
}

responce::responce(responce const &to_copy) : is_image(to_copy.is_image) {}

responce &responce::operator=(responce const &rhs)
{
	this->is_image = rhs.is_image;
	return *this;
}
