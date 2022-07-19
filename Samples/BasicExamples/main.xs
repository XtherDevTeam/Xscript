native_class IO in "libio.xnc.so";
native_class String in "libstring.xnc.so";

def main () {
    var Str = String.fromBuffer("こんにちは、 世界。 你好，世界。 Hello, world. Neihou, Saaigaai.");
    IO.printString(Str);
    return 0;
}