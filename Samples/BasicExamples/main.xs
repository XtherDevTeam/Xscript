import "package_test";

var i = 0;

class ClassA {
    def test () {
        return 11451419;
    }

    def constructor () {
        return this; // whatever you return, but you must return a value.
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
    return Class.test();
}