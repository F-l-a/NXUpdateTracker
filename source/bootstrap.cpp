/*
 *   This file is part of nx-spa
 *   Copyright (C) 2023 Bernardo Giordano
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   Additional Terms 7.b and 7.c of GPLv3 apply to this file:
 *       * Requiring preservation of specified reasonable legal notices or
 *         author attributions in that material or in the Appropriate Legal
 *         Notices displayed by works containing it.
 *       * Prohibiting misrepresentation of the origin of that material,
 *         or requiring that modified versions of such material be marked in
 *         reasonable ways as different from the original version.
 */

#include <stdio.h>
#include <switch.h>
#include "network.h"

//inizializza l'app
bool appInit() {				

	consoleInit(NULL);			//inizializzo la console
	
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
	
	romfsInit();					//monto il romFS dell'app corrente
  
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
		consoleUpdate(NULL);			//aggiorno la console
		svcSleepThread(0ull);			//aspetto per visualizzare i messaggi sulla console
	}

	consoleExit(NULL);				//chiudo la console
	networkExit();					//spengo il server
	romfsExit();					//smonto il romFS dell'app corrente
	return code;					//esco
}
