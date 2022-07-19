native_class IO in "libio.xnc.so";
native_class String in "libstring.xnc.so";

def main () {
    IO.println(String.fromBuffer("He said, one day you will leave this world behind, so live a life you will remember.\n -- By Avicii.\n"));
    return 0;
}