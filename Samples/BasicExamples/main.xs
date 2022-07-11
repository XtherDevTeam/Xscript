var i = 0;

class ClassA {
    public def test () {
        return this.test();
    }
};

def main () {
    var i = 0;
    i = 114514;
    var j = 1;
    j = i + 1919810;
}