/*
 1. free functions & static member functions
 2. member functions
 3. function objects
 4. lambdas




Sergey Ryazanov
The Impossibly Fast C++ Delegates
http://www.codeproject.com/Articles/11015/The-Impossibly-Fast-C-Delegates

Oliver Mueller
C++ Delegates On Steroids
http://blog.coldflake.com/posts/2014-01-12-C%2B%2B-delegates-on-steroids.html


Karel Lodewijk
Fun with functions 
http://www.dreamincode.net/forums/topic/264061-c11-fun-with-functions/

meh.
C++11 lambda to function pointer or std::function 
http://meh.schizofreni.co/programming/magic/2013/01/23/function-pointer-from-lambda.html

Functional C++
Function Traits
http://functionalcpp.wordpress.com/2013/08/05/function-traits/

*/

#include <iostream>
#include <functional>

template<typename R, typename... Args>
class Delegate {
    typedef std::function<R(Args...)> Fn;
    Fn fn_;
    template<class T>
    struct MemberFnCall {
        T* obj_;
        typedef R (T::*Fn)(Args...);
        Fn fn_;
        MemberFnCall(T* obj, Fn fn) : obj_(obj), fn_(fn) { }
        R operator()(Args... args) const {
            return (obj_->*fn_)(args...);
        }
    };
    // per supportare membri const, vedi main #8
    template<class T>
    struct ConstMemberFnCall {
        const T* obj_;
        typedef R (T::*Fn)(Args...) const;
        Fn fn_;
        ConstMemberFnCall(const T* obj, Fn fn) : obj_(obj), fn_(fn) { }
        R operator()(Args... args) const {
            return (obj_->*fn_)(args...);
        }
    };
public:
    Delegate(Fn fn) : fn_(fn) { }
    template<class T>
    Delegate(T* obj, R (T::*fn)(Args...)) : fn_(MemberFnCall<T>(obj, fn)) { }
    // per supportare membri const, vedi main #8
    template<class T>
    Delegate(T* obj, R (T::*fn)(Args...) const) : fn_(ConstMemberFnCall<T>(obj, fn)) { }

    R operator()(Args... args) const {
        return fn_(args...);
    }
};

int add(int a, int b) {
    return a + b;
}

struct Math {
    int add(int a, int b) {
        return a + b;
    }

    int const_add(int a, int b) const {
        return a + b;
    }
};

struct AddOp {
    int operator()(int a, int b) { // e se fosse const?! - verificato, cfr. ConstAddOp
        return a + b;
    }
};



#include <cassert>
#include <cstring> // memset

int main1() {
    assert(add(1, 2) == 3);

    auto freeFn = Delegate<int, int, int>(add);
    assert(freeFn(1, 2) == 3);

    auto delegate = freeFn;
    assert(delegate(1, 2) == 3);

    {
        AddOp addOp;
        assert(addOp(1, 2) == 3);

        auto functionObj = Delegate<int, int, int>(addOp);
        assert(functionObj(1, 2) == 3);

        delegate = functionObj;
    }

    assert(delegate(1, 2) == 3);


    auto addLambda = [](int a, int b) { return a + b; };
    assert(addLambda(1, 2) == 3);

{
    auto lambda = Delegate<int, int, int>(addLambda);
    assert(lambda(1, 2) == 3);
    delegate = lambda;
}
    assert(delegate(1, 2) == 3);

{
    auto lambda_ = Delegate<int, int, int>([](int a, int b) { return a + b; });
    assert(lambda_(1, 2) == 3);
    delegate = lambda_;
}

    assert(delegate(1, 2) == 3);




{
    Math math;
    assert(math.add(1, 2) == 3);
    auto memberFn = Delegate<int, int, int>(&math, &Math::add);
    assert(memberFn(1, 2) == 3);
    delegate = memberFn;
    assert(delegate(1, 2) == 3);
}


/*
    Math* math = new Math();
    assert(math->add(1, 2) == 3);
    auto memberFn = Delegate<int, int, int>(math, &Math::add);
    assert(memberFn(1, 2) == 3);
    delegate = memberFn;
    assert(delegate(1, 2) == 3);
    delete math;
    memset(math, 0, sizeof(Math));
    assert(delegate(1, 2) == 3); // errore di protezione!!!
*/


    return 0;
}

// unfortunately template argument deduction only works on template functions (not on class templates).

// un po' di zucchero sintattico, perché se no devo specificare ogni volta i tipi in gioco:

int f1() {
    return 1;
}

void f2(int& i) {
    i = 1;
}

#include <sstream>

std::string f3(double x) {
    std::ostringstream oss;
    oss << "x=" << x;
    return oss.str();
}

int main2() {

    auto d1 = Delegate<int>(f1);
    assert(d1() == 0);

    auto d2 = Delegate<void, int&>(f2);
    int i = 3;
    d2(i);
    assert(i == 1);

    auto d3 = Delegate<std::string, double>(f3);
    assert(d3(3.14) == "x=3.14");

    return 0;
}

