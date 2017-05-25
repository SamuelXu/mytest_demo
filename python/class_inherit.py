#!env python

class A(object):
    def aprint(self):
        self.name="father"
        print self.name


class B(A):
    def bprint(self):
        self.aprint()
        self.name="child1"
        print self.name

class C(A):
    def cprint(self):
        self.name="child2"
        self.aprint()
        print self.name

b = B()
b.bprint()
c = C()
c.cprint()

