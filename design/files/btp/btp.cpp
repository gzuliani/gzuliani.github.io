#include <cassert>
#include <cmath>

struct Pagamento {
  int rateAnnuali;
public:
  Pagamento(int rateAnnuali_) : rateAnnuali(rateAnnuali_) { }
};

struct PagamentoAnnuale : public Pagamento {
  PagamentoAnnuale() : Pagamento(1) { }
};

struct PagamentoSemestrale : public Pagamento {
  PagamentoSemestrale() : Pagamento(2) { }
};

class Interesse {
  const double valore_;
protected:
  double valore() const {
    return valore_;
  }
public:
  explicit Interesse(double i) : valore_(i) { }
  Interesse(double i, double mu, double ribor) : valore_(i - (mu - ribor)) { }
  virtual double attualizzazione(double anni) const = 0;
};

struct InteresseDiscreto : public Interesse {
  explicit InteresseDiscreto(double i) : Interesse(i) { }
  InteresseDiscreto(double i, double mu, double ribor) : Interesse(i, mu, ribor) { }
  virtual double attualizzazione(double anni) const {
    return pow(1 + valore(), anni);
  }
};

struct InteresseContinuo : public Interesse {
  InteresseContinuo(double i, double mu, double ribor) : Interesse(i, mu, ribor) { }
  virtual double attualizzazione(double anni) const {
      return exp(valore() * anni);
  }
};

class Titolo {
  const double capitale_;
  const double cedola_;
  const int scadenza_;
  Pagamento pagamento_;
public:
  Titolo(double capitale, double cedola, int scadenza, Pagamento pagamento)
    : capitale_(capitale), cedola_(cedola),
      scadenza_(scadenza), pagamento_(pagamento) {
  }
  double prezzo(int anno, const Interesse& interesse) const {
    const double pagamento = capitale_ * cedola_ / pagamento_.rateAnnuali;
    const double anni = scadenza_ - anno + 1.;
    double cumulo = capitale_;
    for (double i = 0; i < anni; i += 1. / pagamento_.rateAnnuali)
      cumulo += pagamento * interesse.attualizzazione(i);
    return cumulo / interesse.attualizzazione(anni);
  }
};

int main() {

  Titolo btp(100, 0.1, 2011, PagamentoAnnuale ());
  assert(fabs(btp.prezzo(2008, InteresseDiscreto(0.15)) - 85.73) < 0.01);

  Titolo btz(100, 0.1, 2011, PagamentoAnnuale ());
  assert(fabs(btz.prezzo(2008, InteresseDiscreto(0.15, 0.10, 0.12)) - 80.79) < 0.01);

  Titolo btz_c(100, 0.1, 2011, PagamentoAnnuale ());
  assert(fabs(btz_c.prezzo(2008, InteresseContinuo(0.10, 0.10, 0.12)) - 91.78) < 0.01);

  Titolo btp_s(100, 0.1, 2009, PagamentoSemestrale());
  assert(fabs(btp_s.prezzo(2008, InteresseDiscreto(0.10)) - 100.42) < 0.01);

  return 0;
}
