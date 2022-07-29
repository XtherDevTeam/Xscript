native_class IO in "libio.xnc.so";
native_class String in "libstring.xnc.so";
native_class Array in "libarray.xnc.so";

def main () {
    var uf = func () {
        IO.println(String.fromBuffer("Hello from unnamed function."));
        return 0;
    };
    uf();
    IO.println(String.fromBuffer("Hello from main function."));
    return 0;
}