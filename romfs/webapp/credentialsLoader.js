//carica le credenziali di github dal file ini presente nella cartella root del server (romfs/webapp). l'ini è copiato in questa cartella dal .nro
var inizializzazioneGitHubEffettuata = false;	//inizialmente non ho ancora letto le credenziali
async function loadCredentials(){
	
	if(!inizializzazioneGitHubEffettuata){		//se non ho ancora effettuato l'inizializzazione delle credenziali
		
		try{
			const response = await axios.get('/githubInfo.ini');	//prende il file- sdmc:/config/NXUpdateTracker/githubInfo.ini unsupported protocol sdmc:
			
			//se non trova il file -> errore
            if (response.status !== 200) {							
				console.log(response)
				var testo = "Cannot read GitHub Credentials. Version loader won't work - ";
				aggiungiNotifica(error, "githubInfo.ini error", testo);
            }
			
			const content = response.data;
			var lines = content.split('\n');				//divido il file in un vettore di righe
			for (var i = 0; i < lines.length; i++) {		//per ogni riga
			
				if (line === '') {		//se  linea vuota o commento (inizia con ;)
					continue; 			//salta la linea
				}	
				var line = lines[i].trim();					//tolgo gli spazi iniziali e finali (anche il \n)
				var components = line.split('=');
				var chiave = components[0].trim();
				var valore = components[1].trim();
				//controllo se la linea inizia con ciò che serve, la divido sull '=' in vettore e assegno il valore
				if (chiave === 'API_TOKEN') {
					API_TOKEN = valore;
				} else if (chiave === 'OWNER') {
					OWNER = valore;
				} else if (chiave === 'REPO') {
					REPO = valore;
				} else if (chiave === 'FILE_PATH') {
					FILE_PATH = valore;
				}
			}
			inizializzazioneGitHubEffettuata = true;	//imposto a vero la flag. prossima volta ritorna senza rileggere
			
		}catch(error){
			var testo = "Cannot load GitHub Credentials - " + error;
			aggiungiNotifica('error', 'GENERIC ERROR', testo);
			console.log(error);
		}
	}
}