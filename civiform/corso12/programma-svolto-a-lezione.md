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
* programmazione di CyberPi in modalità **Live** (dettagli più avanti)
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

### Attuatori: striscia LED /1

* striscia formata da 5 LED indipendenti
* prove di accensione dei LED di rosso con i vari comandi
* accendere i LED solo quando il tasto A è premuto -- notare il ritardo

### Modalità Upload

* programmazione di CyberPi in modalità **Live**:
    * il programma viene creato in mBlock
    * il programma viene eseguito in mBlock
    * quando incontra un blocco relativo a CyberPi mBlock lo invia alla scheda e attende che venga eseguito, dopodiché prosegue con l'istruzione successiva -- il processo non è efficiente:
        * la trasmissione del comando richiede del tempo
        * l'esecuzione del comando richiede del tempo (poco)
        * l'invio della risposta richiede del tempo
    * il programma richiede mBlock per essere eseguito
    * se si scollega CyberPi il programma non funziona più
* programmazione di CyberPi in modalità **Upload**:
    * il programma viene creato in mBlock
    * il programma viene trasferito e memorizzato in CyberPi
    * il programma non richiede mBlock né il PC per essere eseguito
    * il programma viene eseguito alla massima velocità
    * il programma caricato in CyberPi non è leggibile né tanto meno modificabile
    * in caso di blocco il tasto Home riporta al menu iniziale
    * CyberPi consente la memorizzazione di al più 8 programmi -- il programma viene salvato nell'ultima posizione utilizzata

### Attuatori: striscia LED /2

