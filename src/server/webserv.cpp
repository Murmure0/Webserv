

#include "webserv.hpp"

struct ext_to_mime
{
	const char *fileExtension;
	const char *mimeType;
};

const ext_to_mime ext_to_mime_array[347] = {
	{"*3gpp", "audio/3gpp"},
	{"*jpm", "video/jpm"},
	{"*mp3", "audio/mp3"},
	{"*rtf", "text/rtf"},
	{"*wav", "audio/wave"},
	{"*xml", "text/xml"},
	{"3g2", "video/3gpp2"},
	{"3gp", "video/3gpp"},
	{"3gpp", "video/3gpp"},
	{"ac", "application/pkix-attr-cert"},
	{"adp", "audio/adpcm"},
	{"ai", "application/postscript"},
	{"apng", "image/apng"},
	{"appcache", "text/cache-manifest"},
	{"asc", "application/pgp-signature"},
	{"atom", "application/atom+xml"},
	{"atomcat", "application/atomcat+xml"},
	{"atomsvc", "application/atomsvc+xml"},
	{"au", "audio/basic"},
	{"aw", "application/applixware"},
	{"bdoc", "application/bdoc"},
	{"bin", "application/octet-stream"},
	{"bmp", "image/bmp"},
	{"bpk", "application/octet-stream"},
	{"buffer", "application/octet-stream"},
	{"ccxml", "application/ccxml+xml"},
	{"cdmia", "application/cdmi-capability"},
	{"cdmic", "application/cdmi-container"},
	{"cdmid", "application/cdmi-domain"},
	{"cdmio", "application/cdmi-object"},
	{"cdmiq", "application/cdmi-queue"},
	{"cer", "application/pkix-cert"},
	{"cgm", "image/cgm"},
	{"class", "application/java-vm"},
	{"coffee", "text/coffeescript"},
	{"conf", "text/plain"},
	{"cpt", "application/mac-compactpro"},
	{"crl", "application/pkix-crl"},
	{"css", "text/css"},
	{"csv", "text/csv"},
	{"cu", "application/cu-seeme"},
	{"davmount", "application/davmount+xml"},
	{"dbk", "application/docbook+xml"},
	{"deb", "application/octet-stream"},
	{"def", "text/plain"},
	{"deploy", "application/octet-stream"},
	{"disposition-notification", "message/disposition-notification"},
	{"dist", "application/octet-stream"},
	{"distz", "application/octet-stream"},
	{"dll", "application/octet-stream"},
	{"dmg", "application/octet-stream"},
	{"dms", "application/octet-stream"},
	{"doc", "application/msword"},
	{"dot", "application/msword"},
	{"drle", "image/dicom-rle"},
	{"dssc", "application/dssc+der"},
	{"dtd", "application/xml-dtd"},
	{"dump", "application/octet-stream"},
	{"ear", "application/java-archive"},
	{"ecma", "application/ecmascript"},
	{"elc", "application/octet-stream"},
	{"emf", "image/emf"},
	{"eml", "message/rfc822"},
	{"emma", "application/emma+xml"},
	{"eps", "application/postscript"},
	{"epub", "application/epub+zip"},
	{"es", "application/ecmascript"},
	{"exe", "application/octet-stream"},
	{"exi", "application/exi"},
	{"exr", "image/aces"},
	{"ez", "application/andrew-inset"},
	{"fits", "image/fits"},
	{"g3", "image/g3fax"},
	{"gbr", "application/rpki-ghostbusters"},
	{"geojson", "application/geo+json"},
	{"gif", "image/gif"},
	{"glb", "model/gltf-binary"},
	{"gltf", "model/gltf+json"},
	{"gml", "application/gml+xml"},
	{"gpx", "application/gpx+xml"},
	{"gram", "application/srgs"},
	{"grxml", "application/srgs+xml"},
	{"gxf", "application/gxf"},
	{"gz", "application/gzip"},
	{"h261", "video/h261"},
	{"h263", "video/h263"},
	{"h264", "video/h264"},
	{"heic", "image/heic"},
	{"heics", "image/heic-sequence"},
	{"heif", "image/heif"},
	{"heifs", "image/heif-sequence"},
	{"hjson", "application/hjson"},
	{"hlp", "application/winhlp"},
	{"hqx", "application/mac-binhex40"},
	{"htm", "text/html"},
	{"html", "text/html"},
	{"ics", "text/calendar"},
	{"ief", "image/ief"},
	{"ifb", "text/calendar"},
	{"iges", "model/iges"},
	{"igs", "model/iges"},
	{"img", "application/octet-stream"},
	{"in", "text/plain"},
	{"ini", "text/plain"},
	{"ink", "application/inkml+xml"},
	{"inkml", "application/inkml+xml"},
	{"ipfix", "application/ipfix"},
	{"iso", "application/octet-stream"},
	{"jade", "text/jade"},
	{"jar", "application/java-archive"},
	{"jls", "image/jls"},
	{"jp2", "image/jp2"},
	{"jpe", "image/jpeg"},
	{"jpeg", "image/jpeg"},
	{"jpf", "image/jpx"},
	{"jpg", "image/jpeg"},
	{"jpg2", "image/jp2"},
	{"jpgm", "video/jpm"},
	{"jpgv", "video/jpeg"},
	{"jpm", "image/jpm"},
	{"jpx", "image/jpx"},
	{"js", "application/javascript"},
	{"json", "application/json"},
	{"json5", "application/json5"},
	{"jsonld", "application/ld+json"},
	{"jsonml", "application/jsonml+json"},
	{"jsx", "text/jsx"},
	{"kar", "audio/midi"},
	{"ktx", "image/ktx"},
	{"less", "text/less"},
	{"list", "text/plain"},
	{"litcoffee", "text/coffeescript"},
	{"log", "text/plain"},
	{"lostxml", "application/lost+xml"},
	{"lrf", "application/octet-stream"},
	{"m1v", "video/mpeg"},
	{"m21", "application/mp21"},
	{"m2a", "audio/mpeg"},
	{"m2v", "video/mpeg"},
	{"m3a", "audio/mpeg"},
	{"m4a", "audio/mp4"},
	{"m4p", "application/mp4"},
	{"ma", "application/mathematica"},
	{"mads", "application/mads+xml"},
	{"man", "text/troff"},
	{"manifest", "text/cache-manifest"},
	{"map", "application/json"},
	{"mar", "application/octet-stream"},
	{"markdown", "text/markdown"},
	{"mathml", "application/mathml+xml"},
	{"mb", "application/mathematica"},
	{"mbox", "application/mbox"},
	{"md", "text/markdown"},
	{"me", "text/troff"},
	{"mesh", "model/mesh"},
	{"meta4", "application/metalink4+xml"},
	{"metalink", "application/metalink+xml"},
	{"mets", "application/mets+xml"},
	{"mft", "application/rpki-manifest"},
	{"mid", "audio/midi"},
	{"midi", "audio/midi"},
	{"mime", "message/rfc822"},
	{"mj2", "video/mj2"},
	{"mjp2", "video/mj2"},
	{"mjs", "application/javascript"},
	{"mml", "text/mathml"},
	{"mods", "application/mods+xml"},
	{"mov", "video/quicktime"},
	{"mp2", "audio/mpeg"},
	{"mp21", "application/mp21"},
	{"mp2a", "audio/mpeg"},
	{"mp3", "audio/mpeg"},
	{"mp4", "video/mp4"},
	{"mp4a", "audio/mp4"},
	{"mp4s", "application/mp4"},
	{"mp4v", "video/mp4"},
	{"mpd", "application/dash+xml"},
	{"mpe", "video/mpeg"},
	{"mpeg", "video/mpeg"},
	{"mpg", "video/mpeg"},
	{"mpg4", "video/mp4"},
	{"mpga", "audio/mpeg"},
	{"mrc", "application/marc"},
	{"mrcx", "application/marcxml+xml"},
	{"ms", "text/troff"},
	{"mscml", "application/mediaservercontrol+xml"},
	{"msh", "model/mesh"},
	{"msi", "application/octet-stream"},
	{"msm", "application/octet-stream"},
	{"msp", "application/octet-stream"},
	{"mxf", "application/mxf"},
	{"mxml", "application/xv+xml"},
	{"n3", "text/n3"},
	{"nb", "application/mathematica"},
	{"oda", "application/oda"},
	{"oga", "audio/ogg"},
	{"ogg", "audio/ogg"},
	{"ogv", "video/ogg"},
	{"ogx", "application/ogg"},
	{"omdoc", "application/omdoc+xml"},
	{"onepkg", "application/onenote"},
	{"onetmp", "application/onenote"},
	{"onetoc", "application/onenote"},
	{"onetoc2", "application/onenote"},
	{"opf", "application/oebps-package+xml"},
	{"otf", "font/otf"},
	{"owl", "application/rdf+xml"},
	{"oxps", "application/oxps"},
	{"p10", "application/pkcs10"},
	{"p7c", "application/pkcs7-mime"},
	{"p7m", "application/pkcs7-mime"},
	{"p7s", "application/pkcs7-signature"},
	{"p8", "application/pkcs8"},
	{"pdf", "application/pdf"},
	{"pfr", "application/font-tdpfr"},
	{"pgp", "application/pgp-encrypted"},
	{"pkg", "application/octet-stream"},
	{"pki", "application/pkixcmp"},
	{"pkipath", "application/pkix-pkipath"},
	{"pls", "application/pls+xml"},
	{"png", "image/png"},
	{"prf", "application/pics-rules"},
	{"ps", "application/postscript"},
	{"pskcxml", "application/pskc+xml"},
	{"qt", "video/quicktime"},
	{"raml", "application/raml+yaml"},
	{"rdf", "application/rdf+xml"},
	{"rif", "application/reginfo+xml"},
	{"rl", "application/resource-lists+xml"},
	{"rld", "application/resource-lists-diff+xml"},
	{"rmi", "audio/midi"},
	{"rnc", "application/relax-ng-compact-syntax"},
	{"rng", "application/xml"},
	{"roa", "application/rpki-roa"},
	{"roff", "text/troff"},
	{"rq", "application/sparql-query"},
	{"rs", "application/rls-services+xml"},
	{"rsd", "application/rsd+xml"},
	{"rss", "application/rss+xml"},
	{"rtf", "application/rtf"},
	{"rtx", "text/richtext"},
	{"s3m", "audio/s3m"},
	{"sbml", "application/sbml+xml"},
	{"scq", "application/scvp-cv-request"},
	{"scs", "application/scvp-cv-response"},
	{"sdp", "application/sdp"},
	{"ser", "application/java-serialized-object"},
	{"setpay", "application/set-payment-initiation"},
	{"setreg", "application/set-registration-initiation"},
	{"sgi", "image/sgi"},
	{"sgm", "text/sgml"},
	{"sgml", "text/sgml"},
	{"shex", "text/shex"},
	{"shf", "application/shf+xml"},
	{"shtml", "text/html"},
	{"sig", "application/pgp-signature"},
	{"sil", "audio/silk"},
	{"silo", "model/mesh"},
	{"slim", "text/slim"},
	{"slm", "text/slim"},
	{"smi", "application/smil+xml"},
	{"smil", "application/smil+xml"},
	{"snd", "audio/basic"},
	{"so", "application/octet-stream"},
	{"spp", "application/scvp-vp-response"},
	{"spq", "application/scvp-vp-request"},
	{"spx", "audio/ogg"},
	{"sru", "application/sru+xml"},
	{"srx", "application/sparql-results+xml"},
	{"ssdl", "application/ssdl+xml"},
	{"ssml", "application/ssml+xml"},
	{"stk", "application/hyperstudio"},
	{"styl", "text/stylus"},
	{"stylus", "text/stylus"},
	{"svg", "image/svg+xml"},
	{"svgz", "image/svg+xml"},
	{"t", "text/troff"},
	{"t38", "image/t38"},
	{"tei", "application/tei+xml"},
	{"teicorpus", "application/tei+xml"},
	{"text", "text/plain"},
	{"tfi", "application/thraud+xml"},
	{"tfx", "image/tiff-fx"},
	{"tif", "image/tiff"},
	{"tiff", "image/tiff"},
	{"tr", "text/troff"},
	{"ts", "video/mp2t"},
	{"tsd", "application/timestamped-data"},
	{"tsv", "text/tab-separated-values"},
	{"ttc", "font/collection"},
	{"ttf", "font/ttf"},
	{"ttl", "text/turtle"},
	{"txt", "text/plain"},
	{"u8dsn", "message/global-delivery-status"},
	{"u8hdr", "message/global-headers"},
	{"u8mdn", "message/global-disposition-notification"},
	{"u8msg", "message/global"},
	{"uri", "text/uri-list"},
	{"uris", "text/uri-list"},
	{"urls", "text/uri-list"},
	{"vcard", "text/vcard"},
	{"vrml", "model/vrml"},
	{"vtt", "text/vtt"},
	{"vxml", "application/voicexml+xml"},
	{"war", "application/java-archive"},
	{"wasm", "application/wasm"},
	{"wav", "audio/wav"},
	{"weba", "audio/webm"},
	{"webm", "video/webm"},
	{"webmanifest", "application/manifest+json"},
	{"webp", "image/webp"},
	{"wgt", "application/widget"},
	{"wmf", "image/wmf"},
	{"woff", "font/woff"},
	{"woff2", "font/woff2"},
	{"wrl", "model/vrml"},
	{"wsdl", "application/wsdl+xml"},
	{"wspolicy", "application/wspolicy+xml"},
	{"x3d", "model/x3d+xml"},
	{"x3db", "model/x3d+binary"},
	{"x3dbz", "model/x3d+binary"},
	{"x3dv", "model/x3d+vrml"},
	{"x3dvz", "model/x3d+vrml"},
	{"x3dz", "model/x3d+xml"},
	{"xaml", "application/xaml+xml"},
	{"xdf", "application/xcap-diff+xml"},
	{"xdssc", "application/dssc+xml"},
	{"xenc", "application/xenc+xml"},
	{"xer", "application/patch-ops-error+xml"},
	{"xht", "application/xhtml+xml"},
	{"xhtml", "application/xhtml+xml"},
	{"xhvml", "application/xv+xml"},
	{"xm", "audio/xm"},
	{"xml", "application/xml"},
	{"xop", "application/xop+xml"},
	{"xpl", "application/xproc+xml"},
	{"xsd", "application/xml"},
	{"xsl", "application/xml"},
	{"xslt", "application/xslt+xml"},
	{"xspf", "application/xspf+xml"},
	{"xvm", "application/xv+xml"},
	{"xvml", "application/xv+xml"},
	{"yaml", "text/yaml"},
	{"yang", "application/yang"},
	{"yin", "application/yin+xml"},
	{"yml", "text/yaml"},
	{"zip", "application/zip"},
};

