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

#include "bootstrap.h"

int main(int argc, char* argv[]) {
	
	if (!appInit()) {											//inizializza l'app. crea web server
		printf(CONSOLE_RED "\nERR: Couldn't initialize the app!\n");	//messaggio errore se fallisce
		return appExit(1);						//se fallisce, esce
	}

	WebCommonConfig config;										//configurazione Applet
	Result rc = webPageCreate(&config, "http://0.0.0.0:8080");	//creazione configurazione pagina web con indirizzo URL
  
	if (!R_SUCCEEDED(rc)) {										//se creazione non avvenuta con successo
		printf(CONSOLE_RED "\nERR: Couldn't create the webPage!\tErrorCode: %d", rc);	//messaggio errore se fallisce
		return appExit(1);						//se fallisce, esce
	}
  
    webConfigSetWhitelist(&config, "^http*");					//imposto gli URL visitabili
    webConfigSetFooter(&config, true);							//imposto l'utilizzo del footer: true->utilizzato
    webConfigSetFooterFixedKind(&config, WebFooterFixedKind_Always);	//Tipologia footer: _Default | _Always | _Hidden
	webConfigSetPageScrollIndicator(&config, true);				//imposto l'utilizzo di uno scroller. true->utilizzato
	webConfigSetScreenShot(&config, true);						//imposto la possibilità di effettuare screenshot
    webConfigSetTouchEnabledOnContents(&config, true);			//imposto la possibilità di uso del touch screen
    webConfigSetJsExtension(&config, true);						//imposto la possibilità di utilizzo di javascript. true->utilizzato
    rc = webConfigShow(&config, nullptr);						//Lancia il webApplet con la configurazione impostata
  
	return appExit(0);		//esco dall'app spegnendo tutto
}
