#include "../includes/header.hpp"

int main(int argc, char** argv)
{
	if(argc!= 2)
	{
		std::cout << "Missing argument. Usage: ./webserv <./src/Config/config_file.conf>" << std::endl;
		return EXIT_FAILURE;
	}
	else {
		std::cout << "Pioupioupiou lançage des serveurs contenus dans : " << argv[1] << std::endl;
		/*	1.parser le fichier de config
			2.lancer le serveur en boucle infinie
			*/
	}
	return EXIT_SUCCESS;
}