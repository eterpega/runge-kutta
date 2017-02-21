//------------------------------------------------------------------------
#include <math.h>
#include <iostream>
#include <fstream>
//------------------------------------------------------------------------
const double A = 2.0, B = 3.0, C = 4.0, D = 5.0;
const double dt = 0.05;
//------------------------------------------------------------------------
struct Vars {
  double x;
  double y;
  Vars (double nx, double ny) {
    x = nx;
    y = ny;
  }
  Vars () {
    x = 0.0;
    y = 0.0;
  }
  Vars operator+(const Vars &v) {
    return Vars(x + v.x, y + v.y);
  }
  Vars operator*(const double f) {
    return Vars(x * f, y * f);
  }
};
//------------------------------------------------------------------------
class LotkaVolterra {
public:
  class Diff {
  public:
    Vars operator()(Vars s) {
      Vars dx;
      dx.x = s.x * (A - B * s.y);
      dx.y = s.y * (C * s.x - D);
      return dx;
    }
  };
  class H {
  public:
    double operator()(Vars v) {
      return C * v.x + B * v.y - D * log(v.x) - A * log(v.y);
    }
  };
};
//------------------------------------------------------------------------
class HarmonicOscillator {
public:
  class Diff {
  public:
    Vars operator()(Vars s) {
      Vars dx;
      dx.x = - s.y;
      dx.y = s.x;
      return dx;
    }
  };
  class H {
  public:
    double operator()(Vars v) {
      return v.x * v.x + v.y * v.y;
    }
  };
};
//------------------------------------------------------------------------
class Diff2 {
public:
  Vars operator()(Vars s) {
    Vars dx;
    dx.x = -s.y;
    dx.y = s.x;
    return dx;
  }
};
//------------------------------------------------------------------------
double
H(Vars &v) {
  return C * v.x + B * v.y - D * log(v.x) - A * log(v.y);
}
//------------------------------------------------------------------------
double
H2(Vars &v) {
  return v.x * v.x + v.y * v.y;
}
//------------------------------------------------------------------------
template <class DIFF>
class RungeKutta {
private:
  const double dt;
  const double hdt;
  DIFF diff;
public:
  RungeKutta(double _dt) : dt(_dt), hdt(_dt * 0.5) {};
  Vars operator()(Vars v) {
    Vars k1 = diff(v);
    Vars k2 = diff(v + k1 * hdt);
    Vars k3 = diff(v + k2 * hdt);
    Vars k4 = diff(v + k3 * dt);
    v = v + (k1 + k2 * 2.0 + k3 * 2.0 + k4) * (dt / 6.0);
    return v;
  }
};
//------------------------------------------------------------------------
template <class DIFF>
class Euler {
private:
  const double dt;
  DIFF diff;
public:
  Euler(double _dt) : dt(_dt) {};
  Vars operator()(Vars v) {
    v = v + diff(v) * dt;
    return v;
  }
};
//------------------------------------------------------------------------
template <class Method, class H>
void integrate(Method f, H h, const char * filename) {
  Vars v(1.0, 1.0);
  double t = 0;
  std::ofstream ofs(filename);
  std::cout << filename << std::endl;
  for (int i = 0; i < 200; i++) {
    t += dt;
    v = f(v);
    ofs << t << " ";
    ofs << v.x << " ";
    ofs << v.y << " ";
    ofs << h(v) << std::endl;
  }
}
//------------------------------------------------------------------------
int
main(void) {
  integrate(RungeKutta<LotkaVolterra::Diff>(dt), LotkaVolterra::H(), "lv_rk.dat");
  integrate(Euler<LotkaVolterra::Diff>(dt), LotkaVolterra::H(), "lv_euler.dat");
  integrate(RungeKutta<HarmonicOscillator::Diff>(dt), HarmonicOscillator::H(), "ho_rk.dat");
  integrate(Euler<HarmonicOscillator::Diff>(dt), HarmonicOscillator::H(), "ho_euler.dat");
}
//------------------------------------------------------------------------
