Titolo

Sviluppo di un framework di unit-test C++

Abstract

Nel mio intervento illustro l'evoluzione un framework di unit-test in C++
sviluppato in proprio. Spiego le ragioni che hanno portato alla decisione di
realizzarlo in casa, i limiti che l'uso nel tempo ha messo in evidenza e il
modo con cui sono stati affrontati e superati. Buona parte dell'intervento
è focalizzata sulla presentazione delle tecniche implementative. Al termine,
un confronto ragionato con googletest.

Scaletta

1. presentazione del contesto in cui è nato gut
2. ragioni che hanno portato alla decisione di sviluppare gut
3. linee guida della realizzazione del primo prototipo
4. limiti del prototipo che hanno portato a gut
5. esempio realistico di test case gut
6. dettagli implementativi /1: test, suite
7. dettagli implementativi /2: meccanismo di valutazione e logging delle espressioni
8. dettagli implementativi /3: configurabilità dei report
9. gut e googletest

I primi quattro punti necessitano di pochi minuti. L'idea è di giungere
rapidamente all'esempio di unit-test, che mi permette di mostrare le
caratteristiche di gut che ritengo più utili; lo stesso esempio lo userei come
spunto per presentare di volta in volta un differente dettaglio implementativo.
La parte più tecnica prenderebbe il resto del tempo, con l'accortezza, dovessi
sforare, di interrompere l'esposizione a un paio di minuti dalla fine per
lasciar spazio al confronto con googletest.








## Premessa

 Dal waterfall al fallimento
 
 * primi anni 2000
 * sviluppo di servizi server-side
 * processo waterfall
 * solo test manuali:
    * effettuati dal reparto QA
    * a discrezione del singolo sviluppatore
 * l'azienda fallisce
 * un cliente decide di riprovarci

## Motivazioni

 Per serenità: i test devono trasmettere sicurezza

 Scopriremo che:
 
 * consentono il refactoring
   "e se un domani..." diventa sempre più raro nelle discussioni tecniche
 * se scritti bene, documentano (monolitico/procedurale vs. specifica)
 * hanno un effetto benefico sul disaccoppiamento
   disaccoppiamento -> estendibilità/configurabilità

## Contesto di lavoro

 * strumenti di sviluppo:
    * editor
    * console
    * altro: ctags, ...
 * organizzazione del codice:
    * da collezione di oggetti COM...
    * ... a stratificazione di librerie statiche
 * obiettivi:
    * multi-piattaforma (Windows/Linux)
    * multi-compilatore (VC/MinGW)
    * multi-architettura (x86/x64)

## Preparazione al testing

 * nessuna esperienza di testing automatico
 * idee approssimative di cosa servisse *veramente*
 * anche poco era abbastanza!
 
 * quando si scrivono i test?
     * test-after, test-first, TDD, ...
 * come si scrivono i test?
     * setup, exercise, verify, teardown
     * sut, doc, tdo
 * cosa si deve verificare?
     * unit, component, system, acceptance, ...
     * regression-test
     * test non funzionali:
         * prestazioni
         * gestione delle risorse (es. memory leaks)
         * resilienza (es. assenza di rete)
 * al tempo tanti aspetti non erano così ben codificate come oggi

## Desiderata

 * utilizzabile da console
 * portabile
 * impatto minimo, possibilmente un include e via
   (brutte esperienze pregresse con inquinamento da macro
    e opzioni di compilazione incompatibili/indesiderate,
    necessità di ricompilare per le varie piattaforme/toolchain)
 * gestione delle eccezioni (indigestione da HRESULT)
 * no alle macro differenziate
   ASSERT_DOUBLES_EQUAL, ASSERT_INT_EQUAL, ASSERT_STRING_EQUAL, ...
   considerate potenzialmente "instabili"
 * output facilmente parserizzabile o configurabile per reportistiche di c.i.
   nel caso avessimo deciso di proseguire il build anche in caso di un errore
 * non esisteva una scelta "mainstream", così...