webserv::webserv(void)
{
	for (size_t i = 0; i < 347; i++)
	{
		mime[ext_to_mime_array[i].fileExtension] = ext_to_mime_array[i].mimeType;
	}
}

webserv::~webserv(void)
{
	close_sockets();
	servers.clear();
	mime.clear();
}

webserv::webserv(webserv const &to_copy)
{
	(void)to_copy;
	// this->servers = to_copy.servers;
	// this->servers_name_to_server = to_copy.servers_name_to_server;
	// this->_listen_sockets = to_copy._listen_sockets;
	// this->mime = to_copy.mime;
}

webserv &webserv::operator=(webserv const &rhs)
{
	(void)rhs;
	return *this;
}

void webserv::print(void) const
{
	for (std::map<std::string, server>::const_iterator i = servers.begin(); i != servers.end(); i++)
	{
		std::cout << (*i).first << std::endl;
		(*i).second.print();
	}
}

void webserv::config(std::string config_file)
{
	std::string s = file_to_string(config_file);
	std::map<int, int> port_count;
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
					std::pair<std::string, location> l_pair;
					l_pair.first = s_c.before_braquet;
					l_pair.second.set("location_match", s_c.before_braquet);
					while (!l_c.key.empty() || l_i)
					{
						l_i = false;
						l_c = get_next_variable(s_c.value);
						l_pair.second.set(l_c.key, l_c.value);
						if (s_c.value.length() > l_c.next_start)
							s_c.value = s_c.value.substr(l_c.next_start);
						else
							break;
					}
					pair.second.add_location(l_pair);
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
			if (port_count.find(atoi(pair.second.get_id().c_str())) == port_count.end())
			{
				std::pair<int, int> port_pair(atoi(pair.second.get_id().c_str()), 0);
				listen_socket sock(atoi(pair.second.get_id().c_str()));
				_listen_sockets.push_back(sock);

				// std::cout << "heheheheheh: " << atoi(pair.second.get_id().c_str()) << std::endl;
				port_pair.first = atoi(pair.second.get_id().c_str());
				port_pair.second = 0;
				port_count.insert(port_pair);
				pair.first = pair.second.get_id() + "_0";
			}
			else
			{
				(*port_count.find(atoi(pair.second.get_id().c_str()))).second += 1;
				pair.first = pair.second.get_id() + "_" + ft_to_string((*port_count.find(atoi(pair.second.get_id().c_str()))).second);
			}
			servers.insert(pair);
			std::string server_names = pair.second.get_server_name();
			while (!server_names.empty())
			{
				std::string key = server_names.substr(0, server_names.find(" ")) + ":" + pair.second.get_id();
				servers_name_to_server[key] = pair.first;
				if (server_names.find(" ") != std::string::npos)
					server_names = server_names.substr(server_names.find(" ") + 1);
				else
					break;
			}
		}
		if (s.length() > m_c.next_start)
			s = s.substr(m_c.next_start);
		else
			break;
	}
}

