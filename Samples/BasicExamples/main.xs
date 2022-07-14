import "package_test";

var i = 0;

class ClassA {
    def test () {
        return this.test();
    }

    def constructor () {
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
    return @{"package_test"} -> test_func(1+1+4);
}