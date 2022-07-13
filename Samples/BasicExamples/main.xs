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
    var string_object_hello = "Hello";
    var string_object_world = ", world!";
    return string_object_hello + string_object_world;
}