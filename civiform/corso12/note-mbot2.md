

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


====== fino qui ==========


# Lezione n. 7 20220208

recap fotoricettore/microfono; possibili utilizzi

fotoricettore
* regolare il contrasto
* accendere le luci (interruttore crepuscolare)
* ottimizzare l'irraggiamento

audio:
* registrare/riprodurre
* comandi vocali
* attivare comandi col rumore (es. battimani)

possiamo simulare il tramonto con lo sprite del sole (usare la torcia del cellulare per cambiare il livello di luminosità) ANCHE NO: LO FACCIO SOLO VEDERE

-------------------------------------------------------------------
da EN mBot2 Getting Started Activities V1.1.pdf

Accelerometro (modalità LIVE)

accelerometro -> non necessita di azzeramento perché basato sulla gravità (STATICO!)
giroscopio -> necessita dell'azzeramento degli angoli perché è un integrale dell'accelerazione angolare
(x: rotazione in avanti/dietro, y: rotazione sinistra/destra, z: rotazione sul piano)

mostrare il blocco control e di come sia necessario calibrarlo inizialmente
motion sensing: control (Sprite) to follow Cyperpi with sensitivity
permette di muovere uno sprite usando Cyberpi come fosse un puntatore (stile controller Wii)
ci vuole il persempre!


alcuni blocchi mostrano i dati grezzi -> guardarli con le variabili
altri integrano i dati e riconoscono le "gesture" -> "sensor fusion"
gesture -> gesto/atto
shacking/waving 0-100 (adimensionali)
tilt -> in gradi

es. se wave up: far saltare il panda, se shaken farlo tremare
salto con gravità
gioco salta l'ostacolo

simulare un contapassi (il panda conta gli shake)

idee per dopo:
* accendo i led per simulare lo scoppio dell'airbag
* rallentare se il tilt è oltre i 5/10° (dito sotto la ruota)

---------------------------------------------------------------

STRISCIA LED

LED rossi -> non è un vero rosso: click sul comando, verificare che non era rosso
il led resta acceso fino al termine del programma
c'è anche il blocco temporizzato
LED acceso solo quando il tasto A è premuto -> risponde con un certo ritardo

modalità UPLOAD

il programma però è in mBlock: se scollego la schedina il programma non funziona più.
i blocchi a cappello tipici di Scratch sono disabilitati

upload
chiudo mBlock
funziona ancora
stacco/riattacco Cyberpi: c'è ancora!

se c'è un per sempre o il programma sembra bloccato -> premere il tasto Home per tornare al menu
dove va a finire?!?! sostituisce l'ultimo degli otto programmi eseguito

la differenza è ancora più sostanziale quando il numero di operazioni coinvolte è maggiore; proviamo con un ciclo

LED intensità: cambiarla a dente di sega o triangolare con set brightness to/increase LED brightess by

la pulsazione avviene così velocemente che diventa un lampeggio.
fare passi da 1% e aggiungere una pausa di 0.01 secondi

LED lampeggianti
LED lampeggianti alternativamente (indirizzamento singolo LED)
LED lampeggianti alternativamente (definizione della configurazione della striscia)

LED strip: animazione supercar (provare in modalità LIVE e UPLOAD)
LED strip: RGB -> semaforo (2 led rossi (4s), due led verdi (5s), led centrale giallo (2s))
il giallo non è convincente -> scegliamo noi i colori
in modalità LIVE si percepiscono le accensioni singole
LED strip: indicatore di direzione animato ("moderno")
LED strip: lampeggiante polizia 4x(20ms+80ms)-> il lampeggio strobo è lentissimo in modalità LIVE

led: vu-meter
led: luci crepuscolari/inversamente proporzionali alla luminosità

d'ora in poi solo upload

Speaker

suoni predefiniti
musica, melodia: conviene lavorare in upload, le pause del LIVE tra una nota e l'altra rovinano l'esecuzione

Sirena polizia: Cyberpi supporta il multithreading, si può far suonare la sirena col lampeggiante
quando attivare la sirena? tasto b
valutare "quando tasto B premuto": se voglio far continuare il suono non va bene, serve un persempre + if


---------- finito qui -----------------


Display

test/tabella/grafico sono mutuamente esclusive
le 8 etichette sono sovraimposte e funzionano su tutte le modalità
orientando opportunamente il display (right) col testo big si possono fare le emoticon vecchia maniera... insomma, non sono bellissime...

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

----------------------------------------------------------------
da EN mBot2 Getting Started Activities V1.1.pdf

LAN dovrebbe funzionare anche senza Router WiFi, la rete la creano le CyberPi tra loro

stop motori quando si preme A
per fare andare avanti, un motore positivo, l'altro negativo
turn left 90° vs turn left at 50 RPM for 1 sec
traiettoria quadrato/pentagono(!)
passeggiata casuale (con indicatore di movimento)
gimcana
uso degli encoder come sensori
calibrazione degli encoder, anche qui (tolleranze meccaniche, giochi, diametro ruote, ...)!


sensore ultrasonico: visto da davanti TX a sx, RX a dx
range 5-300, +/-5%


sensore di linea
calibrazione con un doppio click del pulsantino
per b/n di norma non serve, se no spostare i sensori dentro/fuori la linea fino a quando non smette il lampeggio
calibrare il sensore sul colore più chiaro da considerare linea

codifica:

lr
WW 0
WB 1
BW 2
BB 3

idem per i 4 (1 sulla linea, 0 fuori dalla linea, nell'ordine l2l1r1r2)
i laterali si usano per determinare diramazioni

deviation: quanto sono/mi sto allontanando dalla linea
si può usare per modulare la curva (50 + 0.6 * deviation)

blu -> rallenta
rosso -> torna indietro (gira 180° + vai avanti di un tot (per uscire dal rosso))
verde -> emetti un suono/accendi i led
-----------------------------------------------------------------------------------






===============================================================================
semplici applicazioni CyberPi "only"

when shaken detected -> mostra il valore del dado
accoda gli eventi, conviene persempre + if

  set volume to 5 %
  forever
   if shaken detected
     clear screen
     play buzzing until done
     show label pick random 1 6 at center of screen by super big pixel
     wait 1 seconds
==================================================================================



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


