class B {
  virtual void f() {}
};

class V {
  virtual void g() {}
};

class X {
};

class D : public B, virtual public V, virtual public X {
};

int challenge1() {
  D d;

  B* pb = &d;
  D* p1 = (D*)pb;
  D* p2 = dynamic_cast<D*>(pb);

  V* pv = &d;
  D* p3 = (D*)pv;
  D* p4 = dynamic_cast<D*>(pv);

  X* px = &d;
  D* p5 = (D*)px;
  D* p6 = dynamic_cast<D*>(px);

  return 0;
}


int main()
{
  challenge1();
  return 0;
}
