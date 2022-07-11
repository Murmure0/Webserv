

#include "webserv.hpp"

webserv::webserv(void)
{
}

webserv::~webserv(void)
{
	servers.clear();
}

webserv::webserv(webserv const &to_copy) {}

webserv &webserv::operator=(webserv const &rhs)
{
	return *this;
}

void webserv::print(void) const
{
	for (std::map<std::string, server>::const_iterator i = servers.begin(); i != servers.end(); i++)
	{
		(*i).second.print();
	}
}

void webserv::config(std::string config_file)
{
	std::string s = file_to_string(config_file);
	t_config m_c;
	t_config s_c;
	t_config l_c;

	bool m_i = true;
	bool s_i = true;
	bool l_i = true;

	while (!m_c.key.empty() || m_i)
	{
		m_i = false;
		m_c = get_next_variable(s);
		if (m_c.key == "server")
		{
			std::pair<std::string, server> pair;
			while (!s_c.key.empty() || s_i)
			{
				s_i = false;
				s_c = get_next_variable(m_c.value);

				if (s_c.key == "location")
				{
					while (!l_c.key.empty() || l_i)
					{
						l_i = false;
						l_c = get_next_variable(s_c.value);

						if (s_c.value.length() > l_c.next_start)
							s_c.value = s_c.value.substr(l_c.next_start);
						else
							break;
					}
				}
				else
				{
					pair.second.set(s_c.key, s_c.value);
				}
				if (m_c.value.length() > s_c.next_start)
					m_c.value = m_c.value.substr(s_c.next_start);
				else
					break;
			}
			servers.insert(pair);
		}
		if (s.length() > m_c.next_start)
			s = s.substr(m_c.next_start);
		else
			break;
	}
}