/* vorrei:

    auto d1 = Delegate(f1);
    auto d2 = Delegate(f2);
    auto d3 = Delegate(f3);
*/

template<typename R, typename... Args>
Delegate<R, Args...> make_delegate(R(*fn)(Args...)) {
    return Delegate<R, Args...>(fn);
}

template<typename R, typename... Args>
Delegate<R, Args...> make_delegate(std::function<R(Args...)> fn) {
    return Delegate<R, Args...>(fn);
}

int main3() {

    auto d1 = make_delegate(f1);
    assert(d1() == 1);

    auto d2 = make_delegate(f2);
    int i = 3;
    d2(i);
    assert(i == 1);

    auto d3 = make_delegate(f3);
    assert(d3(3.14) == "x=3.14");
    return 0;
}


// ok per le free-functions;
// member functions?

template<class T, typename R, typename... Args>
Delegate<R, Args...> make_delegate(T* obj, R(T::*fn)(Args...)) {
    return Delegate<R, Args...>(obj, fn);
}


int main4() {

    auto d1 = make_delegate(f1);
    assert(d1() == 1);

    auto d2 = make_delegate(f2);
    int i = 3;
    d2(i);
    assert(i == 1);

    auto d3 = make_delegate(f3);
    assert(d3(3.14) == "x=3.14");


    Math math;
    assert(math.add(1, 2) == 3);
    auto d4 = make_delegate(&math, &Math::add);
    assert(d4(1, 2) == 3);
    // TODO: test con un metodo con signature diversa

    return 0;
}


// ok per member functions; functors/lambdas (as lambdas are unnamed class with operator())?
// mi pare di capire sia un casino!


/* meh:

Now, lambdas in C++ are instances of an anonymous class specifically created for each lambda object, this means that two lambdas with the same code are actually different objects.

This also means that you can't pass lambdas around without using a template because there's no lambda type.

Non capturing lambdas (the ones with nothing inside the []) can be converted to their function pointer by casting them with the corresponding signature, while capturing ones can be wrapped in std::function.

The issue arises when you don't know the signature of the lambda, you can only cast knowing the signature, and I didn't want to have to write the parameters twice... <--- ANCH'IO!!!
*/

// da una lambda/functor devo tirar fuori il tipo dell'operatore function-call:


template<class F>
struct function_traits;
 
template<class R, class... Args>
struct function_traits<R(Args...)> {
    typedef R (*signature)(Args...);
};

// function pointer capture as a specialization of <R(Args...)>
template<class R, class... Args>
struct function_traits<R(*)(Args...)> : public function_traits<R(Args...)> {
};
 
//~ float free_function(const std::string& a, int b)
//~ {
    //~ return (float)a.size() / b;
//~ }
 
//~ int main5()
//~ {
    //~ using T1 = function_traits<decltype(add)>;

    //~ auto lambda = [](int a, int b) { return a + b; };
    //~ using T2 = function_traits<decltype(lambda)>;
 
    //~ return 0;
//~ }


/* allora posso usare una funzione helper che la converte in std::function

    auto d2 = make_delegate(to_function(lambda));

che dovrebbe andar bene anche per i functor -
conversione esplicita ma almeno non specifico i tipi..
*/


template <typename FnObj>
struct function_traits : public function_traits<decltype(&FnObj::operator())> {
};

template <typename T, typename R, typename... Args>
struct function_traits<R(T::*)(Args...)> {
    //~ typedef R(*signature)(Args...); va bene per le lambda, ma non per i function object
    typedef std::function<R(Args...)> signature;
};

template <typename FnObj>
typename function_traits<FnObj>::signature to_function (FnObj fnObj) { // no referenza su fnObj se no non posso passare lambda "al volo" (r-value ref)
    return static_cast<typename function_traits<FnObj>::signature>(fnObj);
}

//~ template<typename R, typename... Args>
//~ Delegate<R, Args...> make_delegate_(std::function<R(Args...)> fn) {
    //~ return Delegate<R, Args...>(fn);
//~ }


int main6()
{
    auto d1 = make_delegate(add);
    assert(d1(1, 2) == 3);
 
    //~ auto lambda = [](int a, int b) { return a + b; };
    //~ auto d2 = make_delegate(to_function(lambda));
    //~ assert(d2(1, 2) == 3);

    //~ auto d3 = make_delegate(to_function([](int a, int b) { return a + b; }));
    //~ assert(d3(1, 2) == 3);

    AddOp addOp;
    auto d4 = make_delegate(&addOp, &AddOp::operator());
    assert(d4(1, 2) == 3);

    auto d5 = make_delegate(to_function(addOp));
    assert(d5(1, 2) == 3);

    return 0;
}

// il problema dunque è "solo" il const dell'operator() delle lambda.
// ottengo lo stesso errore di compilazione "no matching function for call"
// se faccio diventare const l'operator() di AddOp

