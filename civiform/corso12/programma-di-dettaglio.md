# Coding e robotica per l'innovazione sociale

_Argomenti delle lezioni_

**Nota**: il corso è indirizzato ad insegnanti della scuola secondaria di primo grado.

## Lezione n.1 - Introduzione, 18/01/2022

* presentazione del corso
* inquadramento del coding nello sviluppo del software
* ciclo di sviluppo del software: analisi, progettazione, programmazione, collaudo
* algoritmi e linguaggi di programmazione
* coding e pensiero computazionale
* Scratch: storia, primi approcci

**Nota**: poiché il disbrigo delle pratiche burocratiche di inizio corso hanno richiesto quasi un'ora non c'è stato tempo a sufficienza per completare la presentazione dell'ambiente di sviluppo di Scratch che è stato per questa ragione rimandato alle lezioni successive.

## Lezione n.2 - Narrativa, 20/01/2022

Per introdurre gradualmente l'ambiente di sviluppo di Scratch mi sono ispirato ad un progetto proposto da un collega in un corso precedente: realizzare una presentazione (slideshow) che descriva una gita a Cividale. È un progetto che gli insegnanti potrebbero proporre ai propri studenti.

* breve panoramica dell'ambiente di programmazione di Scratch
* ruolo dello sfondo in Scratch
* predisposizione degli sfondi a partire da immagini scaricate dalla rete
* aggiunta di una didascalia con lo strumento **Testo**
* didascalie modificabili: differenza tra immagini bitmap (raster) e vettoriale
* come rimuovere o rendere invisibile **Sprite1**
* avanzamento temporizzato delle immagini: anche lo sfondo può ospitare script
* definizione della sequenza per nome: uso dei blocchi `switch backdrop to ()` e `wait () seconds`
* il tempo di permanenza di una diapositiva è ripetuto n volte
* definizione della sequenza per posizione in "Backdrops": uso del blocco `repeat ()` con `next backdrop` e `wait () seconds`
* il numero di ripetizioni è pari al numero di sfondi diminuito di 1, se no alla fine ricompare il primo sfondo in lista
* navigazione da tastiera: rimuovere il blocco `repeat ()` e aggiungere un `when [space] key pressed` seguito da un `next backdrop`
* [evitare di passare allo sfondo precedente al primo e/o successivo all'ultimo]
* didascalie dinamiche (es. in dissolvenza): i testi diventano degli sprite che si registrano all'evento `when backdrop switches to []` per mostrarsi/nascondersi in funzione dello sfondo che sta per apparire -- gli elementi grafici delle immagini sono statici
* differenza tra la posizione del testo nello sprite e la posizione dello sprite nello stage
* realizzazione della dissolvenza per mezzo dell'effetto **Ghost**
* utilizzo degli sprite (es. **Nano**) come guida che fornisce informazioni relative all'immagine mostrata
* programmazione di un breve dialogo tra sprite (es. **Nano** e **Giga**) sincronizzato con le pause

## Lezione n.3 - Grafica della tartaruga, 25/01/2022

### Hardware

* cenni sulla storia dei calcolatori elettronici
* mostrare le valvole, i transistor, gli integrati, alcune CPU moderne
* alcuni dei sistemi più celebri:
    * ENIAC (1947) 20.000 valvole, un guasto ogni due giorni
    * ELEA 9003 (1959): realizzato da Olivetti, 300.000 transistor
    * PDP11 (1970): circuiti integrati, sistema in time-sharing
    * APPLE II (1977): il primo home computer 
    * ALTAIR (1975): primo computer personale; 450$ di allora, 2250$ attuali
    * PC IBM (1981): il capostipite dei computer odierni; 1500$ di allora, 4500$ attuali
* breve introduzione all'architettura dei calcolatori

### Poligoni

* caricamento dell'estensione **Penna**
* disegno di un quadrato:

        when 🏳 clicked
        set rotation style [left-right]
        set size to (40) %
        erase all
        pen down
        repeat (4)
          move (100) steps
          turn ⭯ (90)
          wait (1) seconds

* cambiare colore e spessore alla penna            
* interrompere il programma a metà e riavviarlo, cosa accade?
* importanza della fase di inizializzazione: impostare le condizioni iniziali corrette, in questo caso posizione e direzione di partenza con i blocchi `go to x: () y: ()` e `point in direction ()`
* il blocco `go to x: () y: ()` aggiorna automaticamente il valore delle coordinate quando sposto uno sprite nello stage
* disegno del triangolo: 3 volte 120
* generalizzazione dell'algoritmo pensando al caso del pentagono e dell'esagono
* l'angolo di rotazione è dato dal rapporto tra l'angolo giro e il numero di lati da disegnare
* uso dell'operatore `() / ()` per esplicitare questa relazione
* disegno dell'icosagono (20 lati): 100 passi è troppo; procedendo per tentativi si giunge a determinare la lunghezza del lato e la posizione iniziale ottimali: 50 e (0, -160)
* ridurre/eliminare la pausa tra i lati
* il numero di lati compare in due posti: nel blocco `repeat ()` e nell'operatore `() / ()`; conviene introdurre la variabile **Num lati** per esplicitare il significato di questo numero
* **Sprite1** chiede il numero di lati all'utente -- uso dei blocchi `ask`/`answer` per richiedere dati all'utente
* il fumetto della domanda non si vede bene: spostare lo sprte al centro dello stage prima di porre la domanda, rimetterlo subito dopo nella posizione iniziale precedentemente individuata
* alla seconda esecuzione del programma si nota la traccia della penna che dal centro dello stage va verso la posizione iniziale: uso del blocco `pen up` per rimuoverla
chiede ma non usa il valore
* uso del blocco `join () ()` per combinare frammenti di testo: `say (join (Ora disegno un poligono di ) (join (Num lati) ( lati...))) for (2) seconds`
* rifiutarsi di disegnare un poligono di più di 20 lati: uso del blocco `if <> then else`
* cicli nidificati: disegno di poligoni in successione incrementando il numero di lati di uno partendo da 3 e giungendo fino a 20
* disegno dei poligoni con colori diversi: uso del blocco `change pen (color) by (10)`
* applicazione del cambio colore dopo ogni lato

### Luci psichedeliche [argomento non affrontato a lezione]

* disegno dei soli vertici dei poligoni: iniziare con una penna su con spessore "importante" e, in corrispondenza del punto iniziale di ogni lato, comandare un `pen down` subito seguito da un `pen up`
* nascondere **Sprite1** e inserire i due cicli nidificati in un `forever`; attivare la modalità **Turbo** dal menu **Edit** o cliccando la bandierina verde tenendo premuto il tasto **Shift**

### Stelle [argomento non affrontato a lezione]

* la tartaruga deve tornare indietro dopo aver raggiunto uno spigolo, ma di quanto?
* caso del pentacolo: gli angoli al centro di un pentagono sono 5, quindi 360/5=72°; gli angoli degli spigoli sono angoli alla circonferenza, quindi ampi la metà di quelli al centro, dunque 36°; il cambio direzione è quindi pari a 180-36=144°
* la lunghezza dei segmenti dev'essere pari ad almeno 200/250 passi
* una buona posizione di partenza potrebbe essere (-passi/2, +/-40)
* per avere la punta all'insù basta cambiare verso di rotazione
* interessanti osservazioni si possono fare ragionando sulla differenza tra le stelle a punte pari e quelle a punte dispari

### Ghirlande  [argomento non affrontato a lezione]

* partire dal programma della stella
* impostare un numero di lati casuale, compreso tra 10 e 100
* attendere 3 secondi tra un disegno e l'altro, quindi iniziarne uno nuovo
* applicare ad ogni segmento uno spessore e un colore diverso (casuale)
* provare in modalità Standard e **Turbo**

### Spirale quadrata

* proporre l'algoritmo e lasciare che i partecipanti lo codifichino in autonomia:

        imposta PASSI a 10
        vai a 0,0
        ripeti
          punta verso destra
          per due volte:
            muoviti di PASSI passi
            gira di 90° verso sinistra
          aumenta PASSI di 10

* modificare il programma in modo che disegni una spirale esagonale (soluzione: 3+3 a 60°, PASSI=6 per proseguire a incrementi di 6)

### Spirale curva [argomento non affrontato a lezione]

* il ciclo interno non serve
* PASSI parte da 1 e cresce a incrementi di .1/.5 passi
* le rotazioni hanno ampiezza di 10° gradi

### Passeggiata casuale [argomento non affrontato a lezione]

* caricare lo sprite **Rocketship**
* impostare il programma di massima:

        when 🏳 clicked
        erase all
        pen down
        forever
          move (10) steps
          turn ⭯ (15)
          if on edge, bounce

* modificare i numero di passi e l'angolazione (es. 15, 5°)
* il razzo si muove di lato; ruotare tutt i costumi
* cambiare il colore e lo spessore della traccia
* provare il programma in modalità **Turbo**

### Passeggiata casuale con timbro [argomento non affrontato a lezione]

* predisporre uno sprite con un quadrato come costume

        when 🏳 clicked
        erase all
        pen down
        set pen (color) to (...)
        forever
          glide (1) secs to (random position)

* aggiungere un blocco `stamp` prima dello spostamento
* duplicare lo sprite e rilanciare
* l'effetto **Turbo** in questo programma non si percepisce per via del comando `glide (1) secs`

**Nota**: i cicli nidificati hanno creato notevoli difficoltà, tant'è che è stato necessario rivederli nel dettaglio nella lezione successiva.

## Lezione n.4 - Videogioco, 27/01/2022

### Blocchi personalizzati

* veloce ripasso dei cicli nidificati
* utilizzo di un blocco personalizzato per disegnare un poligono e nascondere il ciclo interno:
    * passo 1: definizione del blocco personalizzato `disegna quadrato`
    * passo 2: definizione del blocco personalizzato parametrico `disegna quadrato di lato (passi)`
    * passo 3: definizione del blocco personalizzato parametrico `disegna poligono con (num lati) lati di lunghezza (passi)`
* riflessioni sull'uso dei blocchi personalizzati: cenni ai livelli di astrazione e all'occultamento dei dettagli implementativi

### Mondo sommerso

* eliminare **Sprite1**
* aggiungere lo sprite **Diver2** e rinominarlo in "Sub"
* ridimensionare il nuovo sprite se necessario
* illustrazione delle principali tecniche di controllo degli sprite:
    * **attraverso il mouse**: `point towards (mouse-pointer)` e `move (5) steps` -- instabilità dello sprite quando raggiunge il puntatore del mouse e possibile soluzione
    * **tastiera /1**: `turn () degrees`  e `move (5) steps` -- richiede lo stile di rotazione `all around` per esplicitare la direzione del movimento
    * **tastiera /2**: movimento cartesiano lungo gli assi x/y con i blocchi `change x by (5)` e `change y by (5)` -- utilizzo del blocco `point in direction (90)` e lo stile di rotazione `left-right` per armonizzare l'aspetto dello sprite con gli spostamenti
* caricare lo sfondo **Underwater 2**
* posizionamento dello sprite al centro dello stage all'inizio del gioco
* aggiungere lo sprite **Starfish**, rinominarlo in "Stella" e posizionarlo in basso a destra, alle coordinate (-200, -140) opportunamente rimpicciolito
* gestione della collisione tra Sub e Stella: Stella ringrazia di essere stata salvata e sparisce
* serve un blocco `show` all'inizio per assicurarsi che Stella all'inizio sia visibile
* uso dei costumi: inizialmente Stella indossa il costume **starfish-b**, quando viene salvata passa temporaneamente al costume **starfish-a**
* moltiplicare le stelle da salvare con un ciclo `hide`, `wait (3) seconds`, `go to (random position)` e `show`
* [limitare l'area di competenza di Stella al solo fondale -- uso del blocco `goto x: () y: ()` e due istanze dell'operatore `pick random () to ()` definiti su intervalli opportuni]
* punteggio: introdurre la variabile **Stelle salvate**
* incremento e inizializzazione della variabile
* aggiungere lo sprite **Shark 2** ("Squalo"); adattare la dimensione agli altri sprite
* lo Squalo si muove autonomamente:

        when 🏳 clicked
        go to x: (-170) y: (120)
        forever
         move (3) steps

* utilizzo del blocchi `if on edge, bounce` e `set rotation style [left-right]` per rendere il movimento continuo
* impostazione della direzione tra 30 e 60° per coprire tutto lo stage
* parallelismo in Scratch: definizione di un nuovo script per l'animazione di Squalo:

        when 🏳 clicked
        forever
          switch costume to [shark2-a]
          wait (pick random (1) to (3)) seconds
          switch costume to [shark2-b]
          wait (.2) seconds

* collisione Sub/Squalo:

        when 🏳 clicked
        forever
        set rotation style [left-right]
        forever
          ...
          if <touching [Squalo]?> then
            set [brightness] effect to (60)
            wait (.1) seconds
            set [brightness] effect to (0)
            say [Ahia!] for (2) seconds
            change [Stelle salvate] by (-1)

* fare in modo che il punteggio non diventi negativo
* far apparire Squalo dopo 10 secondi dall'inizio del gioco
* far apparire Stella dopo un intervallo di tempo variabile dopo che è stata salvata
* aggiungere la variabile **Tempo rimanente** e impostarla a 60
* decrementare **Tempo rimanente** ogni secondo
* arrestare il gioco quando la variabile si azzera

## Lezione n.5 - Cloni e liste, 01/02/2022

### Mondo sommerso

* inviare un messaggio agli sprite all'esaurimento del gioco
* Squalo e Stella si nascondono alla ricezione del messaggio di fine partita
* predisporre uno sfondo di fine partita e caricarlo al momento opportuno

### Lucciole sincronizzanti

* realizzazione del volo casuale della lucciola con i blocchi `move (2) steps`, `turn (pick random (-3) to (3)) degrees` e `if on edge, bounce`
* implementazione dell'orologio interno della lucciola e lampeggio al raggiungimento del massimo
* creazione dello sciame di 25 lucciole per clonazione
* sincronizzazione basato sui messaggi:

        when I receive [lampeggio]
        if <(conteggio) > (0)> then
          if <(conteggio) < (50)> then
            change [conteggio] by (-1)
          if <(conteggio) > (50)> then
            change [conteggio] by (1)

### Lista della spesa - parte 1

* definire una variabile lista **Spesa**
* quando cliccato **Sprite1** dice se la lista è vuota -- uso del blocco `length of [Spesa]`
* aggiunta manuale di elementi alla lista (icona **+** in basso a destra)
* **Sprite1** enuncia tutti gli elementi se la lista non è vuota -- algoritmo di scansione lineare
    * introdurre la variabile ausiliaria **Posizione**
    * inizializzare la variabile a `1` al di fuori del ciclo
    * predisporre un ciclo di ripetizioni pari alla lunghezza della lista
    * uso del blocco `item (Posizione) of [Spesa]` per accedere all'i-esimo elemento
    * incrementare **Posizione**
* evitare di aggiungere doppioni alla lista: l'aggiunta va fatta programmaticamente
* aggiungere un pulsante-sprite **Aggiungi**; al click chiedere all'utente il nome dell'elemento da aggiungere; se è già in lista avvisare l'utente che non serve, altrimenti aggiungerlo in coda

## Lezione n.6 - Liste, 03/02/2022

### Lista della spesa - parte 2

* aggiungere un pulsante-sprite **Rimuovi**; al click chiedere all'utente il nome dell'elemento da rimuovere; se non è in lista avvisare l'utente che non si può procedere, altrimenti eliminare l'elemento indicato dalla coda
* l'eliminazione di un elemento in Scratch avviene solo per posizione, non per nome: bisogna risalire prima alla posizione occupata dall'elemento utilizzando il blocco `item # of (thing) in [Spesa]`; se il blocco ritorna un numero non nullo allora l'elemento è in lista e si trova nella posizione indicata dal blocco
* aggiungere un pulsante-sprite **Svuota**; al click, previa conferma, svuota la lista

### Agenda telefonica

* trasformare il programma Lista della spesa in un'agenda telefonica utilizzando due liste parallele: la prima contiene i nomi, la seconda i numeri di telefono; l'aggiunta di un contatto necessita di due informazioni, il nome e il numero di telefono; la rimozione di un contatto avviene per nome (vanno però cancellati nome e relativo numero di telefono); **Svuota** deve avere effetto su entrambe le liste
* aggiungere un pulsante-sprite **Cerca**; al click chiedere all'utente il nome del contatto di cui si vuole conoscere il numero di telefono -- uso del blocco `item # of (answer) in [Nomi]` per ricavare l'indice del contatto all'interno del blocco `item  () of [numeri]` per risalire al numero
* aggiungere un pulsante-sprite **Indovina**; al click propone un numero di telefono e l'utente immette il nome del contatto che ha quel numero; rispondere in modo appropriato a seconda se il nome è quello giusto o se invece non corrisponde

### Algoritmi applicati alle stringhe [argomento non affrontato a lezione]

* cercare un carattere all'interno di una stringa (scansione lineare/blocco `<(apple) contains (a) ?>`)
* contare le occorrenze di un carattere presenti all'interno di una stringa
* contare le occorrenze di un insieme di caratteri, ad esempio le vocali
* rovesciare una stringa
* verificare se due stringhe sono palindrome (richiede l'uso di due indici)
* realizzare il cifrario di Cesare (difficile!)

### Introduzione alla robotica

* definizione di robot
* esempi convenzionali e non di robot
* principi di funzionamento dei robot
* sensori, attuatori, controllo

### CyberPi

* introduzione alla scheda CyberPi
* navigazione nel menu del sistema operativo:
    * joystick per muoversi
    * pulsante B per confermare
    * pulsante A per uscire
    * pulsante Home per richiamare il menu
* breve panoramica di mBlock e differenze rispetto a Scratch
* sezione "Devices"
* connessione a CyberPi
* programmazione di CyberPi in modalità **Live**
* esempi di interazione CyberPi/Sprite attraverso messaggi e variabili
    * spostamento di uno sprite con il joystick di CyberPi
    * click su uno sprite per far emettere un suono a CyberPi
* acquisizione di dati tramite il microfono e il fotoricettore di CyberPi -- entrambi i sensori forniscono una lettura adimensionale nell'intervallo 0÷100
* uso del blocco `say ()` per visualizzare costantemente il livello di luminosità registrato dal fotoricettore di CyberPi

## Lezione n.7 - CyberPi, 08/02/2022

### Sensori: fotoricettore e microfono

* possibili utilizzi del fotoricettore:
    * regolazione automatica del contrasto di un display
    * interruttore crepuscolare (accensione automatica delle luci)
    * scelta della posizione che ottimizza l'irraggiamento
* possibili utilizzi del microfono:
    * effettuare registrazioni ambientali
    * riconoscimento di comandi vocali
    * attivazione di comandi battendo le mani

### Sensori: accelerometro e giroscopio

* principio di funzionamento
* acquisizione e riconoscimento dei dati grezzi di accelerazione e velocità angolare
* difficoltà intrinseca nell'interpretazione dei dati acquisiti
* brevi cenni sul "sensor fusion"
* illustrazione dei blocchi dell'area **Motion Sensing**:
    * famiglia `<[tilted forward] ?>`
    * famiglia `<[wave up] detected?>` (`rotate`, `freefall`, `shaken`, …)
    * `(shaking strength)`, che ritorna un valore nell'intervallo 0÷100
    * `(waving direction)`, che ritorna la direzione verso la quale CyberPi è scosso
    * `(waving speed)`, che ritorna un valore nell'intervallo 0÷100
    * `([titled forward] angle°)`, che ritorna l'angolazione assunta da CyberPi rispetto alla direzione indicata
* far fare un salto allo sprite **Panda** in corrispondenza alla condizione `wave up`
* far tremare lo sprite in corrispondenza alla condizione `shaken`
* necessità dell'azzeramento degli angoli dedotti dai dati del giroscopio
* uso del blocco `control (Panda) to follow Cyperpi with sensitivity (low(0.2))` per controllare la posizione di uno sprite con l'orientamento di CyberPi -- verificare la necessità di una calibrazione periodica
* procedura di calibrazione:
    * puntare CyberPi al centro dello stage
    * cliccare il joystick
    * in corrispondenza del click del pulsante centrale del joystick spostare **Panda** al centro dello stage ed azzerare gli angoli giroscopici

### Attuatori: striscia LED

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

# Lezione n.8 - CyberPi e mBot, 10/02/2022

Altoparlante

Emettere suoni di frequenza specifica

Display

test/tabella/grafico sono mutuamente esclusive
le 8 etichette sono sovraimposte e funzionano su tutte le modalità
orientando opportunamente il display (right) col testo big si possono fare le emoticon vecchia maniera… insomma, non sono bellissime…

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

se i movimenti non tornano, calibrare (precisione encoder, giochi meccanici, attriti, pneumatici consumati…)

-------------- fino qui -------------------

# Lezione n. 9

disegnare una circonferenza? o semplicemente una curva?
per fare andare avanti, un motore positivo, l'altro negativo
traiettoria quadrato/pentagono(!)
passeggiata casuale (con indicatore di movimento)
gimcana
uso degli encoder come sensori
calibrazione degli encoder, anche qui (tolleranze meccaniche, giochi, diametro ruote, …)!

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
 (provare a ridurre la velocità in retromarcia e/o durante le curve? fare una retromarcia curvando dalla parte opposta?)
inseguimento di linea "furbo" (quando esco continuo il movimento che facevo prima di uscire): mi posso spingere ben oltre i 50RPM; questo per come è fatto il circuito!

>>> l'algoritmo di inseguimento diventa un blocco a sé stante, parametrico sulla velocità (o usa una variabile globale) <<<

inseguimento di linea + stop (con led rossi) se distanza < 20
rallento (dimezzo la velocità) se 40 < distanza < 20 [conviene definire il blocco "segui linea a velocità (speed)]

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

controllo del tilt: se rollio supera i 3° si accendono i led di arancione e si rallenta

LAN

dovrebbe funzionare anche senza Router WiFi, la rete la creano le CyberPi tra loro

## Appendice

### Il pacco rubato

La storia interattiva che non ho avuto modo di affrontare è una replica fedele del progetto “Il pacco rubato” realizzato da Enrico Colombini e raccolto nel libro **Coding - programmare è un gioco** edito da DeAgostini. Segue la sequenza passo-passo per realizzare il programma:

* il punto di partenza è un semplice dialogo tra Stella (sprite **Starfish** con il costume dall'aspetto preoccupato) e l'ispettore Granchi (sprite **Crab**); il numero tra parentesi indica la durata del fumetto e la conseguente pausa del compagno:
    * Stella: Ispettore Granchi, mi aiuti! (3)
    * Granchi: Cosa è successo? (2)
    * Stella: Mi hanno rubato il regalo di compleanno! (4)
    * Granchi: Farò delle indagini (3)
* far muovere di tanto in tanto le chele a Granchi sfruttando il parallelismo di Scratch;

Si entra ora nella parte interattiva della storia:

* quando si clicca Stella:
    * Granchi: Stella, è sicura di non averlo perso? (4)
    * Stella: Certo che sono sicura! (2)
* Stella deve notificare a Granchi che è stata cliccata!
* riflettere sulla differenza tra `broadcast` e `broadcast [] and wait`;
* cliccare su Granchi inizialmente non ha effetto sul gioco, sfruttiamo questo evento per suggerire al giocatore che deve cliccare gli altri personaggi con il blocco `thinks [Devo interrogare tutti i testimoni…] for (4) seconds`; Granchi risolverà il mistero solo dopo che il giocatore avrà cliccato tutti gli altri protagonisti del racconto;
* aggiungere lo sprite **Fish**, cambiarne il nome in Branchia e farlo nuotare lentamente a destra e sinistra; quando viene cliccato ha luogo il seguente dialogo:
    * Granchi: Professoressa Branchia, ne sa qualcosa? (4)
    * Branchia: Non ne so nulla (2)
* duplicare lo sprite Branchia, rinominarlo in Pinna e cambiarne il costume; in questo caso quando lo sprite viene cliccato il dialogo sarà:
    * Granchi: Dottor Pinna, ha visto il regalo? (4)
    * Pinna: No, non l'ho visto (2)
* quando Granchi ha interrogato tutti i personaggi svela finalmente il mistero, ma solo quando viene cliccato a sua volta:
    * Granchi dice “Ho risolto il caso” per 3 secondi;
    * lo sprite **Gift** appare nella stessa posizione di Granchi ridotto al 60%;
    * Granchi si sposta lentamente di lato;
    * Granchi dice “Mi ci ero seduto sopra per sbaglio” per 4 secondi;
    * Stella cambia costume e dice “Ispettore, lei è un genio!” per 3 secondi;
* all'inizio del gioco Granchi deve posizionarsi alle coordinate giuste mentre il pacco deve rendersi invisibile; Granchi deve inoltre essere posto in primo piano, per non essere nascosto dal pacco quando appare;
* come fa a sapere Granchi che sono stati cliccati tutti gli sprite almeno una volta? Usa tre variabili booleane che vanno azzerate all'inizio del gioco e impostate al ricevimento del messaggio di click di ognuno dei personaggi. L'apparizione del regalo è comandata dall'invio di un messaggio (unico caso in cui non è necessario attendere la risposta).
