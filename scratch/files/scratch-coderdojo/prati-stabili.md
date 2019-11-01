[//]: # (encoding=utf-8)

# Scaletta

_Campoformido - ?? Novembre 2019_

PRATI STABILI

## preliminari

* avvio di Scratch: impostazione della lingua italiana;

* struttura dell'editor: blocchi a sinistra, area di lavoro al centro, stage e sprite a destra;

## il protagonista

* trasciniamo il blocco `fai (10) passi` nell'area di lavoro; non succede niente;

* click sul blocco e il gattino si sposta verso a destra;

* selezionare il gruppo _Aspetto_;

* trascinare il blocco `dire (Ciao!) per (2) secondi` e agganciarlo sotto al blocco `fai (10) passi` -- notare l'area grigia che appare quando i due blocchi sono vicini: evidenzia il punto di aggancio;

* click su uno qualunque dei blocchi e il gattino si muove e saluta;

* sganciare il blocco `dire (Ciao!) per (2) secondi` trascinandolo lontano dal blocco `fai (10) passi`;

* agganciarlo sopra al blocco `fai (10) passi`:

* click su uno qualunque dei blocchi, e il gatto saluta e si muove: __l'ordine dei comandi conta!__

* sganciare i due blocchi spostando il blocco `fai (10) passi` (si sgancia sempre da sotto, se si trascina il blocco in alto si ottiene lo spostamento dell'intera catena di blocchi);

* eliminare il blocco `dire (Ciao!) per (2) secondi` trascinandolo nell'area dei blocchi -- non importa la posizione precisa;

* facciamo fare una passeggiata al gattino: selezioniamo il gruppo _Controllo_ e trasciniamo il blocco `per sempre` nell'area di lavoro; avvicinandolo al blocco `fai (10) passi` si incastra circondandolo; non succede nulla; click sul blocco e il gattino si sposta fino al bordo destro dello _Stage_;

* lo _Script_ è in esecuzione, lo si riconosce dall'alone giallo; se trasciniamo il gattino al centro dello _Stage_ con il mouse, riprende a spostarsi verso destra;

* per fermare un blocco `per sempre` bisogna premere il pulsante rosso in alto;

* vicino al pulsante di arresto c'è una bandierina verde: è il modo naturale in Scratch di avviare i giochi; facciamolo anche noi...

* selezioniamo il gruppo _Situazioni_, trasciniamo il blocco `quando si clicca su ⚐` nell'area di lavoro e agganciamolo al blocco `per sempre`;

* riportiamo il gattino al centro dello _Stage_, e verifichiamo che se ne sta fermo dove l'abbiamo lasciato; premiamo la bandierina ed esso riprende a muoversi;

* premere il pulsante d'arresto e riportare il gattino al centro della scena;

* vogliamo guidare il gattino con i tasti cursore, come fosse un'automobilina; per fare questo ricorriamo ai blocchi `ruota ↷ di (15) gradi` e `ruota ↶ di (15) gradi`:

        quando si clicca su ⚐
        per sempre
         fai (10) passi

        ruota ↷ di (15) gradi

        ruota ↶ di (15) gradi

* le rotazioni devono avvenire solo se sono premuti rispettivamente i tasti "freccia destra" e "freccia sinistra"; accedere al gruppo _Controllo_ e portare un blocco `se <> allora` nell'area di lavoro:

        quando si clicca su ⚐
        per sempre
         fai (10) passi

        ruota ↶ di (15) gradi

        ruota ↷ di (15) gradi

        se <> allora

* spostare il blocco `ruota ↷ di (15) gradi` all'interno del blocco `se <> allora`:

        quando si clicca su ⚐
        per sempre
         fai (10) passi

        se <> allora
          ruota ↷ di (15) gradi

        ruota ↶ di (15) gradi

* notare lo spazio vuoto esagonale tra il `se` e l'`allora`: lì va indicata la condizione per la quale devono essere eseguiti i blocchi interni; le varie condizioni disponibili si trovano nel gruppo _Sensori_;

* selezionare il gruppo _Sensori_ e trascinare il blocco `<tasto [spazio] premuto>` nello spazio, verificando che l'agganciamento sia avvenuto nel modo corretto (assicurarsi che il perimetro dell'esagono si evidenzi di bianco prima di rilasciare il blocco); aprire il menu a tendina e selezionare il tasto `freccia destra`;

        quando si clicca su ⚐
        per sempre
         fai (10) passi

        se <tasto (freccia destra) premuto> allora
         ruota ↷ di (15) gradi

        ruota ↶ di (15) gradi

* inserire il blocco `se <> allora` nel programma principale, prima del blocco `fai (10) passi`:

        quando si clicca su ⚐
        per sempre
         se <tasto (freccia destra) premuto> allora
          ruota ↷ di (15) gradi
         fai (10) passi

        ruota ↶ di (15) gradi

* premere la bandierina verde; il gattino comincia a muoversi verso destra; premere il tasto cursore a destra, ed esso curva verso destra! fare alcune prove, al termine premere il pulsante d'arresto;

* in modo analogo si prepari un blocco `se <> allora` per la rotazione sinistra:

        quando si clicca su ⚐
        per sempre
         se <tasto (freccia destra) premuto> allora
          ruota ↷ di (15) gradi
         fai (10) passi

        se <tasto (freccia sinistra) premuto> allora
         ruota ↶ di (15) gradi

* inserire il nuovo blocco `se <> allora` nel programma principale, sempre prima del blocco `fai (10) passi`:

        quando si clicca su ⚐
        per sempre
         se <tasto (freccia destra) premuto> allora
          ruota ↶ di (15) gradi
         se <tasto (freccia sinistra) premuto> allora
          ruota ↷ di (15) gradi
         fai (10) passi

* verificare che ora il controllo sul gattino è completo; provare a modificare i parametri dei comandi: che effetto hanno sulla mobilità del personaggio?

* poiché il tema del nostro gioco è un'ape, carichiamo lo sprite _bee.sprite3_: click sul pulsante _Scegli uno Sprite_ in basso a destra, quindi _Importa Sprite_;

* il nuovo personaggio appare al centro della scena, e l'icona che lo rappresenta si aggiunge a quella di Scratch nell'area degli sprite;

* il programma che avevamo scritto è sparito! Niente paura, ogni sprite ha il suo programma: selezionare _Sprite1_ ed ecco che il programma ricompare; trasciniamolo sopra l'icona dell'ape, in modo da copiarlo (attendere che l'icona si evidenzi di blu prima di rilasciare il codice); selezionare lo sprite dell'ape e verificare che il programma è stato copiato; a questo punto si può cancellare lo sprite di Scratch selezionando l'icona e premendo il pulsante "Cestino";

* adattiamo il programma alle dimensioni del nuovo personaggio:

        quando si clicca su ⚐
        per sempre
         se <tasto (freccia destra) premuto> allora
          ruota ↶ di (5) gradi
         se <tasto (freccia sinistra) premuto> allora
          ruota ↷ di (5) gradi
         fai (3) passi

* l'ape ha due costumi: alternandoli, si ha l'impressione che essa svolazzi; applichiamo l'effetto al programma aggiungendo il blocco `passa al costume seguente` dopo il blocco `fai (3) passi`:

        quando si clicca su ⚐
        per sempre
         se <tasto (freccia destra) premuto> allora
          ruota ↶ di (5) gradi
         se <tasto (freccia sinistra) premuto> allora
          ruota ↷ di (5) gradi
         fai (3) passi
         passa al costume seguente

* all'inizio del gioco vogliamo che l'ape occupi una posizione centrale; notare che quando sposto lo sprite con il mouse le coordinate del blocco `vai a x: () y: ()` cambiano; posizionare l'ape al centro, e inserire questo blocco prima del `per sempre`:

        quando si clicca su ⚐
        vai a x: (0) y: (0)
        per sempre
         se <tasto (freccia destra) premuto> allora
          ruota ↶ di (5) gradi
         se <tasto (freccia sinistra) premuto> allora
          ruota ↷ di (5) gradi
         fai (3) passi
         passa al costume seguente

* è ora di salvare il gioco!

## l'obiettivo

* scopo del gioco è raccogliere quanto più polline possibile prima che arrivi l'inverno; carichiamo allora lo sprite _sunflower.sprite3_ che rappresenta l'obiettivo che l'ape deve raggiungere;

* all'inizio del gioco il girasole deve apparire in una posizione a caso:

        quando si clicca su ⚐
        raggiungi (posizione a caso)

* se avvio il gioco e guido l'ape sul girasole non succede nulla; facciamo in modo che il fiore sparisca quando viene toccato dall'ape; il sensore da usare è `sta toccando (puntatore del mouse)`, ricordandosi di sostituire `puntatore del mouse` con `bee`:

        quando si clicca su ⚐
        raggiungi (posizione a caso)
        per sempre
         se <sta toccando (bee)> allora
          nascondi

* abbiamo ottenuto l'effetto voluto! se però adesso riavvio il gioco, il fiore non riappare; per questo dobbiamo aggiungere un blocco `mostra` all'inizio, dopo il blocco `raggiungi (posizione a caso)`:

        quando si clicca su ⚐
        raggiungi (posizione a caso)
        mostra
        per sempre
         se <sta toccando (bee)> allora
          nascondi

* per far riapparire il fiore devo cliccare sulla bandierina verde; perché non riappare automaticamente, magari dopo un breve lasso di tempo, da un'altra parte?

        quando si clicca su ⚐
        raggiungi (posizione a caso)
        mostra
        per sempre
         se <sta toccando (bee)> allora
          nascondi
          attendi (1) secondi
          raggiungi (posizione a caso)
          mostra

* aggiungiamo uno sfondo per dare un'ambientazione consona al gioco; premere il pulsante _Scegli uno Sfondo_ in basso a destra e scegliere l'immagine preferita (es. "Forest");

* si può giocare a schermo intero premendo il pulsante _Modalità presentazione_ in alto a destra; premere il riquadro nella stessa posizione per tornare alla modalità di lavoro;

* è ora di aggiungere il punteggio: contiamo quanti sono i girasoli sui quali l'ape è riuscita a posarsi... selezionare _Variabili_, quindi _Crea una Variabile_, chiamarla "Punti" e confermare premendo _OK_; cosa succede?

* abbiamo detto che facciamo un punto ogni volta che l'ape si posa su un girasole; selezioniamo lo sprite del girasole ed aggiungiamo il blocco `cambia [my variable] di (1)` all'interno del corpo del blocco `se <sta toccando (bee)> allora`, avendo l'accortezza di sostituire la variabile "my variable" con la variabile "Punti":

        quando si clicca su ⚐
        raggiungi (posizione a caso)
        mostra
        per sempre
         se <sta toccando (bee)> allora
          cambia [Punti] di (1)
          nascondi
          attendi (1) secondi
          raggiungi (posizione a caso)
          mostra

* provare il gioco e verificare che il punteggio aumenta quando l'ape raggiunge il girasole;

* notate un problema? quando il gioco riparte, il punteggio non si azzera! la soluzione è aggiungere il blocco `porta [Punti] a [0]` all'inizio del programma:

        quando si clicca su ⚐
        porta [Punti] a [0]
        raggiungi (posizione a caso)
        mostra
        per sempre
         se <sta toccando (bee)> allora
          cambia [Punti] di (1)
          nascondi
          attendi (1) secondi
          raggiungi (posizione a caso)
          mostra

## l'antagonista

* rendiamo il gioco più difficile: poiché siamo in autunno, l'ape deve evitare le foglie che cadono dagli alberi; se tocca una foglia, perde un punto;

* carichiamo l'ultimo sprite, _leaf.sprite3_, e posizioniamolo in alto sullo _Stage_; come facciamo a far cadere la foglia? beh, sappiamo che si comincia con qualcosa di simile a:

        quando si clicca su ⚐
        vai a x: (-80) y: (150)
        per sempre

* [brevi cenni al sistema di coordinate cartesiane...]

* per far spostare uno sprite verso il basso bisogna far diminuire la sua coordinata y; agganciamo perciò un blocco `cambia y di (-10)`; attenzione al meno, se ve lo scordate la foglia salirà in cielo!

        quando si clicca su ⚐
        vai a x: (-80) y: (150)
        per sempre
         cambia y di (-10)

* se ritenete che la foglia scenda troppo velocemente, potete abbassare il valore a -3;

* per rendere la caduta più realistica possiamo aggiungere una rotazione:

        quando si clicca su ⚐
        vai a x: (-80) y: (150)
        per sempre
         cambia y di (-3)
         ruota ↷ di (15) gradi

* quando la foglia raggiunge il fondo dello _Stage_ deve sparire; un modo per capire se la foglia è giunta a terra è verificare il valore della sua coordinata y: se è inferiore a -180 allora la si può riportare nella sua posizione iniziale:

        quando si clicca su ⚐
        vai a x: (-80) y: (150)
        per sempre
         cambia y di (-3)
         ruota ↷ di (15) gradi
         se <(posizione y) < (-180)> allora
          vai a x: (-80) y: (150)

* per rendere il gioco più vario, possiamo fare in modo che la posizione orizzontale venga scelta a caso dal programma:

        quando si clicca su ⚐
        vai a x: (-80) y: (150)
        per sempre
         cambia y di (-3)
         ruota ↷ di (15) gradi
         se <(posizione y) < (-180)> allora
          vai a x: (numero a caso tra (-200) e (200)) y: (150)

* poiché lo sprite _leaf_ è dotato di molti costumi possiamo cambiare l'aspetto ad ogni nuova discesa:

        quando si clicca su ⚐
        vai a x: (-80) y: (150)
        per sempre
         cambia y di (-3)
         ruota ↷ di (15) gradi
         se <(posizione y) < (-180)> allora
          vai a x: (numero a caso tra (-200) e (200)) y: (150)
          passa al costume seguente

* se la foglia tocca l'ape allora si perde un punto:

        quando si clicca su ⚐
        vai a x: (-80) y: (150)
        per sempre
         cambia y di (-3)
         ruota ↷ di (15) gradi
         se <(posizione y) < (-180)> allora
          vai a x: (numero a caso tra (-200) e (200)) y: (150)
          passa al costume seguente
         se <sta toccando (bee)> allora
          cambia [Punti] di (-1)

* provare il gioco andando a finire di proposito su una foglia... cosa accade? perché? se la cosa non piace, come si potrebbe risolvere? beh, per esempio riportando la foglia in alto:

        quando si clicca su ⚐
        vai a x: (-80) y: (150)
        per sempre
         cambia y di (-3)
         ruota ↷ di (15) gradi
         se <(posizione y) < (-180)> allora
          vai a x: (numero a caso tra (-200) e (200)) y: (150)
          passa al costume seguente
         se <sta toccando (bee)> allora
          cambia [Punti] di (-1)
          vai a x: (numero a caso tra (-200) e (200)) y: (150)
          passa al costume seguente

* una foglia sola non complica abbastanza il gioco? se ne può aggiungere un'altra! una possibilità è duplicare lo sprite (magari ritardando l'apparizione delle copie per aumentare gradualmente il livello di difficoltà del gioco), l'altra è usare i _Cloni_;

* cloni: lo sprite principale ha il solo scopo di generare copie di sè stesso, e sono le copie (i cloni) che eseguono il programma vero e proprio:

        quando si clicca su ⚐
        crea clone di (me stesso)

        quando vengo clonato
        vai a x: (-80) y: (150)
        per sempre
         cambia y di (-3)
         ruota ↷ di (15) gradi
         se <(posizione y) < (-180)> allora
          vai a x: (numero a caso tra (-200) e (200)) y: (150)
          passa al costume seguente
         se <sta toccando (bee)> allora
          cambia [Punti] di (-1)
          vai a x: (numero a caso tra (-200) e (200)) y: (150)
          passa al costume seguente

* conviene nascondere il clone principale della foglia: ferma lì in mezzo allo schermo dà solo fastidio -- ricordiamoci di inserire un blocco `mostra` nel programma principale, altrimenti anche i cloni rimarranno invisibili:

        quando si clicca su ⚐
        nascondi
        crea clone di (me stesso)

        quando vengo clonato
        vai a x: (-80) y: (150)
        mostra
        per sempre
         cambia y di (-3)
         ruota ↷ di (15) gradi
         se <(posizione y) < (-180)> allora
          vai a x: (numero a caso tra (-200) e (200)) y: (150)
          passa al costume seguente
         se <sta toccando (bee)> allora
          cambia [Punti] di (-1)
          vai a x: (numero a caso tra (-200) e (200)) y: (150)
          passa al costume seguente

* il vantaggio dei cloni è che è semplice definire quando e quanti cloni devono essere in gioco, ad esempio:

        quando si clicca su ⚐
        nascondi
        per sempre
         crea clone di (me stesso)
         attendi (5) secondi

* quando un clone tocca l'ape è possibile metterlo "fuori gioco":

        quando vengo clonato
        vai a x: (-80) y: (150)
        mostra
        per sempre
         cambia y di (-3)
         ruota ↷ di (15) gradi
         se <(posizione y) < (-180)> allora
          vai a x: (numero a caso tra (-200) e (200)) y: (150)
          passa al costume seguente
         se <sta toccando (bee)> allora
          cambia [Punti] di (-1)
          elimina questo clone

## partita a tempo

* facciamo in modo che il gioco abbia una durata predefinita... possiamo usare una nuova variabile, la impostiamo ad un valore iniziale che viene decrementato ogni secondo e, quando questa raggiunge lo zero, interrompiamo il gioco con il blocco `ferma [tutto]` (oppure la si incrementa a partire da zero e si interrompe il gioco quando raggiunge un valore predefinito);

* questo script può essere assegnato a uno sprite qualunque, anche allo sfondo!

* creare una nuova variabile "Tempo", quindi:

        quando si clicca su ⚐
        porta [Tempo] a (30)
        per sempre
         attendi (1) secondo
         cambia [Tempo] di (-1)
         se <(Tempo) = (0)> allora
          ferma [tutto]

## altri spunti

* aggiungere gli effetti sonori;

* sapreste simulare l'effetto del vento sulle foglie? e un vento di intensità variabile?

* è accettabile un punteggio negativo? come si potrebbe fare per evitare questa condizione? basta togliere il punto solo se il punteggio non è zero!

* aggiungere una schermata finale al gioco;

* aggiungere una schermata iniziale di presentazione del gioco con le istruzioni;

* il girasole sparisce se l'ape non lo raggiunge entro 5 secondi;

* aggiungere un altro sprite (es. _mushroom.sprite3_) che appare di tanto in tanto e che se toccato dall'ape causa la fine del gioco;

* aggiungere un altro sprite (es. _boots.sprite3_) che insegue l'ape e che se la raggiunge causa la fine del gioco;

* per chi ha scelto lo sfondo "Forest", fare in modo che il fiore appaia solo tra l'erba (sostituire i due blocchi `raggiungi (posizione a caso)` con `vai a x: (numero a caso tra (-200) e (200)) y: (numero a caso tra (-140) e (-30))`;
