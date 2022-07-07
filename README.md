# Webserv

		1. recup le fichier de config : argv[2]
			parsing du fichier dans differentes classes : 
				- verifier que le fichier de config est ok : pas de fichier vide, des {} fermées ...
				- une classe qui reprends l'ensemble des infos
				- une classe par port écouté avec ses specificités
			but : selon la requete client, trouver le bon port et utiliser la config associée
		a voir : Fichier de config Nginx 
		https://www.digitalocean.com/community/tutorials/understanding-the-nginx-configuration-file-structure-and-configuration-contexts

		2. lancer le serveur en boucle infinie :
			creer un/plusieurs socket : 1 par ports a ecouter (listen_fd = socket())
			lier un socket avec un port a ecouter (bind())
			ecouter en mode non bloquant les requetes clients (listen() /fd_client = accept() / select())
				parser les requetes clients (contenu dans fd_client)
					identifier sur quel port on ecoute et a quel partie du serveur transmettre la requete
					identifier la requete du client et si c'est possible d'y repondre 
						en fonction des parametres de la partie consernée
				
				envoyer une reponse au client 

			fini ? Fermer les sockets

  		3. si on a besoin de contenu dynamique (.php par ex) on passera par une CGI
			https://www.nginx.com/resources/wiki/start/topics/examples/phpfcgi/
		
To do a coté :
		
- Creer une fonction qui renvoie les types de pages/reponses avec leur messages, a transmettre en fonction de la requete et de son succes/echec: 1xx,2xx,3xx,4xx ou 5xx

- Creer une gestion d'erreur efficace lors de chaque creation de classe : penser aux exceptions a throw (on ne peut pas utiliser le retour de errno dans le projet)
