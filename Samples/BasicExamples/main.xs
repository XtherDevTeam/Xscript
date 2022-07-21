native_class IO in "libio.xnc.so";
native_class String in "libstring.xnc.so";

def main () {
    var Str = String.fromBuffer("1145141919810");
    IO.println(Str.substr(6, 4));
    IO.println(Str.substr(6));
    IO.println(String.fromInt(Str.find("1919")));
    return 0;
}