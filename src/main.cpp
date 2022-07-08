#include "../includes/webserv.hpp"

int main(int argc, char** argv)
{
	if(argc!= 2)
	{
		std::cout << "Missing argument. Usage: ./webserv <./src/Config/config_file.conf>" << std::endl;
		return EXIT_FAILURE;
	}
	else {
		std::cout << "Pioupioupiou lançage des serveurs contenus dans : " << argv[1] << std::endl;
		
		//	1.parser le fichier de config
			/* proposition d'organisation :

				container map(int PortEcouté, class Server); // un container regroupant toutes les infos parsées dans le serveur.conf, 
																reférencées selon le port écouté = une classe Server() dédiée

					↪class Server(); // Une classe par port écouté, sous-divisée en classe Location()

						↪class Location(); // Une sous classe par subdivision du server, avec des regles qui override celles du Server()
											 si necessaire (methode authorisées, index ...) */


		//	2.lancer le serveur en boucle infinie : test not  tested yet
			// 	int ServerFd; //fd donné par socket(), permettra l'acces au réseau
			// 	if(ServerFd = socket(AF_INET, SOCK_STREAM, 0) < 0)
			// 	{
			// 		std::cerr << "cannot creat socket" << std::endl;
			// 		exit (EXIT_FAILURE);
			// 	}

			// 	const int PORT = 8080; //port de notre serveur
			// 	struct sockaddr_in address; //struct pour bind :
			// 		// struct sockaddr_in 
			// 		// { 
			// 		// 	__uint8_t         sin_len; 
			// 		// 	sa_family_t       sin_family; 
			// 		// 	in_port_t         sin_port; 
			// 		// 	struct in_addr    sin_addr; 
			// 		// 	char              sin_zero[8]; 
			// 		// };
			// 	memset((char *)&address, 0, sizeof(address));
			// 	address.sin_family = AF_INET; //acces par IPv4
			// 	address.sin_addr.s_addr = htonl(INADDR_ANY); //whatever IP, INADDR_ANY = 0.0.0.0 
			// 	address.sin_port = htons(PORT); 
			// 		// htonl converts a long integer (e.g. address) to a network representation 
			// 		// htons converts a short integer (e.g. port) to a network representation 

			// 	if(bind(ServerFd, (struct sockaddr *)&address, sizeof(address)) < 0)
			// 	{
			// 		std::cerr << "bind failed" << std::endl;
			// 		exit (EXIT_FAILURE);
			// 	}
			// 		// lie le port de notre serveur au FdServer et à la structure qui permet d'échanger sur le réseau
			// while(true)
			// {

			// 	if (listen(ServerFd, 3) < 0) 
			// 	{ 
			// 		exit(EXIT_FAILURE); 
			// 		std::cerr << "In listen" << std::endl;
			// 	}

			// 	int NewSocket;
			// 	if (NewSocket = accept(ServerFd, (struct sockaddr *)&address, (socklen_t*)sizeof(address)) < 0 )
			// 	{
			// 		std::cerr << "In accept" << std::endl;           
			// 		exit(EXIT_FAILURE);        
			// 	}	


			// 	char buffer[1024] = {0};
			// 	int valread = read( NewSocket, buffer, 1024); 
			// 	std::cout << buffer << std::endl;
			// 	if(valread < 0)
			// 	{ 
			// 		printf("No bytes are there to read");
			// 	}
			// 	char *hello = "Hello from the server";//IMPORTANT! WE WILL GET TO IT
			// 	write(NewSocket , hello , strlen(hello));


			// 	close(NewSocket);
			// }

	}
	return EXIT_SUCCESS;
}