* caricare il programma precedente e verificare la maggiore reattività
* modificare l'intensità dei LED portandola da 0 a 100 e poi di nuovo a zero a passi di 10; confrontare i tempi di esecuzione nelle modalità **Live** e **Upload** -- nel secondo caso le pulsazioni avvengono così velocemente che per renderle distinguibili da un lampeggio è necessario aumentare il numero di passi da 10 a 100 (abbassando l'incremento a 1) e aggiungendo una pausa di 0.01 secondi tra un incremento e il successivo
* far lampeggiare l'intera striscia
* far lampeggiare alternativamente i LED della striscia
* riprodurre l'animazione dell'auto Kit di "Supercar"
* uso dei colori: selezioni dalla palette
* sintesi additiva e definizione RGB della tinta
* simulare il funzionamento di un semaforo
* simulare il lampeggiante della polizia: 4 lampeggi stroboscopici blu del LED di sinistra (20ms acceso, 80ms spento, 4 lampeggi blu del LED di destra -- in modalità **Live** non è possibile rispettare le tempistiche date
* realizzare un vu-meter che rappresenta il livello di rumore captato dal microfono
* accendere i LED della striscia con un'intensita inversamente proporzionale alla luminosità registrata dal fotoricettore (luce crepuscolare)

### Attuatori: altoparlante

* riproduzione dei suoni predefiniti
* creazione di melodie -- caricare i programmi in CyberPi perché le pause che la modalità **Live** introduce tra l'emissione di due note pregiudicano l'esecuzione
* esempio di conversione di "Tanti Auguri"
* riproduzione della sirena della polizia:
* sfruttare il multi-threading di CyberPi per riprodurre il lampeggio stroboscopico della polizia e la sirena quando si preme il pulsante B

# Lezione n.8 - CyberPi e mBot, 10/02/2022

### Attuatori: altoparlante

* emissione di suoni di frequenza e durata specifica
* emissione di suoni casuali 

### Attuatori: display

* display grafico di 1.44" con risoluzione di 128×128 pixel
* gestisce tre modalità distinte mutuamente esclusive: testo, tabella e grafico
* consente fino a 8 etichette in sovrimpressione
* display orientabile via software
* modalità testo:
    * 4 dimesioni di carattere: `small`, `middle`, `big`, `super big`
    * dimensione e colore uguale per tutto il flusso di testo
    * flusso organizzato a linee
    * il flusso ha origine in alto a sinistra
    * a-capo automatico e su richiesta
    * scorrimento automatico verso l'alto al raggiungimento dell'ultima riga
* modalità tabella:
    * massimo 4 righe, 3 colonne
    * dimensione del testo prefissata (`middle`)
    * scorrimento orizzontale automatico dei testi
* modalità grafica:
    * grafico a linea o a barre verticali
    * origine in basso a sinistra
    * valori compresi nell'intervallo [0÷100]
    * raggruppamento implicito per colore
    * scorrimento automatico delle tracce
    * aggiornamento automatico delle barre
* etichette:
    * 8, disponibili in tutte le modalità
    * appaiono in sovrimpressione al resto
    * liberamente posizionabili sul display
    * dimensione e colore del testo proprie
* diagrammare l'intensità luminosa e il livello di rumore acquisiti da CyberPi
* simulare il lancio di un dado allo scuotimento di CyberPi
* realizzare una livella digitale
* usare la modalità testo per presentare brevemente i programmi

### Attuatori: motori con encoder

* caricamento dell'estensione **mBot2 Shield**
* distinzione tra l'area **mBot2 Chassis** e **mBot2 Extension Port**: i blocchi per il controllo dei motori con encoder si trovano nella prima
* encoder: sensibilità 1°, accuratezza in rotazione 5°
* ruote di mBot2 come pomelli di controllo
* uso del blocco `wait until <button [B] pressed>?` come sicurezza
* movimenti base di mBot: avanti, indietro, rotazione (sul posto)
* controllo della velocità: RPM/percentuale di potenza
* controllo della distanza percorsa su tratti rettilinei
* controllo dell'angolo di rotazione su sé stesso
* movimento lungo i lati di un quadrato, poi un pentagono di lato 50cm
* considerazioni sulla precisione della traiettoria seguita
* effetto benefico della calibrazione nel compensare i giochi meccanici
* programmazione di una passeggiata casuale
* uso dei LED per indicare il tipo di movimento

# Lezione n.9 - mBot2: motori, sensore ultrasonico, 15/02/2022 

* tracciamento di traiettorie curvilinee
* controllo dei singoli motori
* relazione tra segno della velocità e senso di rotazione dei motori -- valori positivi fanno ruotare il motore di sinistra (M1) nel senso di marcia, quello di destra (M2) in direzione opposta
* relazione tra rapporto delle velocità di rotazione e raggio di curvatura
* movimento lungo traiettorie curvilinee arbitrarie: a S, a U, a 8

### Sensori: sensore ultrasonico

* principio di funzionamento: ecolocalizzazione
* visto frontalmente la capsula TX è quella di sinistra, RX quella di destra
* caratteristiche del sensore: campo di misura 5-300cm, accuratezza 5%
* caricamento dell'estensione **Ultrasonic Sensor 2**
* uso del blocco `ultrasonic 2 (1) distance to an object (cm)`: il primo indice identifica il sensore -- mBuild consente di collegare in sequenza fino a 10 sensori, l'indice discrimina quale dei sensori ultrasonici presenti in catena dev'essere interrogato
* uso dei LED per indicare la distanza dell'ostacolo -- verde per "via libera", giallo per "ostacolo in distanza", rosso per "ostacolo in prossimità"
* realizzazione di un sensore di parcheggio
* uso del sensore per arrestare il robot di fronte ad un ostacolo
* programma "scansa-ostacoli": procedere diritti se l'ostacolo si trova a più di 40cm altrimenti sterzare in una direzione a caso
* programma "scansa-ostacoli" avanzato: effettuare una sterzata in retromarcia se l'ostacolo si trova a meno di 15cm

# Lezione n.10 - Competenze trasversali e imprenditorialità, 17/02/2022 

[Lezione svolta da altri insegnanti]

# Lezione n.11 - Inseguitore di linea, 15/02/2022 

### Sensori: sensore di linea

* principio di funzionamento
* ruolo dei LED RGB accoppiati ai sensori -- diminuire le interferenze della luce ambientale
* procedura di calibrazione del sensore:

    > * Double-press: When the button is double-pressed, Quad RGB Sensor starts to learn the background and line for line following.
    >   Place the light sensors on the background of the line-following track map and double-press the button. When you see the LEDs indicating the line-following state blink quickly, sway the sensors from side to side above the background and line until the LEDs stop blinking. It takes about 2.5 seconds. The parameter values obtained are automatically stored. If the learning fails, the LEDs blink slowly, and you need to start the learning again.
    > * Long-press: When the button is long-pressed, Quad RGB Sensor switches the color of the fill lights. Generally, you don’t need to change the color. The color is set automatically after the learning is complete.

* caricamento dell'estensione **Quad RGB Sensor(beta)**
* uso del blocco `quad rgb sensor (1) L1, R1's [line] status (0~3)`
* codifica: 1 se il sensore è sulla linea (**L**ine), 0 se sullo sfondo ((**B**ackground)):

        L1 R1 value status
        B  B   00     0
        B  L   01     1
        L  B   10     2
        L  L   11     3

* logica analoga per i sensori esterni -- di norma usati per individuare diramazioni della pista principale
* programma "inseguitore di linea":
    * procedere diritti quando entrambi i sensori sono sulla linea
    * curvare quando uno dei due sensori esce dalla linea -- rotazione vs. sterzata
    * retromarcia quando entrambi i sensori sono fuori dalla linea 
* spostare l'algoritmo in un blocco personalizzato `insegui la linea`
* integrare un arresto in caso di oggetto a meno di 20cm
* integrare un rallentamento in caso di oggetto a distanza a meno di 40cm
* riconoscimento dei colori:
    * emettere un breve suono quando si percorre il tratto verde
    * accendere il LED di giallo quando si incontra il tratto giallo
    * rallentare quando si percorre il tratto di pista blu
    * invertire il senso di marcia (rotazione di 180°) quando si incontra il tratto rosso

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