void webserv::check_error(std::string reason)
{
	std::cout << "config error: " << reason << std::endl;
	throw BadConfig();
}

void webserv::check_config(std::string config_file)
{
	std::string s = file_to_string(config_file);
	std::string serv_name;
	t_config m_c;
	t_config s_c;
	t_config l_c;

	bool m_i = true;
	bool s_i = true;
	bool l_i = true;

	if (s.empty())
		check_error("bad configuration file");
	if (trim(s, "\n ").empty())
		check_error("empty configuration file");

	while (!m_c.key.empty() || m_i)
	{
		m_i = false;
		m_c = get_next_variable(s);
		if (m_c.key == "server")
		{
			server serv;
			if (trim(m_c.value, " \n\t").empty())
				check_error("empty server");
			while (!s_c.key.empty() || s_i)
			{
				s_i = false;
				s_c = get_next_variable(m_c.value);

				if (s_c.key == "location")
				{
					location loc;
					if (s_c.before_braquet.empty())
						check_error("location need location match");
					loc.set("location_match", s_c.before_braquet);
					if (trim(s_c.value, " \n").empty())
						check_error("empty location");
					while (!l_c.key.empty() || l_i)
					{
						l_i = false;
						l_c = get_next_variable(s_c.value);
						loc.set(l_c.key, l_c.value);
						if (s_c.value.length() > l_c.next_start)
							s_c.value = s_c.value.substr(l_c.next_start);
						else
							break;
					}
				}
				else
				{
					serv.set(s_c.key, s_c.value);
				}
				if (m_c.value.length() > s_c.next_start)
					m_c.value = m_c.value.substr(s_c.next_start);
				else
					break;
			}
			std::string server_names = serv.get_server_name();
			while (!server_names.empty())
			{
				std::string key = server_names.substr(0, server_names.find(" ")) + ":" + serv.get_id();
				if (serv_name.find(key) != std::string::npos && serv_name[serv_name.find(key) + key.size()] == '|')
					check_error("server name with this port already exist");
				serv_name += key + "|";
				if (server_names.find(" ") != std::string::npos)
					server_names = server_names.substr(server_names.find(" ") + 1);
				else
					break;
			}
			std::cout << serv_name << std::endl;
		}
		if (s.length() > m_c.next_start)
			s = s.substr(m_c.next_start);
		else
			break;
	}
}