## Un proto-framework di test

 * criterio fondante:
   in caso d'errore il test-case lancia un'eccezione

 * un test case è un file cpp con un main:

        [TestMyClass.cpp]
        #include
        
        int main() {               >>> TEST_BEGIN
          try {
        
            // test body
        
          } catch (const Exception& e) {
            /* si giunge qui se:
             * a) una condizione di test è fallita
             * b) il codice sotto test ha sollevato un'eccezione
             * in entrambi i casi il test è considerato fallito
             */
            return -1;
          }
          return 0;
        }                            >>> TEST_END
    
   Il programma di test esce al primo errore. Al tempo fu ritenuto accettabile,
   considerato il livello di paranoia dovuto al modo di lavorare precedente!

 * c'è una macro per la verifica di espressioni booleane:

            ASSERT(expr)
            d:\projects\...\TestMyClass.cpp(79) : test error
        
 * c'è un "pattern" per la verifica del sollevamento di eccezioni:

            try {
              // code that should throw
              TEST_ERROR
            } catch (const ExpectedException&) {
            }
        
        d:\projects\...\TestMyClass.cpp(145) : exception expected

## Limiti

 * il messaggio d'errore generico costringeva spesso e volentieri a:

        // std::cout << i << "\n";
        ASSERT(i == 42)

   Cominciava a diventare un'ossessione...

 * terminazione del test al primo errore

 * cattura esplicita delle eccezioni

 * la suite è implicita
   si è indotti a scrivere test monolitici

## La nascita di GUT

* stampare l'espressione originale e i valori in gioco

        CHECK(i == 42);
        d:\projects\...\TestMyClass.cpp(79): i == 42 evaluates to 7 == 42

* ovviare al pattern per la verifica dell'eccezione:

        THROWS(code_that_should_throw());

* segmentare il test per scoraggiare test monolitici

* proseguire nel test in caso di fallimento

## Esempio

* ...

## Fonti d'ispirazione

* da Kevlin Henney l'idea della cattura dell'espressione invalida

* da Sean Parent il polimorfismo senza ereditarietà per i report

* da Phil Nash l'idea del CHECK/REQUIRE

* SFINAE per il rendering delle espressioni unarie

## Dettagli implementativi

"strano": girano tutti su tre variabili statiche: Expression::last, Suite::tests_, theReport::report_;


cos'è un test: (nome, funzione void)

typedef void (*TestFn)();

class Test {
	std::string name_;
	TestFn test_;
public:
	Test(const std::string& name, TestFn test) : name_(name), test_(test) {
	}
	const std::string& name() const {
		return name_;
	}
	void run() {
		test_();
	}
};

class Suite {
	static std::vector<Test> tests_;
public:
	struct add {
		add(const std::string& name, TestFn test) {
			tests_.push_back(Test(name, test));
		}
	};
	static const std::vector<Test>& tests() {
		return tests_;
	}
};

TEST("a test") {
  // test body
}


#define TEST(name_) \
	static void MAKE_UNIQUE(test_)(); \
	gut::Suite::add MAKE_UNIQUE(testAddition_)(name_, &CONCAT_(test_, __LINE__)); \
	static void MAKE_UNIQUE(test_)()

static void test_42();
gut::Suite::add testAddition_42("a test", test_42); <--- oggetto temporaneo!
static void test_42() {
  // test body
}

nella suite è stato inserita l'associazione ("a test", test_42)
non resta che ciclare sui test, registrando le anomalie:


int runTests_() {
	theReport::start();
	for (auto test : Suite::tests()) {
		theReport::startTest(test.name());
		try {
			test.run();
		} catch(const std::exception& e_) {
			theReport::failure(FatalUnexpectedExceptionFailure(e_));
		} catch(...) {
			theReport::failure(FatalUnknownExceptionFailure());
		}
		theReport::endTest();
	}
	theReport::end();
	return theReport::failedTestCount();
}

int main() {
  return runTests_();
}


CATTURA


A fronte di:

        int i = 1;
        int j = 2;
        CHECK(i == j);

mi aspetto qualcosa tipo:

        d:\projects\...\TestMyClass.cpp(79): i == j evaluates to 1 == 2

