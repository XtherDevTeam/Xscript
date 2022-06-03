var i = 0;

class ClassA {
    public def test () {
        return this.test();
    }
};

def Hello (j) {
    i = 114514;
    i += j;
    return Hello(j+1);
}