void webserv::run()
{
	std::cout << "~*~ Server running ~*~" << std::endl;
	std::cout << "Listening on ports (server name) : " << std::endl;

	for (std::map<std::string, server>::const_iterator i = servers.begin(); i != servers.end(); i++)
	{
		std::cout << (*i).first << " (" << (*i).second.get_server_name() << ")" << std::endl;
	}
	handle_client_connection();
}

void webserv::close_sockets(void)
{
	for (std::vector<listen_socket>::iterator it = _listen_sockets.begin(); it != _listen_sockets.end(); it++)
	{
		close(it->get_fd());
	}
	servers.clear();
}

std::string urlDecode(std::string str)
{
	std::string ret;
	char ch;
	int j;
	int len = str.length();

	for (int i = 0; i < len; i++)
	{
		if (str[i] != '%')
		{
			if (str[i] == '+')
				ret += ' ';
			else
				ret += str[i];
		}
		else
		{
			sscanf(str.substr(i + 1, 2).c_str(), "%x", &j);
			ch = static_cast<char>(j);
			ret += ch;
			i = i + 2;
		}
	}
	return ret;
}

t_responce_config webserv::generate_config(std::string host, std::string path, std::string header)
{
	server *selected = NULL;
	// if hostname match with server use this server. If not use default server with this port
	if (servers_name_to_server.find(host) != servers_name_to_server.end())
		selected = &servers[servers_name_to_server[host]];
	else
		selected = &servers[host.substr(host.find(":") + 1) + "_0"];

	// get location that match with path if exist
	path = urlDecode(path);
	location *loc = selected->get_location(path);
	t_responce_config config;
	config.url = path;
	if (loc)
	{
		// get config from server and overide it with location
		selected->config_responce(&config);
		loc->config_responce(&config);
		if (loc->have_root())
			config.path = complete_url(config.path, path.substr(loc->get_location_match().size()));
		else
			config.path = complete_url(config.path, path);
	}
	else
	{
		// get config from server
		selected->config_responce(&config);
		config.path += rtrim(path, "/");
	}
	// std::cout << config.path << " " << config.root << " " << config.index << std::endl;
	//  add index if exist
	if (compare_url(config.path, config.root) && config.index.size())
	{
		config.path = complete_url(config.path, config.index);
	}
	if (loc)
	{
		// std::cout << "url: " << config.url << " | " << selected->get_id() + ":" + selected->get_server_name() << " | loc: " << loc->get_location_match() << " | " << config.path << " | " << config.method << std::endl;
	}
	else
	{
		// std::cout << "url: " << config.url << " | " << selected->get_id() + ":" + selected->get_server_name() << " | alone | " << config.path << std::endl;
	}
	config.header = header;
	return config;
}

std::map<std::string, std::string> *webserv::get_mime(void)
{
	return &mime;
};
