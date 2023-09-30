/*	-crea e sposta files
 */

#include "pagesetup.h"
#include <cstdio>
#include <cerrno>
#include <switch.h>

#define DESTINAZIONE_HTML "sdmc:/switch/NXUpdateTracker/index.html"
#define DESTINAZIONE_JS "sdmc:/switch/NXUpdateTracker/credentialsLoader.js"
#define DESTINAZIONE_INI "sdmc:/switch/NXUpdateTracker/githubInfo.ini"

bool fileExists(const char* percorso);
bool copyFile(const char* sorgente, const char* destinazione);

//COPIA FILE NECESSARI. SE NON RIESCE A COPIARE, RITORNA 0: ERRORE
int pageSetup(){
	//HTML
	if (!fileExists(DESTINAZIONE_HTML) || !fileExists("sdmc:/switch/NXUpdateTracker/.keep")) {	//se il file non esiste o se ".keep" non esiste
		if(!copyFile("romfs:/webapp/NXUpdateTracker.html", DESTINAZIONE_HTML)){	//copia HTML
			return 0;
		}
	}
	
	//JS
	if (!fileExists(DESTINAZIONE_JS) || !fileExists("sdmc:/switch/NXUpdateTracker/.keep")) {	//se il file non esiste o se ".keep" non esiste
		if(!copyFile("romfs:/webapp/credentialsLoader.js", DESTINAZIONE_JS)){	//copia JS
			return 0;
		}
	}
	
	//INI
	if (!fileExists(DESTINAZIONE_INI)) {									//se il file non esiste ancora
		if(!copyFile("romfs:/webapp/githubInfo.ini", DESTINAZIONE_INI)){	//copia INI
			return 0;
		}
    }
	
	printf(CONSOLE_GREEN "\nPage setup completed");
	consoleUpdate(NULL);			//aggiorno la console
	svcSleepThread(0ull);			//aspetto per visualizzare i messaggi sulla console
    return 1;
}

//CONTROLLA SE IL FILE ESISTE
bool fileExists(const char* percorso) {
    FILE* file = fopen(percorso, "r");	//Provo ad aprirlo in lettura
    if (file){							//se non è null, allora lo chiudo e ritono vero
        fclose(file);
        return true;
    }
    return false;						//altrimenti non esiste, ritorno falso
}

//COPIA IL FILE
bool copyFile(const char* sorgente, const char* destinazione) {
    
    FILE* fileSorgente = fopen(sorgente, "rb");		//APRO FILE SORGENTE
    if (!fileSorgente) {
		printf(CONSOLE_RED "\nERR: Error opening source file: %s", sorgente);
        perror("\n \\_Error description:");		//SE NON ESISTE, STAMPO ERRORE
        return false;
    }

    FILE* fileDestinazione = fopen(destinazione, "wb");	//APRO FILE DESTINAZIONE
    if (!fileDestinazione) {							//se non riesco, chiudo il file sorgente e stampo errore
		printf(CONSOLE_RED "\nERR: Error opening destination file: %s", destinazione);
        perror("\n \\_Error description:");		//SE NON ESISTE, STAMPO ERRORE
		fclose(fileSorgente);
        return false;
    }

    char buffer[4096];
    size_t byteLetti;
    while ((byteLetti = fread(buffer, 1, sizeof(buffer), fileSorgente)) > 0) {	//leggo dal file sorgente
        size_t byteScritti = fwrite(buffer, 1, byteLetti, fileDestinazione);		//scrivo sul file destinazione
        if (byteScritti != byteLetti) {							//se scrivo un numero di byte diverso da quelli letti stampo errore e chiudo file
            printf(CONSOLE_RED "\nERR: Error writing to destination file: %s", destinazione);
			perror("\n \\_Error description:");		//SE NON ESISTE, STAMPO ERRORE
            fclose(fileSorgente);
            fclose(fileDestinazione);
            return false;
        }
    }

    fclose(fileSorgente);			//chiude file
    fclose(fileDestinazione);

    return true;
}