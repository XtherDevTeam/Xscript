var i = 0;

class ClassA {
    public def test () {
        return this.test();
    }
};

def add_number(a, b) {
    return a + b;
}

def main () {
    return add_number(1+1+4, 514);
}