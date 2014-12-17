/*

Type erasure in tre passi

Devo poter ricevere un oggetto che implementa una policy, es. `string f(int)`

1) definisco una classe che contiene l'oggetto che implementa l'interfaccia:

template<typename T>
struct Model {
  T object_;
  Model(T object) : object_(object) { }
  std::string f(int i) { return object_.f(i); }
};

Ora posso usare Model<T>(object) al posto di object, ma voglio slegarmi da T.
Idea: accedere a Model<T> tramite un puntatore a una classe base non tipizzata.
Come? In due passaggi:

2) introduco una classe base che definisce l'interfaccia:

struct Concept {
  virtual std::string f(int i) = 0;
};

template<typename T>
struct Model : Concept {
  T object_;
  Model(T object) : object_(object) { }
  std::string f(int i) override { return object_.f(i); }
};

3) definisco il contenitore "agnostico" che implementa la policy:

struct Container {
  std::shared_ptr<Concept> object_;
  template<class T>
  Container(T object) : object_ (std::make_shared<Model<T>>(object)) { }
  std::string f(int i) { return object_->f(i); }
};

Container può ospitare qualunque oggetto che implementi la policy iniziale!
*/


#include <iostream>
#include <memory>

struct A {
  std::string f(int i) { return "A::f(" + std::to_string(i) + ")"; }
};

struct B {
  std::string f(int i) { return "B::f(" + std::to_string(i) + ")"; }
};

// passo 1: definire un contenitore che possa contenere A e B
/*
template<typename T>
struct Model {
  T object_;
  Model(T object) : object_(object) { }
  std::string f(int i) { return object_.f(i); }
};
*/

// passo 2: 

struct Concept {
  virtual std::string f(int) = 0;
};

template<typename T>
struct Model : Concept {
  T object_;
  Model(T object) : object_(object) { }
  std::string f(int i) override { return object_.f(i); }
};

struct Container {
  std::shared_ptr<Concept> object_;
  template<class T>
  Container(T object) : object_ (std::make_shared<Model<T>>(object)) { }
  std::string f(int i) { return object_->f(i); }
};

int main() {
  A a;
  B b;
  std::cout << a.f(0) << std::endl;
  std::cout << b.f(0) << std::endl;

// passo 1
  Model<A> a1(a);
  Model<B> b1(b);
  std::cout << a1.f(0) << std::endl;
  std::cout << b1.f(0) << std::endl;

// non basta! il tipo del contenitore dipende ancora dal tipo!

// passo 2 - Concept - il programma regge ancora...
  std::shared_ptr<Model<A>> a2 = std::make_shared<Model<A>>(a);
  std::shared_ptr<Model<B>> b2 = std::make_shared<Model<B>>(b);
  std::cout << a2->f(0) << std::endl;
  std::cout << b2->f(0) << std::endl;

// passo 3 - introduzione del contenitore "agnostico"
  Container a3(a);
  Container b3(b);
  std::cout << a3.f(0) << std::endl;
  std::cout << b3.f(0) << std::endl;
}
