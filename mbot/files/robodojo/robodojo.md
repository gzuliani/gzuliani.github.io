[//]: # (encoding=utf-8)

# RoboDojo @Palmanova

_11/18 novembre 2018_

## Introduzione

* cosa è un robot: origine del termine, definizione -- dal dizionario Treccani:

    > Apparato meccanico ed elettronico programmabile, impiegato nell’industria, in sostituzione dell’uomo, per eseguire automaticamente e autonomamente lavorazioni e operazioni ripetitive, o complesse, pesanti e pericolose."

* esempi di robot: androidi, robot casalinghi, industriali, militari, medicali; impieghi nella ricerca scientifica;

* principi di funzionamento e struttura di un robot: interazione con l'ambiente circostante; sensori, controllo, attuatori.

## Premesse

* se si lavora in gruppo, ricordarsi di scambiarsi i ruoli di tanto in tanto.

## Introduzione mBot

* principali sensori e attuatori di mBot;

* mCore, ovvero il circuito di controllo -- consegna della scheda e del cavo usb;

* affinità con Arduino (conviene citare qui la parentela perché in mBlock poi si lavorerà in "modalità Arduino");

* fonti di alimentazione, interruttore per l'accensione;

* indicare la possibile presenza del modulo wireless, nel caso qualcuno noti delle differenze tra la sua scheda e quella mostrata sullo schermo;

* prova di accensione: collegare la scheda al PC con il cavo USB e spostare l'interruttore su ON; la spia di accensione si illumina.

## Primo programma - LED

* breve presentazione dell'ambiente di programmazione mBlock; spiegare la necessità di connettere la scheda al programma;

* cosa sono i LED, dove si trovano su mCore;

* guida alla definizione del primo programma, che accende i due LED di rosso;

* predisposizione dell'ambiente in modalità Arduino per il trasferimento del programma sulla scheda mCore; uso del pulsante "Upload to Arduino" per l'avvio della procedura di trasferimento ignorando al momento il contenuto dell'area di destra della finestra principale;

* *(solo se è disponibile il pacco batterie)* verifica del caricamento del programma spegnendo e riaccendendo la scheda; far notare che ogni volta che si scollega o si spegne la scheda mCore è necessario riconnetterla al programma mBlock prima di poterla riprogrammare (nota: serve il pacco batterie!).

## Esercitazione

* ridurre la luminosità dei LED;

* spegnere i LED dopo qualche secondo;

* far lampeggiare i LED;

* far lampeggiare i LED alternativamente.

## Intermezzo n. 1: sintesi additiva RGB

I LED montati su mCore sono RGB. Spiegare come funziona la sintesi e lasciare ai partecipanti scoprire quali sono i colori secondari; proporre quindi alcune semplici attività:

* simulare un semaforo -- i più volenterosi possono usare i due LED in modo indipendente per regolare il traffico di un incrocio;

* far cambiare colore ai LED ogni secondo, in modo causale;

* *(opzionale)* replicare il lampeggiante della polizia: 4 lampeggi stroboscopici azzurri su un LED (un lampeggio stroboscopico si ottiene accendendo un LED per 20ms, quindi lasciandolo spento per 80ms) mentre l'altro è spento, poi invertire il ruolo dei due LED.

## Intermezzo n. 2: la programmazione

* ruolo del programmatore e del linguaggio naturale;

* il circuito da programmare e il linguaggio binario;

* linguaggi ad alto e basso livello, necessità di un "interprete";

* ruolo del linguaggio intermedio usato da mBlock (C/C++).

## Intermezzo n. 3: hardware, software e firmware

Descrivere brevemente i tre concetti. Per firmware si intende del software integrato stabilmente (firm = stabile) in un componente elettronico, di norma una memoria a sola lettura (ROM/EEPROM).

## Secondo programma - Cicalino *(opzionale)*

Proseguiamo con l'analisi degli attuatori di mCore.

* principio di funzionamento del cicalino;

* emissione di una nota arbitraria.

## Esercitazione

* suono dell'ottava centrale (C4 - C5) della scala diatonica;

* riproduzione della sirena della polizia:

        G4 per 1s
        E5 per 1/6s
        G4 per 1/6s
        E5 per 1/6s

ripetere la sequenza;

* riproduzione di una melodia famosa a partire dallo spartito.

## Prestazioni

mCore non è abbastanza potente da permetterci di far lampeggiare i LED e contemporaneamente riprodurre la sirena della polizia dal cicalino. Ma quanto potente è? Per esempio, non regge il confronto con un sistema "analogo" noto, ovvero l'iPhone 7:

     | mCore          | iPhone 7   | fattore  |
     | (ATMega328)    | (A10)      |          |
     | -------------- | ---------- | -------- |
     | 8 bit          | 64 bit     | x8       |
     | 1 core         | 2 core(1)  | x2       |
     | 16MHz          | 2.34GHz    | x150     |
     | 32KB flash     | 32GB       | x1000000 |
     | 2KB RAM        | 2GB        | x1000000 |

(1) A10 ha 4 core ma vengono usati solo due alla volta; ha pure una GPU hexa-core.

## Programma n. 3 - Pulsante

Individuare il pulsante di bordo, posto sulla parte anteriore della scheda e distinguerlo da quello di reset che si trova invece nei pressi della presa USB.

* blocco `on board button [pressed]` per la verifica dello stato del pulsante;

* blocco `if <> then` per l'esecuzione condizionale di una sequenza di comandi;

* di norma la verifica dello stato del pulsante dev'essere fatta continuamente, per esempio all'interno di un blocco "forever".

## Esercitazione

Estendiamo alcuni dei programmi già studiati in precedenza:

* *(solo se il cicalino è stato affrontato)* far suonare la sirena alla pressione del pulsante;

* far cambiare colore ai LED alla pressione del pulsante;

* accendere i LED solo quando il pulsante è premuto;

* *(opzionale)* come sopra, ma evitando di accendere i LED se sono già accesi o spegnerli se sono già spenti -- servirà una variabile che tiene traccia dello stato dei LED.

## Montaggio di mBot

* consegna del kit da montare;

* rapida analisi dei componenti;

* via al montaggio -- attenzione alle viti!

* verifica del montaggio e delle connessioni dei sensori.

## Programma n. 4 - Motori

Occorre fare attenzione quando si lavora con i motori. Senza i necessari accorgimenti può accadere che il robot si muova non appena il programma è stato trasferito su mCore. Se non siamo pronti, rischiamo di venir presi di sorpresa. Urti e cadute possono danneggiare mBot, quindi usare le dovute cautele. Conviene anche prevedere un modo per arrestare i motori, per non essere costretti a spegnere mBot per fermarlo. La riprogrammazione in queste condizioni può rivelarsi particolarmente scomoda.

* movimento direzionale con il blocco `[run forward] at speed (255)`;

* analizzare i quattro movimenti - come si muovono i due motori?

* far muovere il robot alla pressione del pulsante; il robot si deve arrestare
dopo un intervallo di tempo prestabilito, ad esempio 3s;

* è possibile far percorrere a mBot una distanza prefissata? Accennare al problema della calibrazione, e della dipendenza dallo stato di carica delle batterie;

* controllo indipendente dei motori: blocco `set motor (M1) speed (255)`;

* sperimentare varie velocità sui due motori; verificare la dipendenza tra i raggi di curvatura e il rapporto tra le due velocità (e non sui loro valori assoluti).

## Esercitazione

* disegnare una traiettoria predefinita, ad esempio una S o una M (attenzione: tracciare correttamente una M richiede parecchio tempo!);

* *(richiede la calibrazione del robot)* tracciare delle figure geometriche e/o percorrere una gimcana su un circuito prestabilito;

* realizzare una passeggiata casuale;

* come sopra, usando i LED per indicare la direzione di movimento: verde per l'avanti, rosso per l'indietro, giallo (solo il LED interno, a mo' di freccia) per le rotazioni.

## Programma n. 5 - Sensore ultrasonico

* principio di funzionamento - ecolocalizzazione;

* caratteristiche del sensore;

* *(solo se il cicalino è stato affrontato)* uso del sensore per realizzare un theremin/sensore di parcheggio;

* *(in alternativa al punto precedente)* uso dei LED per indicare la distanza dell'ostacolo -- verde per il remoto, giallo per il distante, rosso per il vicino;

* uso del sensore per arrestare mBot di fronte ad un ostacolo (strategia #1);

* presentazione della strategia di base del programma "scansa-ostacoli": se l'ostacolo è lontano si procede diritti, se è vicino si sterza; uso dei diagrammi di flusso (strategia #2);

* estensione della strategia "scansa-ostacoli": se l'ostacolo è troppo vicino, allora si effettua una sterzata in retromarcia (in questo modo replichiamo la strategia implementata dal firmware di base di mBot -- strategia #3);

* dal diagramma di flusso al programma: trasformazione passo-passo.

* valutare se proporre una strategia "scansa-ostacoli" alternativa: in presenza di un ostacolo si arretra, quindi si ruota (il tempo di rotazione può essere prefissato o casuale -- strategia #4); questa strategia è migliore o peggiore delle due precedenti? ...

## Sfide

* Realizzare un programma che avvicini mBot il più possibile al muro senza toccarlo. Il punto di partenza è a 1m in direzione perpendicolare. A parità di distanza vince il robot più veloce. Usare i LED e/o un segnale sonoro per indicare che mBot ha concluso la sua marcia di avvicinamento;

* Uno alla volta i robot vengono posti al centro di un'area circolare/quadrata delimitata da una barriera e contenente alcuni ostacoli. Vince il robot che riesce ad muoversi all'interno dell'arena per più tempo senza urtare gli ostacoli o la barriera. La velocità dei motori non può scendere sotto una soglia prefissata (es. 70/100). Trascorso un certo lasso di tempo si possono aggiungere ostacoli supplementari secondo delle regole prestabilite. Può diventare il banco di prova delle varie strategie presentate.

## Programma n. 6 - Inseguimento della linea

* principio di funzionamento dei sensori rifettivi;

* valore ritornato dal sensore di linea;

* algoritmo "naif" dell'inseguitore di linea;

* algoritmo con memoria dell'inseguitore di linea;

* sfida di velocità su circuito;

* *(opzionale)*: sistema di mantenimento della distanza di sicurezza: un inseguitore di linea procede sul circuito a velocità ridotta, un altro lo segue rispettando una distanza minima prefissata.

## Conclusioni

* retrospettiva delle due giornate;

* le tre leggi della robotica;

* saluti.

## Altri aspetti non considerati

### Controllo di mBot da mBlock

Tutti gli esempi e le esercitazioni proposte funzionano in modalità Arduino, ovvero caricando il programma direttamente sul robot con il comando "Upload to Arduino". Questo modo di lavorare, che ha l'indubbio vantaggio di produrre alla fine un robot completamente autonomo, rende d'altra parte lo sviluppo piuttosto disagevole sotto due punti di vista: innanzitutto richiede che mBot sia connesso fisicamente al computer tramite il cavo USB, in secondo luogo i tempi di compilazione e caricamento del prorgramma non sono trascurabili.

È tuttavia possibile controllare mBot direttamente dall'ambiente mBlock caricando sul robot l'apposito firmware (comando "Upgrade Firmware" del menu "Connect" di mBlock v. 3.x o il comando "For mBlock" del sottomenu "Update Firmware (USB)" del menu "Connected" di mBlock v. 4.x) e preparando un programma Scratch convenzionale.

Una volta che il firmware è stato trasferito con successo è possibile scollegare mBot dal computer e connetterlo a mBlock in modalità wireless. A questo punto mBot diventa di fatto un rover controllato da remoto.

### Hardware

Il connettore tra la presa USB e la presa 4 è SPI ([Serial Peripheral Interface](https://en.wikipedia.org/wiki/Serial_Peripheral_Interface)).

### Alimentazione

Da [Lipo battery charging specs for mbot](https://forum.makeblock.com/t/lipo-battery-charging-specs-for-mbot/1346/33):

> mBot can operate from AA batteries (4 x1.5V) or LiPo battery (1 x 3.7V).
>
> mBot needs +5V internally to operate, mBot power supplied via a TP3605
> switching regulator (U1). This regulator will supply the correct voltage to
> mBot provided there is sufficient energy in either the AA cells or the LiPo
> cell. mBot will cease to operate once the under-voltage threshold of the
> TP3056 is reached. The mBot motors are supplied directly from the battery,
> not via the regulator. This means that as the batteries deplete the motor
> speed will decrease.
>
> mBot will not charge the AA cells connected to JP2 (barrel).
>
> mBot will charge the LiPo cell connected to P1 (JST).
>
> mBot has an onboard charger TP4056 (U2) that will charge the LiPo battery
> from the USB connector.
>
> The mBot onboard charger has two LED's just near the mBot on/off switch, a
> solid red one to indicate charging and a solid green one to indicate fully
> charged. If the green LED flashes then there is a problem with the LiPo cell.
>
> You may have AA cells and LiPo cell connected at the same time, mBot will
> deplete the AA cells first and then switch over to the LiPo cell.

## Spunti per esercitazioni supplementari

### Telecomando

* guida manuale di mBot tramite i tasti direzionali del telecomando;

* come sopra, usando i tasti numerici per selezionare la velocità.

### Cicalino

* realizzare un metronomo usando il cicalino;

* usare una variabile per realizzare un suono a frequenza crescente (sweep), per esempio la sirena dei vigili del fuoco americani; da [www.mblock.cc](http://www.mblock.cc/example/fire-engine-sound-effects/):

    > Online data suggests that, the fire engine siren’s low frequency sound is
    > between 650Hz and 750Hz, and its high frequency sound is between 1450Hz
    > and 1550Hz. The siren sound is generated by repeating the following
    > pattern: the low frequency sound amplifies to a high frequency sound in
    > 1.5 seconds, and then drops back to the lower frequency in 3.5 seconds.
    > Therefore, the fire engine siren sounds can be programmatically simulated
    > as follows:
    >
    > set the low frequency to be 700Hz, and then set the high frequency sound
    > to be 1500HZ, repeatedly playing the buzzer in a range from 700Hz to
    > 1500Hz and then back to 700Hz. The ratio of amplification time to the
    > drop time is 1.5:3.5, which is 3:7, so the ratio of frequency
    > amplification to the drop needs to be 7:3. Then, by tuning the sound time
    > and amplification v.s. drop’s amplitude, the fire engine siren is
    > simulated.
    >
    >     forever
    >       set [f] to [700]
    >       repeat until <(f) > [1500]>
    >         play tone on note (f) beat (12)
    >         change [f] by (35)
    >       set [f] to [1500]
    >       repeat until <(f) < [700]>
    >         play tone on note (f) beat (12)
    >         change [f] by (-15)

### Fotoresistore

* Da [TechMonkeyBusiness](http://www.techmonkeybusiness.com/robotics-1d-mbot-sensors.html):

    > Is your mBot afraid of the dark? No? Well it - should be. There's monsters
    > out there. Use the on-board light sensor to make your mBot speed up to get
    > out of dark places quickly.

* usare il sensore luminoso per realizzare un inseguitore di luce (falena) o un rifuggi-luce (scarafaggio).

### Sensore ultrasonico

* Da [learn.makeblock.com](http://learn.makeblock.com/en/robot-kits/mbot/the-ultrasonic-sensor/)
   > Can you write a program that follows an object? So if the object is too
   > close, the robot goes backwards, if the object is far away, it goes
   > forward, and if the object is not near or far, the robot stops.
   >
   > Can you change your program from question 2, to make the robot move at
   > different speeds?

* usare il sensore ultrasonico per raggiungere l'oggetto più vicino.

### Sensore di linea

* usare il sensore di linea come antifurto; porre mBot su una superficie chiara e suonare un allarme se il sensore di linea cambia valore. Come si può ingannare l'antifurto?

* usare il sensore di linea come sensore anti-caduta (funziona solo su tavoli dalla superficie chiara);

* usare il sensore di linea per inseguire il bordo della linea (idea: mantenere un sensore sulla linea, l'altro sullo sfondo);

* usare il sensore di linea per realizzare una passeggiata casuale entro un'area delimitata (rasaerba);

* usare il sensore di linea per inseguire una linea interpretando i tratteggi come particolari comandi (es. cambio velocità, parcheggio, ...).

### Riferimenti

* sez. [mBot](https://gzuliani.github.io/index.html#mbot) dei miei appunti;

* sez. [Examples](http://www.mblock.cc/example/introduction/) sul sito ufficiale.
