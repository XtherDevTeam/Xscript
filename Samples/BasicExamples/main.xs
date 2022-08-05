native_class IO in "libio";
native_class String in "libstring";
native_class Array in "libarray";
native_class Thread in "libthread";

/* Comment test */
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