struct ConstAddOp {
    int operator()(int a, int b) const {
        return a + b;
    }
};

// già ci sono casini solo col to_function: 
/*
    auto d5 = to_function(constAddOp); non compila
*/

template <typename T, typename R, typename... Args>
struct function_traits<R(T::*)(Args...) const> {
    typedef std::function<R(Args...)> signature;
};

int main7()
{
    auto d1 = make_delegate(add);
    assert(d1(1, 2) == 3);
 
    auto lambda = [](int a, int b) { return a + b; };
    auto d2 = make_delegate(to_function(lambda));
    assert(d2(1, 2) == 3);

    auto d3 = make_delegate(to_function([](int a, int b) { return a + b; }));
    assert(d3(1, 2) == 3);


    ConstAddOp constAddOp;
    auto d5 = to_function(constAddOp);
    assert(d5(1, 2) == 3);

    auto d6 = make_delegate(to_function(constAddOp));
    assert(d6(1, 2) == 3);

    return 0;
}

// e i metodi const in genere, tipo Math.add const?
/* o equivalentemente:

    ConstAddOp constAddOp;
    auto d_ = make_delegate(&constAddOp, &ConstAddOp::operator());
    assert(d_(1, 2) == 3);
*/

// notare il const!

template<class T, typename R, typename... Args>
Delegate<R, Args...> make_delegate(T* obj, R(T::*fn)(Args...) const) {
    return Delegate<R, Args...>(obj, fn);
}

// con questa funzione, l'errore si sposta da make_delegate al ctor di Delegate...


int main8()
{
    auto d1 = make_delegate(add);
    assert(d1(1, 2) == 3);
 
    auto lambda = [](int a, int b) { return a + b; };
    auto d2 = make_delegate(to_function(lambda));
    assert(d2(1, 2) == 3);

    auto d3 = make_delegate(to_function([](int a, int b) { return a + b; }));
    assert(d3(1, 2) == 3);


    ConstAddOp constAddOp;
    auto d5 = to_function(constAddOp);
    assert(d5(1, 2) == 3);

    auto d6 = make_delegate(to_function(constAddOp));
    assert(d6(1, 2) == 3);

    auto d7 = make_delegate(&constAddOp, &ConstAddOp::operator());
    assert(d7(1, 2) == 3);


    Math math;
    assert(math.add(1, 2) == 3);
    auto d8 = make_delegate(&math, &Math::add);
    assert(d8(1, 2) == 3);

    auto d9 = make_delegate(&math, &Math::const_add);
    assert(d9(1, 2) == 3);

    return 0;
}


// adesso si incasina se due membri sono uno costante, l'altro no:

struct ConstOverride {
    int f(double /*x*/) {
        return 0;
    };
    int f(double /*x*/) const {
        return 1;
    };
};

int main9()
{
    ConstOverride constOverride;
    auto d1 =
        make_delegate(
            &constOverride,
            static_cast<int (ConstOverride::*)(double)>(&ConstOverride::f));
    assert(d1(3.14) == 0);
    auto d2 =
        make_delegate(
            &constOverride,
            static_cast<int (ConstOverride::*)(double) const>(&ConstOverride::f));
    assert(d2(3.14) == 1);
    return 0;
}


// in genere si incasina se i due metodi hanno signature differente:

struct Override {
    int f(double /*x*/) {
        return 0;
    };
    int f(const std::string& /*s*/) {
        return 1;
    };
};

int main10()
{
    Override override;
    auto d1 =
        make_delegate(
            &override,
            static_cast<int (Override::*)(double)>(&Override::f));
    assert(d1(3.14) == 0);
    auto d2 =
        make_delegate(
            &override,
            static_cast<int (Override::*)(const std::string&)>(&Override::f));
    assert(d2("acme") == 1);
    return 0;
}




// static member function!!!

struct Static {
    static int f() {
        return 3;
    }
};

int main11()
{
    auto d1 = make_delegate(&Static::f);
    assert(d1() == 3);
    return 0;
}


// si riesce ad eliminare la chiamata esplicita to_function???

template<class Fn>
auto make_delegate(Fn fn) -> decltype(make_delegate(to_function(fn))) {
    return make_delegate(to_function(fn));
}





int main()
{
    auto d1 = make_delegate(add);
    assert(d1(1, 2) == 3);
 
    auto lambda = [](int a, int b) { return a + b; };
    auto d2 = make_delegate(to_function(lambda));
    assert(d2(1, 2) == 3);

    auto d3 = make_delegate(to_function([](int a, int b) { return a + b; }));
    assert(d3(1, 2) == 3);

    AddOp addOp;
    auto d5 = make_delegate(addOp);
    assert(d5(1, 2) == 3);

    ConstAddOp constAddOp;
    auto d6 = make_delegate(constAddOp);
    assert(d6(1, 2) == 3);

    return 0;
}