Cos'è CHECK?

        #define CHECK(expr_) \
          do { \
            if (!(gut::Capture()->*expr_)) \
              gut::theReport::failure(gut::CheckFailure(#expr_, gut::Expression::last, __FILE__, __LINE__)); \
          } while (0)

Gran parte di gut sta in quelle due righe:

 * cattura dell'espressione
 * aggiornamento del report

## Cattura

Semplifichiamo:

        if (!(gut::Capture()->*expr_)) \
          std::err << #expr_ << " evaluates to " << gut::last_capture; \

`gut::Capture()->*expr_` valuta il valore di verità dell'espressione e 
 ha come effetto collaterale l'istanziazione della stringa statica
 (thread-safety addio!) `gut::last_capture` a `1 == 2`.

* `#expr_` rappresenta l'espressione letterale (`i == j`)

* come si arriva a `1 == 2`?

        gut::Capture()->*expr_

 * un oggetto temporaneo di tipo `gut::Capture` con operatore di puntatore-a-membro:
    * è usato di rado
    * ha priorità più alta rispetto a tutti gli operatori relazionali

        gut::Capture()->*expr_

diventa:

        gut::Capture()->*i == j

cioè:

        gut::Capture()->*(i) == j

se l'`operator->*` di `gut::Capture` torna un oggetto ausiliario `Term`:

        template<typename T>
        Term<T> Capture::operator->*(const T& term) {
            return Term<T>(term);
        }

allora si ha:

        Term<int>(i) == j

se si salva i nel costruttore, nell'`operator==` abbiamo a disposizione i valori
dei due termini:

        template<typename T>
        class Term {
          const T& lhs_;
        public:
          Term::Term(const T& lhs) : lhs_(lhs) { }
          template<typename U>
          bool Term::operator==(const U& rhs) const {
            // so quanto vale i
            // so quanto vale j
            // so che è un ==
          }
        };

Tutto il resto è infrastruttura per:

  1) specializzazione della funzione di confronto per eliminare warning
     (es. warning signed/unsigned) o in assenza di conversioni implicite
     (es. puntatore/intero, puntatore/nullptr, etc.)

              return lhs_ == rhs; // warning!


          bool Term::operator==(const U& rhs) const {
              return compare<e_equal>(lhs_, rhs); <--- si occupa indirettamente della stringa statica
          }

 il compare astrae dall'operatore relazionale, ha lo scopo di "aggiustare" i tipi
 e chiamare il compare generico:

        // signed/unsigned
        template<Operator op>
        bool compare(unsigned int lhs, int rhs) {
          return compare<op>(static_cast<unsigned int>(lhs), rhs);
        }

cosa fa il "vero" compare?

    istanzia un oggetto `ExprFactory` che istanzia l'espressione `op`
    alla quale chiede di loggare i due valori e valutare l'espressione

        template<Operator op, typename T, typename U>
        bool compare(const T& lhs, const U& rhs) {
          return ExprFactory<T, U, op>::logAndEvaluate(lhs, rhs);
        }

  2) `ExprFactory` si occupa della costruzione dell'espressione
     rispetto all'operatore: ho i valori, 1 e 2; che simbolo ci devo mettere in
     mezzo? secondo quale criterio devo confrontarli?

        template<typename T, typename U>
        struct ExprFactory<T, U, e_equal> {
          static bool logAndEvaluate(const T& lhs, const U& rhs) {
            return Equal<T, U>(lhs, rhs).logAndEvaluate();
          }
        };

        template<typename T, typename U>
        struct ExprFactory<T, U, e_lessThan> {
          static bool logAndEvaluate(const T& lhs, const U& rhs) {
            return LessThan<T, U>(lhs, rhs).logAndEvaluate();
          }
        };

    `Equal` e `LessThan` sono due classi derivate da `Expression`, il cui metodo
    `logAndEvaluate` prevede:
    
        struct Expression {
          static std::string last;
          virtual ~Expression() { }
          virtual bool evaluate() const = 0;
          virtual std::string toString() const = 0;
          bool logAndEvaluate() {
            Expression::last = toString();
            return evaluate();
          }
        };

una classe intermedia cattura lhs e rhs:

        template<typename T, typename U>
        class BinaryExpression : public Expression {
        protected:
          const T& lhs_;
          const U& rhs_;
        public:
         BinaryExpression(const T& lhs, const U& rhs) : lhs_(lhs), rhs_(rhs) { }
         virtual std::string toString() const {
           return gut::toString(lhs_) + " " + getOpName() + " " + gut::toString(rhs_);
         }
         virtual std::string getOpName() const = 0;
        };

