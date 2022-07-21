

#include "request.hpp"

request::request(void) : _content_size(-1), _header_completed(false), _request_completed(false)
{
}

request::~request(void)
{
}

request::request(request const &to_copy) : _content_size(to_copy._content_size), _header_completed(to_copy._header_completed), _request_completed(to_copy._request_completed) {}

request &request::operator=(request const &rhs)
{
	return *this;
}
