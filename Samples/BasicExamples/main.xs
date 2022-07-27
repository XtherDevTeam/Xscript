native_class IO in "libio.xnc.so";
native_class String in "libstring.xnc.so";

class MemFuck {
    def constructor () {
        def A in this;
        this.A = String.fromBuffer("aaa");
        return this;
    }
};

def main () {
    var Str = String.fromBuffer("こんにちは、 世界。 你好，世界。 Hello, world. Neihou, Saaigaai.");
    IO.println(Str);
    var n = 0;
    while (n < 10000000000000) {
        var MemFucker = new MemFuck.constructor();
        n += 1;
    }
    return 0;
}