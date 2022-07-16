import "package_test";

var i = 0;

class ExtendTest {
    def constructor () {
        def proto in this;
        this.proto = 520;
        return this;
    }
};

class ClassA extends (ExtendTest) {
    def test () {
        return 11451419;
    }

    def constructor () {
        ExtendTest.constructor(this);
        def t in this;
        this.t = 11451419198;
        return this;
    }
};

def add_number(a, b) {
    return a + b;
}

def fib(a) {
    if (a < 3) {
        return 1;
    } else {
        return fib(a - 1) + fib(a - 2);
    }
}

def main () {
    var Class = new ClassA.constructor();
    return Class.proto;
}