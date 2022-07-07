# Webserv

		/*recup le fichier de config : argv[2]
			parsing du fichier dans differentes classes : 
				verifier que le fichier de config est ok : pas de fichier vide, des {} fermées ...
				une classe qui reprends l'ensemble des infos
				une classe/port écouté avec ses specificités
			but : selon la requete client, trouver le bon port et utiliser la config associée
		*/

		/*lancer le serveur en boucle infinie :
			creer un/plusieurs socket : 1 par ports a ecouter (socket)
			lier un socket avec un port a ecouter (bind)
			ecouter en mode non bloquant les requetes clients (listen /accept)
				parser les requetes clients
					identifier sur quel port on ecoute et a quel partie du serveur transmettre la requete
					identifier la requete du client et si c'est possible d'y repondre 
						en fonction des parametres de la partie consernée
				
				envoyer une reponse au client 

			fini ? Fermer les sockets
		*/

		/* creer les types de reponses avec leur messages,
			 a transmettre en fonction de la requete : 1xx,2xx,3xx,4xx ou 5xx
		*/

  /*si on a besoin de contenu dynamique (.php par ex) on passera par une CGI */
  
  /* Creer une gestion d'erreur efficace lors de chaque creation de classe : penser aux exceptions a gerer */
