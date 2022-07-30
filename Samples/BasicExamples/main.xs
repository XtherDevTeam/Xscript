native_class IO in "libio.xnc.so";
native_class String in "libstring.xnc.so";
native_class Array in "libarray.xnc.so";
native_class Thread in "libthread.xnc.so";

def main () {
    var uf = func (a, b) {
        IO.println(String.fromBuffer("Konnichiha, Sekai. ThreadID: ") + String.fromInt(Thread.id()) + 
                    String.fromBuffer(" a: ") + String.fromInt(a) + String.fromBuffer(" b: ") + String.fromInt(b));
        return a + b;
    };
    var tid = Thread.start(uf, 114, 514);
    var result = Thread.getResult(tid);
    IO.println(String.fromBuffer("Thread execution result: ") + String.fromInt(result));
    IO.println(String.fromBuffer("Hello from main function."));
    return 0;
}