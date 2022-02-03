

Cyberpi non ha una batteria interna, da solo funziona solo se collegato al computer


info su hardware:

http://docs.makeblock.com/halocode/en/mbuild/hardware/sensors/ultrasonic-sensor-2.html
https://education.makeblock.com/help/category/cyberpi-mbot2/electronic-parts-and-components/cyberpi-series-mbuild-modules/cyberpi-series-sensors/


collego Cyberpi al computer e si accende automaticamente
sul display appare il menu
  joystick per muoversi
  pulsante A (quadrato) per uscire (Return)
  pulsante B (triangolo) per entrare (Confirm)
  quando c'è un programma in esecuzione, Home per tornare al menu

avvio mBlock
verifico che tra i dispositivi c'è Cyberpi
premo Connect
mBlock propone una porta COM (di solito è abbastanza furbo da trovare quella giusta)


due parole su mBlock, similarità con Scratch, novità della sezione "Devices"


Modalità Live
programma eseguito in mBlock


quando è in modalità Live Cyberpi è "sordo", ascolta solo i comandi che arrivano dal computer (non funziona nemmeno il tasto Home)


Cyberpi è visto come uno degli sprite e interagisce con gli altri via variabili o messaggi
se voglio muovere lo sprite col joystick devo fare il giro del globo...
cyberpi ascolta e invia messaggi...
... gli sprite reagiscono ai messaggi
vale anche l'inverso: clicco lo sprite, lui invia un messaggio...
... cyberpi lo riceve ed emette un suono/fa comparire una scritta


altri pulsanti: come la tastiera con Scratch, qui in più conta il numero di volte che un tasto è stato premuto






microfono e fotoricettore: range 0-100

per far dire al panda il livello di luminosità/rumorosità: il device deve aggiornare regolarmente una variabile col valore del sensore, il panda lo dice



possiamo simulare il tramonto con lo sprite del sole (usare la torcia del cellulare per cambiare il livello di luminosità)







LED rossi
LED intensità
LED lampeggianti
LED lampeggianti alternativamente (indirizzamento singolo LED)
LED strip: animazione supercar
LED strip: lampeggiante polizia -> il lampeggio strobo è lentissimo in modalità LIVE

Speaker

musica, melodia
anche armonia (quante voci?)

Sirena polizia: Cyberpi supporta il multithreading, si può far suonare la sirena col lampeggiante



giroscopio -> necessita dell'azzeramento degli angoli perché è un integrale dell'accelerazione angolare
(x: rotazione in avanti/dietro, y: rotazione sinistra/destra, z: rotazione sul piano)

accelerometro -> tilt, non necessita di azzeramento perché basato sulla gravità
wave -> accelerazione direzionale

es. se wave up: far saltare il panda, se shaken farlo tremare
salto con gravità
gioco salta l'ostacolo

motion sensing: control (Sprite) to follow Cyperpi with sensitivity
permette di muovere uno sprite usando Cyberpi come fosse un puntatore (stile controller Wii)
ci vuole il persempre!




anche con la musica si nota il ritardo in modalità Live.

display: origine in altro a sx
display: la dimensione del testo è globale, non si possono visualizzare due scritte a dimensioni diverse
differenza show (bitmap!) e print
display: autoscrolling (provare a stampare i numeri da 1 a 20 uno per riga)
display: dedurre quante righe di testo per ognuna delle 4 dimensioni (small:8, middle:6, big:4, super-big: poco meno di 3)
print vs show label: ?
line chart: disegna un grafico tra 0 e 100 (rimappati su 0-128), scroll automatico, distanza tra punti configurabile, colore pure, spessore linea no
bar chart: unica barra al centro, mappata tra 0 e 100
per avere più barre, cambiare colore; se si torna a un colore già usato, viene aggiornata la barra vecchia
table: disegna una tabella, la più piccola che contiene tutti i dati (comunque non oltre 4x3)

luminosità come chart e bar
modulare la velocità di aggiornamento col tempo (line chart anche con la risoluzione)
anche in questo caso la reattività in modalità upload è molto più alta della live (ma meno comoda)



modalità UPLOAD

il programma però è in mBlock: se scollego la schedina il programma non funziona più.
i blocchi a cappello tipici di Scratch sono disabilitati

when joystick middle pressed
  led display rosso per 1 secondo

upload
dove va a finire?!?! sostituisce l'ultimo degli otto programmi eseguito
chiudo mBlock
funziona ancora
stacco/riattacco Cyberpi: c'è ancora!

se c'è un per sempre o il programma sembra bloccato -> premere il tasto Home per tornare al menu

--------------------------

mBot2 Shield se non è già presente lo si carica come estensione
si ottengono i comandi di controllo dei motori
per il sensore ultrasonico e il sensore di linea ci vogliono le estensioni dedicate (line sensor è in beta!)
il primo indice si riferisce al primo sensore in catena (mBuild è una daisy-chain, ce ne potrebbero essere di più)

https://education.makeblock.com/help/ultrasonic-sensor-2/
https://education.makeblock.com/help/mblock-block-based-device-cyberpi-extension-quad-rgb-sensor/
https://education.makeblock.com/help/mbuild-quad-rgb-sensor/#articleTOC_6






~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

CyberPi ~80€

CPU: ESP-32 SOC (System on a chip)

  Xtensa® 32-bit LX6 dual-core 240MHz
  448KB ROM
  520KB SRAM
  8MB SPI Flash (Serial Peripheral Interface)
  8MB PSRAM (Pseudo Static RAM)

> Pseudostatic RAM (PSRAM or PSDRAM) is dynamic RAM with built-in refresh and address-control circuitry to make it behave similarly to static RAM (SRAM). It combines the high density of DRAM with the ease of use of true SRAM.

Wifi: Sì
Bluetooth: Sì
Input:
 Joystick 5 direzioni
 Microfono
 Pulsanti A (conferma), B (ritorno), Home
 Fotoricettore
Output:
 Display a colori 128x128
 Speaker
 Striscia LED
Porte di espansione:
 USB C (alimentazione + programmazione)
 porta 14-pin
 connettore mBuild (daisy-chain)

Programmabile con mBlock coi blocchi o in Python

~~~~~~~~~~~~~~~~~~~~~~~~~~


