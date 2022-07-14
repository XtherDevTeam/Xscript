import "package_test";

var i = 0;

class ClassA {
    public def test () {
        return this.test();
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
    return @{"package_test"} -> test;
}