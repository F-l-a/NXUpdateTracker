 /*	-chiama inizializzazione app
 *	-chiama spostamento risorse romfs -> sdmc
 *	-inizializza e crea webApplet
 */


#include <stdio.h>
#include <switch.h>
#include <string.h>

#include "bootstrap.h"
#include "pagesetup.h"

int main(int argc, char* argv[]) {
	
	if (!appInit()) {											//inizializza l'app. crea web server
		printf(CONSOLE_RED "\nERR: Couldn't initialize the app!\n");	//messaggio errore se fallisce
		return appExit(1);						//se fallisce, esce
	}
	
	if(!pageSetup()){					//inserisce in sdmc:/switch/NXUpdateTracker i file necessari per l'app web
		printf(CONSOLE_RED "\nERR: Couldn't setup the page!\n");	//messaggio errore se fallisce
		return appExit(1);						//se fallisce, esce
	}

	WebCommonConfig config;										//configurazione Applet
	const char* URL = "http://0.0.0.0:8080";
	Result rc = webPageCreate(&config, URL);	//creazione configurazione pagina web con indirizzo URL
  
	if (!R_SUCCEEDED(rc)) {										//se creazione non avvenuta con successo
		printf(CONSOLE_RED "\nERR: Couldn't create the webPage at %s!\tErrorCode: %d", URL, rc);	//messaggio errore se fallisce
		return appExit(1);						//se fallisce, esce
	}
  
	printf(CONSOLE_GREEN "\nOK: webPage successfully created at %s!", URL);	//not printed. why?
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
