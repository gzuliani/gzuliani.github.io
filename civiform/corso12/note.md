[pensare ad attività da svolgere a casa (almeno per il giovedì)]

# LEZIONE n. 1 - 20220118

Introduzione

L01 - presentazione, intro corso, concetti di base, introduzione a Scratch, primi approcci
[stessa intro dei coderdojo, muovi, per sempre, pulsante stop/bandierina verde, muovi con barra spaziatrice, effetto del blocco per sempre (cosa succede se lo togliamo e perché), rimbalza quando tocchi il bordo, concetto di direzione, stile di rotazione, animazione(costumi), cambiare lo sprite al gatto, miao iniziale(suoni), ridurre la durata del suono, aggiungere un altro sprite nel mezzo, dire ahia e fermare tutto quando si scontrano, far apparire il secondo sprite dopo un po']

=========
non c'è stato tempo per vedere nulla, ci siamo fermati prima del "rimbalza quando tocchi il bordo"
=========


# LEZIONE n. 2 - 20220120

Scratch

Storytelling (narrativa)

# slide show con gli sfondi

caricare gli sfondi City With Water, Boardwalk, Mural, Castle 4 o scaricare foto di Cividale a Wikipedia
aggiungere un titolo alla prima slide, tipo "Saluti da ..."
se lasciamo l'immagine Bitmap, poi non potremo più correggere/cambiare il testo, che viene "fuso" nell'immagine
pippone immagine bitmap (o raster) vs. vettoriale -- cambiano pure i comandi
volendo si può prevedere una slide di chiusura [esercizio]
Scratch non dev'essere visibile, nasconderlo o cancellarlo
il codice delle transizioni lo mettiamo nello sfondo
avanti in automatico con timer (e musica!)
specificare la sequenza interponendo `switch backdrop to ()` e `wait () seconds`.
se voglio cambiare la durata di una diapositiva, devo cambiare il parametro in 4 posti diversi
se li metto in ordine in "Backdrops" posso usare `repeat ()` con `next backdrop` e `wait () seconds` (mi è più semplice modificare il ritardo, c'è un'unica istruzione); conviene impostare il primo!
ripeti per un numero di volte = slide - 1, se no si torna all'inizio!
se si segue l'ordine dei backdrop è facile andare avanti con la tastiera: rimuovere il ripeti e aggiungere un `when [space] key pressed` seguito da un `next backdrop`
... e se non voglio tornare alla prima??? => usare il blocco `backdrop (number)`
indietro -> `switch backdrop to ()` comprende anche `previous backdrop` ...
e se non voglio passare dalla prima all'ultima???
aggiungiamo una descrizione su ognuno dei backdrop
se statico, basta farlo nel backdrop, se però vogliamo un applicare un effetto (QUALE?)
-> creare uno sprite con la scritta "xxxx"; all'inizio nascosto, appare quando si passa allo sfondo "Boardwalk"
(usare when backdrop switches to; se si usa per sempre se background name=... l'effetto viene applicato ciclicamente -- può essere desiderabile oppure no, dipende dall'effetto)
differenza tra posizione del testo nello sprite e posizione dello sprite nello stage!!
duplicare lo sprite e adattarlo per la seconda slide
duplicae lo sprite e ...

questo sprite potrebbe essere un personaggio che si sposta e spiega... poi dice lui quando passare alla prossima diapositiva

# scenetta interattiva

narrativa interattiva, avventure testuali, avventure grafiche

si inizia con un dialogo tra la stella (preoccupata) e il granchio (via Scratch, sfondo "marino")
iniziano entrambi con la bandierina, sincronismo con `wait () seconds`
S: Ispettore Granchi, mi aiuti! (3)
G: Cosa è successo? (2)
S: Mi hanno rubato il regalo di compleanno! (4)
G: Farò delle indagini (3)

possiamo far muovere le chele a Granchi [parallelismo]

A questo punto inizia la parte interattiva
L'unica interazione che possiamo avere al momento è il click sugli sprite

click su Stella
 Granchi deve chiedere: Stella, è sicura di non averlo perso? (4)
 Stella deve rispondere: Certo che sono sicura! (2)

Come fa Granchi a sapere che abbiamo cliccato Stella? Glielo dice Stella con un messaggio.
differenza tra `broadcast` e `broadcast [] and wait`

click su Granchi:
 non serve ai fini del gioco; usiamolo per suggerire al giocatore di cliccare gli altri sprite
 `thinks [Devo interrogare tutti i testimoni...] for (4) seconds`

Solo quando avremo cliccato su tutti gli sprite, un click su Granchi risolverà il mistero

A questo punto è il caso di aggiungere qualche altro sprite; usiamo Fish; lo chiamiamo Branchia; facciamolo nuotare su e giù lentamente

click su Branchia:
 G: Professoressa Branchia, ne sa qualcosa? (4)
 B: Non ne so nulla (2)

duplichiamo lo sprite, lo chiamiamo Pinna e gli cambiamo costume

click su Pinna:
 G: Dottor Pinna, ha visto il regalo? (4)
 P: No, non l'ho visto (2)

A questo punto, cliccando su Granchi deve succedere questo
 G: Ho risolto il caso (3)
 appare il regalo sotto Granchi ====> aggiungere lo sprite del regalo (60%) e portare a inizio programma Granchi in primo piano
 Granchi si sposta lentamente di lato =====> all'inizio deve posizionarsi alle coordinate giuste!
 G: Mi ci ero seduto sopra per sbaglio (4)

 A questo punto Stella cambia costume e dice:
  S: Ispettore, lei è un genio! (3)

Come fa a sapere Granchi che sono stati cliccati tutti gli sprite almeno una volta?

Contatore? No!
Tre flag booleani? Sì!

Quando Granchi riceve il messaggio alza il flag relativo
(ricordarsi di inizializzarli a inizio gioco)

per l'apparizione del regalo si fa un broadcast senza attesa

alla fine nascondere le variabili


=========
non c'è stato tempo per la storiella interattiva
=========


# LEZIONE 3 - 20220125

passeggiata su quadrato: ripeti per 4 volte fai 100 passi, gira di 90 a sx, aspetta 1 secondo
meglio la pausa tra passi e gira
stile di rotazione (fuori dal ciclo, basta dirlo una volta per tutte)
rimpicciolire il gatto (col blocco o nelle proprietà)
caricare l'estensione penna
erase all + pen down all'inizio
cambiare colore/spessore (sempre fuori dal ciclo)

cosa succede se arresto il programma a metà?
così non ho più le condizioni iniziali giuste!
all'inizio conviene impostare posizione e direzione
concetto di inizializzazione
blocco vai a x/y che si aggiorna da solo -> molto comodo!
blocco punta in direzione

[penna/01-quadrato]

triangolo: 3 volte 120
quadrato: 4 volte 90
pentagono, esagono?

[penna/02-pentagono]

la rotazione è angolo giro diviso numero di lati
ho un computer, perché devo fare io la divisione?
usiamo l'operatore divisione per far emergere questa relazione
11 lati: 100 passi è troppo
con 50 e partendo da y=-160 si riesce ad arrivare a 20
abbassare/togliere il wait, se no perdiamo tempo
adesso scrivo due volte lo stesso numero in due posti diversi, rischio di dimenticarmene
variabile "num lati"
crea variabile, metti il blocco "num lati" in ripeti e nella divisione
ma vale zero, non succede nulla
all'inizio, porta "num lati" a ... e scriviamo lì il numero di lati una volta per tutte
possiamo chiedere all'utente quanti farne
blocco ask
non si vede la domanda! scratch al centro quando chiede, poi va al posto giusto
al secondo giro si vede la traccia... all'inizio del programma "penna su"
chiede ma non usa il valore
blocco answer (verificare con "dire" answer) [answer contiene l'ultimo dato immesso]
join per dire "num lati: answer"
porta num lati a answer

[penna/03-poligono-a-richiesta]

rifiutarsi di disegnare più di 20 lati se allora altrimenti
disegnare poligoni in successione, da 3 fino a 20
cicli nidificati
num lati ci dice il numero di lati del poligono in fase di disegno
nascondere la variabile se dà fastidio
disegnare ogni poligono con un colore diverso
disegnare ogni lato con un colore diverso
[set pen all'inizio se si vuole ottenere ogni volta la stessa sequenza di colori]

[penna/04-poligoni-in-sequenza]

=========
i due loop nidificati hanno creato notevoli difficoltà
=========

giocare anche con lo spessore (uguale per tutti, che cambia per ogni poligono)
non disegnare il lato ma solo i vertici: penna su/penna giù ad ogni spigolo, con penna abbastanza grossa
modalità turbo (menu edit o shift+bandierina verde)
farlo girare più volte: se non c'è il set del colore della penna iniziale si ottiene un bell'effetto grafico
metterci un persempre (dal goto in poi) per dargli continuità (nascondere il gatto, modulare la pausa tra un ciclo e l'altro) anche il valore del change pen ha un effetto interessante

=========
non c'è stato tempo per questo
=========

[penna/05-luci-psichedeliche]

stelle
devo tornare indietro ad ogni spigolo, ma di quanto?
gli angoli al centro di un pentagono sono 5, quindi 360/5=72
gli angoli degli spigoli sono angoli alla circonferenza, quindi metà: 36
devo quindi tornare indietro di 180-36 = 144
passi: almeno 200-250
cambiare posizione di partenza (y=+/-40, x=-passi/2)
se voglio la punta all'insù? Basta girare dall'altro verso!

=========
non c'è stato tempo per la stella
=========

[penna/06-stella-5-punte]

come generalizzare? 180 - 180/num lati
vale però solo per i lati dispari
disegnare il doppio dei lati e funziona

ciclare con num lati casuale, pausa 3 secondo, poi si ricomincia
ogni lato spessore e colore a caso
provare con e senza turbo

=========
non c'è stato tempo per la ghirlanda
=========


[penna/07-ghirlande]

spirale quadrata

passi = 10
vai a 0,0, punta a dx
per due volte: passi, gira
change passi di 10
cicla

cambiare colore di ogni lato, ogni due lati, ogni quadrato (richiede due cicli da 2)
provare a cambiare penna di 25 (25x4=100)

proporre il ripeti finché non tocchi il bordo

[penna/08-spirale-quadrata]

spirale esagonale (3 + 3 a 60°, passi 6 a incrementi di 6)

[penna/09-spirale-esagonale]

=========
lezione terminata qui
=========

spirale curva: il ciclo interno non serve; passi da 1 a incrementi di 0.1/0.5, ruotare di 10 gradi

[penna/10-spirale-curvilinea]

passeggiata casuale

razzo che lascia la scia: sprite "Rocketship"

penna giù / per sempre / fai 10 passi / ruota di 15
non va bene! aumentare i passi, diminuire i gradi (es. 15, 5)
meglio, aggiungere rimbalza quando tocchi il bordo
il razzo si muove di lato; ruotare i costumi
penna giu + cambia colore
provare ad abilitare il turbo durante la passeggiata casuale

[penna/11-razzo-pazzo]

passeggata casuale 2 (con timbro)

scegliamo uno sprite geometrico (o creiamo uno sprite a forma di quadrato -- usare shift per fare un quadrato preciso)
per sempre / scivola in 1 secondo in una posizione a caso
aggiungere un timbra prima di spostarsi:
per sempre / timbra / scivola in 1 secondo in una posizione a caso
duplicare lo sprite e rilanciare
il turbo qui non ha effetto, perché (è il scivola in 1 secondo che comanda!)

[penna/12-punti-e-linee]


# LEZIONE n. 4 - 20220127

tornare sul discorso del ciclo nidificato, provare a definire un blocco per il poligono
prima facciamo il blocco del quadrato, del triangolo e del pentagono
poi generalizziamo
poi li mettiamo in sequenza con n=3, 4, 5,  ...
a questo punto il ciclo esterno dovrebbe venire più naturale
gioco: ispirarsi a mondo sommerso
partire con lo sfondo griglia e parlare di movimento x/y e direzione/stile di rotazione

---

L02 - approccio informale incrementale: un semplice videogioco completo (varibili -- scegliere bene i nomi! --, cloni, messaggi)
L03.1 - un approccio più formale: implementazione dell'algoritmo di Euclide (occhio allo zero!)

L03.2 - geometria con la tartaruga (poligoni, spirali) => esercizio: casetta; spirale quadrata, circolare, girandole (180/(180-N)) N spigoli se N è dispari, 2N se pari [posso fermarmi quando dir=0, tanto non ci sono segmenti paralleli!]; timbro

L05.2 - matematica: tabelline, fibonacci (spirale?), numeri primi (Eratostene)
L04.1 - suoni, melodie, melodie politonali
L04.2 - simulazioni (razzo? proiettile? caduta del grave?)
L05.1 - uso ludico del microfono e della webcam
L06.1 - qualcosa con le liste... (massimo/minimo, media)

mBot

L07 - intro robotica, intro mBot, programmi precaricati, mCore + mBlock, LED, cicalino, pulsante
L08 - montaggio, motori, movimento, sensore ultrasonico -> aggiramento di ostacoli
L09 - sensore di linea, cruise control -> cruise control adattativo
L10 - modalità rover (se possibile!), rover cerca luce, robot cerca luce
L11 - comunicazione: sincronizzazione luci, seti, ...
L12 - tecniche avanzate: parcheggio, analisi del moto, ...

L13 - Simulazione di mBot in Scratch
L14 - Scratch e Arduino