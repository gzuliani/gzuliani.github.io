# L'informatiche creative cun Scratch

Marilenghe & Mariscuele
Codroip, scuele primarie G.B. Candotti

_Sabide ai 8 di Avrîl dal 2017_

![](scripts\zuc.png)

## Surisutis!

 * impostare la lingua friulana scegliendo _Furlan_ dal menu di selezione
   delle lingue (icona mappamondo in alto a sinistra);
 * trascinare il blocco `fâs (10) pas` nell'area di lavoro: non succede nulla!

    ![](scripts\intro-1.png)

 * doppio click e il gatto si muove;
 * selezionare _Aspiet_;
 * trascinare il blocco `dî [Hello!] par (2) seconts` e agganciarlo sotto al
   blocco `fâs (10) pas` -- notare l'effetto calamita e il tratto bianco che
   evidenzia il punto di aggancio che appare quando i due blocchi sono vicini;
 * doppio click su `Hello!` e scrivere `Mandi!`:

    ![](scripts\intro-2.png)

 * doppio click su uno qualunque dei blocchi e il gatto si muove e saluta;
 * sganciare il blocco `dî [Mandi!] par (2) seconts` trascinandolo lontano
   dal blocco `fâs (10) pas`;
 * agganciarlo sopra al blocco `fâs (10) pas`:

     ![](scripts\intro-3.png)

 * doppio click su uno qualunque dei blocchi, e il gatto saluta e si muove:
   __l'ordine dei comandi conta!__
 * sganciare i due blocchi spostando il blocco `fâs (10) pas` (si sgancia
   sempre da sotto, se si trascina il blocco in alto si ottiene lo spostamento
   dell'intera catena di blocchi);
 * eliminare il blocco `dî [Mandi!] par (2) seconts` trascinandolo nell'area
   dei blocchi -- non importa la posizione precisa;
 * selezionare _Control_;
 * trascinare il blocco `par simpri` sopra il blocco `fâs (10) pas` in modo
   da contenerlo (aiuarsi con l'indicazione del punto di aggancio):

    ![](scripts\gjat-1.png)

[//]: # (        par simpri                                                    )
[//]: # (         fâs (10) pas                                                 )

 * doppio click, il gatto oltrepassa il bordo destro;
 * trascinare lo sprite a centro schermo prendendolo per la coda: il gatto
   riprende la sua corsa;
 * notare l'alone giallo attorno ai blocchi:__il programma è in esecuzione!__
 * per arrestare il programma in esecuzione, premere il pulsante rosso in alto;
 * notare la bandierina che cambia colore: durante l'esecuzione è verde chiaro,
   quando il programma è arrestato è verde scuro;
 * si usa avviare il programma cliccando sulla bandierina... selezionare
   _Situazions_, agganciare il blocco `cuant che si cliche su P` sopra il
   blocco `par simpri`:

    ![](scripts\gjat-2.png)

[//]: # (        cuant che si cliche su P                                      )
[//]: # (        par simpri                                                    )
[//]: # (          fâs (10) pas                                                )                                                )

 * provare ad avviare ed arrestare il programma...
 * riportare il gatto al centro dello schermo;
 * anziché farlo camminare verso destra, lo facciamo camminare verso il cursore
   del mouse: in questo modo possiamo controllare la traiettoria del gatto!
   Selezionare _Moviment_, aggiungere il blocco
   `ponte viars [pontadôr dal mouse]` prima del blocco `fâs (10) pas`:

    ![](scripts\gjat-3.png)

[//]: # (        cuant che si cliche su P                                      )
[//]: # (        par simpri                                                    )
[//]: # (          ponte viars [pontadôr dal mouse]                            )
[//]: # (          fâs (10) pas                                                )

 * riavviare il programma e verificare il funzionamento;
 * Si riscontrano due problemi: quando va verso sinistra il gatto cammina a
   testa in giù, inoltre quando raggiunge il cursore sembra impazzire!
 * il primo problema si risolve con il blocco
   `puarte stîl di rotazion a [çampe-drete]`, da inserire prima del blocco
   `par simpri` (non serve ribadirlo ad ogni movimento):

    ![](scripts\gjat-4.png)

[//]: # (        cuant che si cliche su P                                      )
[//]: # (        puarte stîl di rotazion a [çampe-drete]                       )
[//]: # (        par simpri                                                    )
[//]: # (          ponte viars [pontadôr dal mouse]                            )
[//]: # (          fâs (10) pas                                                )

 * provare l'effetto degli altri stili: `no zirâ` e `puès zirâ`;
 * il secondo problema si risolve evitando lo spostamento del gatto quando
   questo è vicino al cursore del mouse (es. la distanza è minore di 10 passi).
   Selezionare _Control_, trascinare il blocco `se <> alore` sopra i blocchi
   `ponte viars [pontadôr dal mouse]` e `fâs (10) pas` in modo da contenerli;
 * far partire il programma: il gatto non si muove... __manca la condizione che
   indica quando il gatto si deve muovere__!
 * il gatto si deve muovere solo se è abbastanza lontano dal cursore del mouse;
   riformulando: _SE la distanza dal mouse è maggiore di 3 ALLORA..._;
 * si comincia inserendo l'operatore di disuguaglianza: selezionare _Operadôrs_,
   quindi inserire il blocco `[] > []` nella casella del blocco `se <> alore`;
 * selezionare _Sensôrs_, ed inserire il blocco
  `distance di [pontadôr dal mouse]` nella casella di sinistra dell'operatore;
 * doppio clic sulla casella di destra, quindi inserire `10` con la tastiera:

    ![](scripts\gjat-5.png)

[//]: # (        cuant che si cliche su P                                      )
[//]: # (        puarte stîl di rotazion a [çampe-drete]                       )
[//]: # (        par simpri                                                    )
[//]: # (          se <(distance di [pontadôr dal mouse]) > [10]> alore        )
[//]: # (            ponte viars [pontadôr dal mouse]                          )
[//]: # (            fâs (10) pas                                              )

 * aggiungiamo un'animazione...
 * selezionare la scheda _Costums_, si vede che il gatto ne ha due;
 * selezionandoli in rapida sequenza si genera una semplice animazione;
 * tornare alla scheda _Script_, selezionare _Aspiet_;
 * trascinare il blocco `passe al costum sucessîf` e agganciarlo al blocco
   `fâs (10) pas`:

    ![](scripts\gjat-6.png)

[//]: # (        cuant che si cliche su P                                      )
[//]: # (        puarte stîl di rotazion a [çampe-drete]                       )
[//]: # (        par simpri                                                    )
[//]: # (          se <(distance di [pontadôr dal mouse]) > [10]> alore        )
[//]: # (            ponte viars [pontadôr dal mouse]                          )
[//]: # (            fâs (10) pas                                              )
[//]: # (            passe al costum sucessîf                                  )

 * provare...;
 * il gatto è troppo veloce? Portare il numero di passi a `5`. Il gatto è
   troppo grande? Rimpicciolirlo interattivamente con lo strumento
    _Ridûs il sprite_ della barra della finestra, oppure con il blocco
   `puarte dimension al (100) %`, impostando una percentuale adeguata, es.
   `80`:

    ![](scripts\gjat-7.png)

[//]: # (        cuant che si cliche su P                                      )
[//]: # (        puarte dimension al (80) %                                    )
[//]: # (        puarte stîl di rotazion a [çampe-drete]                       )
[//]: # (        par simpri                                                    )
[//]: # (          se <(distance di [pontadôr dal mouse]) > [10]> alore        )
[//]: # (            ponte viars [pontadôr dal mouse]                          )
[//]: # (            fâs (5) pas                                               )
[//]: # (            passe al costum sucessîf                                  )

 * aggiungiamo uno sfondo: click sull'icona _Sielç un fonts de librarie_ (un
   paesaggio stilizzato) in basso a sinistra, selezionare uno sfondo
   quanlunque, es. __room3__;
 * introduciamo un nuovo personaggio; click sull'icona _Gnûf sprite:_ al di
   sotto dello _Stage_ (un piccolo alieno) e selezionare __Mouse1__;
 * il programma è sparito?! No, ogni sprite ne ha uno; semplicemente ora è
   selezionato lo sprite del topolino, che al momento ne è sprovvisto (così
   come lo era il gatto all'inizio). Selezionando lo sprite del gatto si
   ritrova il programma fin qui predisposto -- ri-selezionare il topolino;
 * è sproporzionato rispetto al gatto: andrà ridimensionato (es. `50`%);
 * rinominiamo gli sprite: _gjat_ per il gatto, _surisute_ per il topo...
 * selezionare lo sprite, click sulla (i) azzurra per accedere alle proprietà,
   cambiare il nome, quindi click sulla freccia azzurra per tornare all'elenco;
 * il topolino deve scorrazzare per lo schermo... sappiamo come farlo correre
   senza sosta:

    ![](scripts\surisute-1.png)

[//]: # (        cuant che si cliche su P                                      )
[//]: # (        puarte dimension al (50) %                                    )
[//]: # (        par simpri                                                    )
[//]: # (          fâs (10) pas                                                )

 * così va a sbattere contro il bordo destro, come accadeva al gatto; si può
   però costringerlo a cambiare direzione quando raggiunge il limite dello
   schermo utilizzando il blocco `sbalce cuant che tu tocjis la flancade`
   subito dopo il blocco `fâs (10) pas`:

    ![](scripts\surisute-2.png)

[//]: # (        cuant che si cliche su P                                      )
[//]: # (        puarte dimension al (50) %                                    )
[//]: # (        par simpri                                                    )
[//]: # (          fâs (10) pas                                                )
[//]: # (          sbalce cuant che tu tocjis la flancade                      )

 * il topolino si muove solo in orizzontale... impostare una direzione
   arbitraria iniziale con il blocco `ponte in direzion (90)`, avendo cura di
   scegliere una traiettoria obliqua:

    ![](scripts\surisute-3.png)

[//]: # (        cuant che si cliche su P                                      )
[//]: # (        puarte dimension al (50) %                                    )
[//]: # (        ponte in direzion (60)                                        )
[//]: # (        par simpri                                                    )
[//]: # (          fâs (10) pas                                                )
[//]: # (          sbalce cuant che tu tocjis la flancade                      )

 * per rendere la corsa più realistica, sfruttare anche per questo sprite il
   secondo costume, aggiungendo il blocco `passe al costum sucessîf`;

    ![](scripts\surisute-4.png)

[//]: # (        cuant che si cliche su P                                      )
[//]: # (        puarte dimension al (50) %                                    )
[//]: # (        ponte in direzion (60)                                        )
[//]: # (        par simpri                                                    )
[//]: # (          fâs (10) pas                                                )
[//]: # (          passe al costum sucessîf                                    )
[//]: # (          sbalce cuant che tu tocjis la flancade                      )

 * quando il gatto raggiunge il topo, questo deve sparire...
   __un altro SE/ALORE__!

    ![](scripts\surisute-5.png)

[//]: # (        cuant che si cliche su P                                      )
[//]: # (        puarte dimension al (50) %                                    )
[//]: # (        ponte in direzion (60)                                        )
[//]: # (        par simpri                                                    )
[//]: # (          se <al sta tocjant [gjat]?> alore                           )
[//]: # (            tapone                                                    )
[//]: # (          fâs (10) pas                                                )
[//]: # (          passe al costum sucessîf                                    )
[//]: # (          sbalce cuant che tu tocjis la flancade                      )

 * una volta preso, il topolino non compare più -- neanche se si fa ripartire
   il gioco... perché? Bisogna assicurarsi che all'inizio della partita il
   topolino non sia nascosto, aggiungendo un blocco `mostre` (da _Aspiet_) come
   primo blocco dopo il `cuant che si cliche su P`:

    ![](scripts\surisute-6.png)

[//]: # (        cuant che si cliche su P                                      )
[//]: # (        mostre                                                        )
[//]: # (        puarte dimension al (50) %                                    )
[//]: # (        ponte in direzion (60)                                        )
[//]: # (        par simpri                                                    )
[//]: # (          se <al sta tocjant [gjat]?> alore                           )
[//]: # (            tapone                                                    )
[//]: # (          fâs (10) pas                                                )
[//]: # (          passe al costum sucessîf                                    )
[//]: # (          sbalce cuant che tu tocjis la flancade                      )

 * ora va meglio, ma il gioco si limita a catturare un solo topolino... Dopo
   che è stato catturato, si può far ricomparire il topolino dopo un po' in una
   altra zona dello schermo, aggiungendo un blocco `spiete (3) seconts` seguito
   da un `va a [posizion a câs]` e un `mostre`:

    ![](scripts\surisute-7.png)

[//]: # (        cuant che si cliche su P                                      )
[//]: # (        mostre                                                        )
[//]: # (        puarte dimension al (50) %                                    )
[//]: # (        ponte in direzion (60)                                        )
[//]: # (        par simpri                                                    )
[//]: # (          se <al sta tocjant [gjat]?> alore                           )
[//]: # (            tapone                                                    )
[//]: # (            spiete (3) seconts                                        )
[//]: # (            va a [posizion a câs]                                     )
[//]: # (            mostre                                                    )
[//]: # (          fâs (10) pas                                                )
[//]: # (          passe al costum sucessîf                                    )
[//]: # (          sbalce cuant che tu tocjis la flancade                      )

 * provare il gioco...
 * la direzione del topolino è facilmente prevedibile; aumentare la difficoltà
   del gioco cambiando (di poco) la direzione ad ogni passo, sfruttando il
   blocco `numar a câs tra (1) e (10)`:

    ![](scripts\surisute-8.png)

[//]: # (        cuant che si cliche su P                                      )
[//]: # (        mostre                                                        )
[//]: # (        puarte dimension al (50) %                                    )
[//]: # (        ponte in direzion (60)                                        )
[//]: # (        par simpri                                                    )
[//]: # (          se <al sta tocjant [gjat]?> alore                           )
[//]: # (            tapone                                                    )
[//]: # (            spiete (3) seconts                                        )
[//]: # (            va a [posizion a câs]                                     )
[//]: # (            mostre                                                    )
[//]: # (          fâs (10) pas                                                )
[//]: # (          zire di (numar a câs tra (-45) e (45)) ponts                )
[//]: # (          passe al costum sucessîf                                    )
[//]: # (          sbalce cuant che tu tocjis la flancade                      )

 * anche i passi del topolino possono essere variabili (es. tra 1 e 20):

     ![](scripts\surisute-9.png)

[//]: # (        cuant che si cliche su P                                      )
[//]: # (        mostre                                                        )
[//]: # (        puarte dimension al (50) %                                    )
[//]: # (        ponte in direzion (60)                                        )
[//]: # (        par simpri                                                    )
[//]: # (          se <al sta tocjant [gjat]?> alore                           )
[//]: # (            tapone                                                    )
[//]: # (            spiete (3) seconts                                        )
[//]: # (            va a [posizion a câs]                                     )
[//]: # (            mostre                                                    )
[//]: # (          fâs (numar a câs tra (1) e (20)) pas                        )
[//]: # (          zire di (numar a câs tra (-45) e (45)) ponts                )
[//]: # (          passe al costum sucessîf                                    )
[//]: # (          sbalce cuant che tu tocjis la flancade                      )

 * per estendere il gioco a tutto lo schermo, premere __il pulsante azzurro__
   in alto a sinistra;
 * contiamo i topolini catturati, introducendo una variabile selezionando
   _Variabilis e Listis_ e premendo il pulsante _Cree une Variabile_;
 * chiamiamo la variabile _surisutis_; cosa accade sullo schermo?
 * aggiungiamo un blocco `mude [surisutis] di (1)` subito dopo il blocco
   `tapone`, in modo da aggiornare il punteggio appena il topolino è stato
   raggiunto:

    ![](scripts\surisute-10.png)

[//]: # (        cuant che si cliche su P                                      )
[//]: # (        mostre                                                        )
[//]: # (        puarte dimension al (50) %                                    )
[//]: # (        ponte in direzion (60)                                        )
[//]: # (        par simpri                                                    )
[//]: # (          se <al sta tocjant [gjat]?> alore                           )
[//]: # (            tapone                                                    )
[//]: # (            mude [surisutis] di (1)                                   )
[//]: # (            spiete (3) seconts                                        )
[//]: # (            va a [posizion a câs]                                     )
[//]: # (            mostre                                                    )
[//]: # (          fâs (numar a câs tra (1) e (20)) pas                        )
[//]: # (          zire di (numar a câs tra (-45) e (45)) ponts                )
[//]: # (          passe al costum sucessîf                                    )
[//]: # (          sbalce cuant che tu tocjis la flancade                      )

 * verificare l'incremento del punteggio;
 * __chi scopre l'errore?__ Il punteggio va azzerato a inizio partita:

    ![](scripts\surisute-11.png)

[//]: # (        cuant che si cliche su P                                      )
[//]: # (        puarte [surisutis] a [0]                                      )
[//]: # (        mostre                                                        )
[//]: # (        puarte dimension al (50) %                                    )
[//]: # (        ponte in direzion (60)                                        )
[//]: # (        par simpri                                                    )
[//]: # (          se <al sta tocjant [gjat]?> alore                           )
[//]: # (            tapone                                                    )
[//]: # (            mude [surisutis] di (1)                                   )
[//]: # (            spiete (3) seconts                                        )
[//]: # (            va a [posizion a câs]                                     )
[//]: # (            mostre                                                    )
[//]: # (          fâs (numar a câs tra (1) e (20)) pas                        )
[//]: # (          zire di (numar a câs tra (-45) e (45)) ponts                )
[//]: # (          passe al costum sucessîf                                    )
[//]: # (          sbalce cuant che tu tocjis la flancade                      )

 * facciamo in modo che il gioco abbia una durata predefinita... Idea: 
   introdurre una nuova variabile, la si imposta ad un valore iniziale
   che viene decrementato ogni secondo e, quando questa raggiunge lo zero,
   interrompiamo il gioco...
 * questo script può essere assegnato a qualunque sprite, anche allo sfondo!
 * creare una nuova variabile _timp_, quindi:

    ![](scripts\timp.png)

[//]: # (        cuant che si cliche su P                                      )
[//]: # (        puarte [timp] a [30]                                          )
[//]: # (        par simpri                                                    )
[//]: # (          spiete (1) seconts                                          )
[//]: # (          mude [timp] di (-1)                                         )
[//]: # (          se <(timp) = [0]> alore                                     )
[//]: # (            ferme [dut]                                               )

## Altri spunti

 * aggiungere una schermata finale al gioco;
 * il gatto ingrassa e rallenta mano a mano che fa scorpacciata di topolini;
 * aumentare il numero di topolini che si muovono sullo schermo (cfr. cloni);
 * il topolino sparisce se il gatto non lo cattura entro 3 secondi;
 * controllare gli spostamenti del gatto con i tasti freccia anziché il mouse;
 * aggiungere un nuovo sprite che il gatto deve evitare, pena...
 * ...
