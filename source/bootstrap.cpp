
 /*	-controlla se sono in appletMode
 *	-inizializza e chiude console
 *	-inizializza e chiude romfs
 *	-chiama inizializzazione e chiusura server
 *	-aspetta input uscita in caso di errori
 */
 

#include <stdio.h>
#include <switch.h>
#include "network.h"

//inizializza l'app
bool appInit() {				

	consoleInit(NULL);			//inizializzo la console
	consoleDebugInit(debugDevice_CONSOLE);

	
	printf(CONSOLE_YELLOW);
	printf("  _   ___   ___    _           _       _    _______             _              \n");
    printf(" | \\ | \\ \\ / / |  | |         | |     | |  |__   __|           | |             \n");
    printf(" |  \\| |\\ V /| |  | |_ __   __| | __ _| |_ ___| |_ __ __ _  ___| | _____ _ __  \n");
    printf(" | . ` | > < | |  | | '_ \\ / _` |/ _` | __/ _ \\ | '__/ _` |/ __| |/ / _ \\ '__| \n");
    printf(" | |\\  |/ . \\| |__| | |_) | (_| | (_| | ||  __/ | | | (_| | (__|   <  __/ |    \n");
    printf(" |_| \\_/_/ \\_\\\\____/| .__/ \\__,_|\\__,_|\\__\\___|_|_|  \\__,_|\\___|_|\\_\\___|_|    \n");
    printf("                    | |                                                        \n");
    printf("                    |_|                          " CONSOLE_GREEN "              F-l-a " CONSOLE_WHITE "-" CONSOLE_RED " v1.0    \n");
	printf(CONSOLE_CYAN "________________________________________________________________________________\n");
	consoleUpdate(NULL);			//aggiorno la console

	//Se non sono in application-mode (sono in appletMode) esco con un messaggio errore
    if (appletGetAppletType() != AppletType_Application){
        printf(CONSOLE_RED "\n-->Applet Mode is not supported, please launch hbmenu by" CONSOLE_MAGENTA " overriding" CONSOLE_RED " a title!\n");
		printf(CONSOLE_MAGENTA "                         (open a game pressing the R button)_/\n");
		return false;	//ritorno falso. il messaggio è stampato dalla funzione di uscita con errore
    }
   
	svcSleepThread(0ull);	//aspetto per visualizzare i messaggi sulla console
	
	Result rc = romfsInit();					//monto il romFS dell'app corrente
	if (R_FAILED(rc)){
        printf(CONSOLE_RED "\nERR: romfsInit: %08X\n", rc);
	}
	
	if (!networkInit()) {			//crea il web server
		return false;
	}								//ritorna lo stato
	return true;
}

//esco dall'app
int appExit(int code) {	
 
	if(code != 0){						//se esco con errore, ho la possibilità di fermare la console per leggere gli errori
		printf(CONSOLE_WHITE "\n\n\nPress " CONSOLE_CYAN "[" CONSOLE_RED "+ " CONSOLE_WHITE "or" CONSOLE_RED " - " CONSOLE_WHITE "or" CONSOLE_RED " B" CONSOLE_CYAN "]" CONSOLE_WHITE " to exit..");
		consoleUpdate(NULL);			//aggiorno la console
		
		PadState pad;					//struct contenente lo stato del pad
		padConfigureInput(1, HidNpadStyleSet_NpadStandard);	//configura l'input. (numeroControllerMassimo, TipoController)
		padInitializeDefault(&pad);		//inizializza la struct contenente lo stato del pad
	
		do{								//mette in pausa l'esecuzione. esce se +/-/B premuto
			padUpdate(&pad);					//aggiorna lo stato del pad leggendo dalle sorgenti di input specificate
			u64 kDown = padGetButtons(&pad); 	//ritorna i pulsanti correnti premuti
			if(kDown & HidNpadButton_Minus || kDown & HidNpadButton_Plus || kDown & HidNpadButton_B){//se +/-/B è stato premuto esco dal ciclo
				break;
			}
		}while(true);
	}else{
		printf(CONSOLE_GREEN "\nExiting..");
		consoleUpdate(NULL);			//aggiorno la console
		svcSleepThread(0ull);			//aspetto per visualizzare i messaggi sulla console
	}

	consoleExit(NULL);				//chiudo la console
	networkExit();					//spengo il server
	romfsExit();					//smonto il romFS dell'app corrente
	return code;					//esco
}
