

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

# Lezione n.8 20220210

Altoparlante

Emettere suoni di frequenza specifica

Display

test/tabella/grafico sono mutuamente esclusive
le 8 etichette sono sovraimposte e funzionano su tutte le modalità
orientando opportunamente il display (right) col testo big si possono fare le emoticon vecchia maniera... insomma, non sono bellissime...

display: origine in altro a sx
display: la dimensione del testo è globale, non si possono visualizzare due segmenti a dimensioni/colori diverse
display: autoscrolling (provare a stampare i numeri da 1 a 20 uno per riga)
display: dedurre quante righe di testo per ognuna delle 4 dimensioni (small:8, middle:6, big:4, super-big: poco meno di 3)

line chart: disegna un grafico tra 0 e 100 (rimappati su 0-128), scroll automatico, distanza tra punti configurabile, colore pure, spessore linea no

bar chart: unica barra al centro, mappata tra 0 e 100
per avere più barre, cambiare colore; se si torna a un colore già usato, viene aggiornata la barra vecchia

table: disegna una tabella, la più piccola che contiene tutti i dati (comunque non oltre 4x3); dimensione del testo fissa a middle

etichette: 8 sovraimpresse, su testo, grafico o tabella
ognuna con dimensione e colore del testo propri
utili per posizionare del testo al di fuori del flusso normale

luminosità come chart e bar
modulare la velocità di aggiornamento col tempo (line chart anche con la risoluzione)
anche in questo caso la reattività in modalità upload è molto più alta della live (ma meno comoda)

MOTORI

mBot2 Shield se non è già presente lo si carica come estensione di CyberPi
-> si ottengono i comandi di controllo dei motori con encoder
-> più un'altra estensione per servi, motori DC e tutto ciò che si può collegare allo shield

gli encoder hanno una accuratezza di 1°, la rotazione < 5°
si può vedere l'effetto in LIVE con il trucco della variabile nel persempre

occhio, parte subito dopo l'UPLOAD!!
muoversi solo dopo che si è premuto il tasto B ("attendi fino a quando" come prima istruzione)

movimenti base: avanti, indietro, rotazione (sul posto)
movimento a RPM/percentuale di potenza, ev. per un tempo prefissato
avanti/indietro con distanza
rotazione con gradi
turn left 90° vs turn left at 50 RPM for 1 sec

tartaruga! proviamo il quadrato, poi il pentagono (lato 50cm)
passeggiata casuale con LED
gimcana

se i movimenti non tornano, calibrare (precisione encoder, giochi meccanici, attriti, pneumatici consumati...)

-------------- fino qui -------------------

# Lezione n. 9

disegnare una circonferenza? o semplicemente una curva?
per fare andare avanti, un motore positivo, l'altro negativo
traiettoria quadrato/pentagono(!)
passeggiata casuale (con indicatore di movimento)
gimcana
uso degli encoder come sensori
calibrazione degli encoder, anche qui (tolleranze meccaniche, giochi, diametro ruote, ...)!

SENSORE ULTRASONICO

caricare l'estensione di CyberPi dedicata
il primo indice dei blocchi si riferisce al primo sensore in catena (mBuild è una daisy-chain, ce ne potrebbero essere di più)

visto da davanti TX a sx, RX a dx
range 5-300, +/-5%