`Equal` e `LessThan` non devono far altro che fornire il valore di verità e il simbolo dell'operatore implementato:

        template<typename T, typename U>
        struct Equal : public BinaryExpression<T, U> {
          Equal(const T& lhs, const U& rhs) : BinaryExpression<T, U>(lhs, rhs) { }
          virtual bool evaluate() const { return lhs_ == rhs_; }
          virtual std::string getOpName() const { return "=="; }
        };

        template<typename T, typename U>
        struct LessThan : public BinaryExpression<T, U> {
          LessThan(const T& lhs, const U& rhs) : BinaryExpression<T, U>(lhs, rhs) { }
          virtual bool evaluate() const { return lhs_ < rhs_; }
          virtual std::string getOpName() const { return "<"; }
        };

`BinaryExpression` mette insieme il tutto

booleani
più semplice, ci pensa direttamente l'operator bool() di Term a istanziare una UnaryExpression
(non ci sono tipi da allineare nè operatori da etichettare)

toString -> in genere si passa per ostringstream
per i primitivi c'è della personalizzazione, per evidenziare il tipo (signed, long, ...)
per le stringhe si potrebbe differenziare tra std::string e (const) char*
per fare lo stream personalizzato dei propri oggetti, basta fornire l'operator<<

    std::ostream& operator<<(std::ostream& os, const MyType& _)

se non c'è, viene emesso {?}
per gli oggetti convertibili a bool il toString non è applicabile
(ambiguità di operator<< su bool/int), per cui c'è un giro "strano" che
se l'oggetto è convertibile a std::string si fa, se no boolalpha << static_cast<bool>(obj)



// operatori non supportati, es. CHECK (i % j) ==> parentesi
// UNEXPECTED_ASSIGNMENT

## Report polimorfici senza ereditarietà

esiste un'interfaccia implicita, tipo policy:

    void start()
    void end()
    void startTest(const std::string& name)
    void endTest()
    void failure(const Notice& failure)
    void eval(const Notice& eval)
    void info(const Notice& info)
    void warn(const Notice& warn)
    void quit(const std::string& report)

    // si implementa il comportamento desiderato
    struct MyReport {
      void failure(...);
    }

infine:

    GUT_ENABLE_REPORT(MyReport)

in caso d'errore:

        gut::theReport::failure(...);

come fa?

theReport è un proxy verso un Report statico
come fa MyReport a diventare un Report?!
Report è un wrapper di un qualunque oggetto che implementi l'interfaccia implicita

l'interfaccia implicita ne origina una virtuale


    struct Concept {
      virtual void failure(...) = 0;
    };

si introduce un pimpl:

    template<class T>
    struct Model : public Concept {
      T pimpl_;
      Model(T report) : report_(report) { }
      virtual void failure(...) {
        pimpl_.failure(...);
      }
    };

basta iniettare il mio report in un Model apposito:

    MyReport myReport;
    Model model (myReport);
    model.failure(...); -> chiamerà myReport.failure()

## Gut vs googletest

 * coprono le esigenze di base in modo molto simile
   [confronto di uno stesso caso di test nei due framework]

aspetti critici di googletest:

 * è una libreria statica (e necessita di pthreads)
 * nella cattura delle eccezioni non consente di verificare il what
 
googletest in più ha:

 * fixtures
 * piu test-case per file: TEST(test_case_name, test_name)
    per gut c'è un unico test_case implicito a livello di file
    per me va anche bene, perché di norma ho:
     * 1 test per classe
     * 1 test per ogni funzionalità verticale
     * 1 test per ogni baco
 * filtro sui test da eseguire
 * test listeners
   intrigante, ma serve?
   l'oggetto report potrebbe essere considerato un proto-listener?
 * test parametrici
     * sul tipo
     * su valore
 * shuffling dei test
 per verificare l'indipendenza dall'ordine di definizione
 * break_on_failure
 * ripetizione del test
 per test che falliscono di tanto in tanto, per poter entrare nel debugger
 * death tests
