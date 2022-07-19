native_class IO in "libio.xnc.so";
native_class String in "libstring.xnc.so";

class MemFuck {
    def constructor () {
        def A in this;
        this.A = 114514;
        return this;
    }
};

def main () {
    var n = 0;
    while (n < 1048577) {
        var MemFucker = new MemFuck.constructor();
        n += 1;
    }
    return 0;
}