* principio di funzionamento - ecolocalizzazione;
* caratteristiche del sensore;
* uso dei LED per indicare la distanza dell'ostacolo -- verde per il remoto, giallo per il distante, rosso per il vicino;
* uso del sensore per realizzare un theremin/sensore di parcheggio;
* uso del sensore per arrestare mBot di fronte ad un ostacolo (strategia #1);
* presentazione della strategia di base del programma "scansa-ostacoli": se l'ostacolo è lontano si procede diritti, se è vicino si sterza; uso dei diagrammi di flusso (strategia #2); 50/0 | 0/-50 RPM
* estensione della strategia "scansa-ostacoli": se l'ostacolo è troppo vicino, allora si effettua una sterzata in retromarcia (in questo modo replichiamo la strategia implementata dal firmware di base di mBot -- strategia #3) -70/20 | -20/70 RPM;


# Lezione n. 10

[competenze trasversali, imprenditorialità]

# Lezione n. 11 (20220222)


SENSORE DI LINEA

principio di funzionamento
ruolo dei 4 led vicino ai sensori -> luce artificiale per diminuire le interferenze di quella ambientale -> richiede calibrazione (ancora!)

> * Double-press: When the button is double-pressed, Quad RGB Sensor starts to learn the background and line for line following.
>   Place the light sensors on the background of the line-following track map and double-press the button. When you see the LEDs indicating the line-following state blink quickly, sway the sensors from side to side above the background and line until the LEDs stop blinking. It takes about 2.5 seconds. The parameter values obtained are automatically stored. If the learning fails, the LEDs blink slowly, and you need to start the learning again.
> * Long-press: When the button is long-pressed, Quad RGB Sensor switches the color of the fill lights. Generally, you don’t need to change the color. The color is set automatically after the learning is complete.

calibrazione con un doppio click del pulsantino
per b/n di norma non serve, se no far passare i sensori sulla linea (fuori-dentro-fuori) fino a quando non smette il lampeggio
calibrare il sensore sul colore più chiaro da considerare linea
se tutto ok: led sulla linea spenti, fuori linea accesi

calibrazione alternativa: calibro sul nero, poi cambio a mano il colore dei led verificando sperimentalmente se il robot riconosce anche i tratti colorati; di solito la luce blu è quella più efficace.

caricare l'estensione di CyberPi dedicata (a febbraio 2022 è ancora in beta!)

in modalità line/background non considera il colore

codifica (B=background, L=line):

lr
BB 00 0
BL 01 1
LB 10 2
LL 11 3

logica contraria all'accensione dei led: sono sulla riga, valore 1, led spento; sono fuori dalla riga, valore 0, led acceso!

idem per i 4 (1 sulla linea, 0 fuori dalla linea, nell'ordine l2l1r1r2)
i laterali si usano per determinare diramazioni

inseguimento di linea naive (cerco di tenere i due sensori sulla riga, quando esco torno indietro)
 con rotazioni: oscilla a destra e sinistra
 con curva a rapporto 1:5: oscilla avanti e indietro, anche a 20 RPM
inseguimento di linea "furbo" (quando esco continuo il movimento che facevo prima di uscire): mi posso spingere ben oltre i 50RPM; questo per come è fatto il circuito! [NON AFFRONTATO PER MANCANZA DI TEMPO]

>>> l'algoritmo di inseguimento diventa un blocco a sé stante, parametrico sulla velocità (o usa una variabile globale) <<<

inseguimento di linea + stop (con led rossi) se distanza < 20
rallento (dimezzo la velocità) se 40 < distanza < 20 [conviene definire il blocco "segui linea a velocità (speed)] [NON AFFRONTATO PER MANCANZA DI TEMPO]

[QUESTO ANCHE NO]
deviation: quanto sono/mi sto allontanando dalla linea (-100 la linea è alla mia destra, 100 la linea è alla mia sinisra)
si può usare per modulare la curva: se deviation > 0 v.sinistra va diminuita, v.destra aumentata, così giro a sinitra;
se deviation < 0 v.sinistra va aumentata, v.destra diminuita, così giro a destra; es:
v.sinistra = 50 - k * deviation
v.destra = -(50 + k * deviation)
k modula l'effetto

riconoscimento dei colori sulla linea (sensore L1/R1 a scelta oppure metterli in or):

verde -> emetti un suono
giallo -> accendi i led (da spegnere su black)
blu -> rallenta
rosso -> torna indietro (gira 180° + vai avanti di un tot (per uscire dal rosso))

------------ fino qui ---------------

L'ultima lezione sarà dedicata al ripasso del sensore di linea e alla prova finale, non si vedrà nient'altro

=====================================

controllo del tilt: se rollio supera i 3° si accendono i led di arancione e si rallenta

LAN

dovrebbe funzionare anche senza Router WiFi, la rete la creano le CyberPi tra loro

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
