native_class IO in "libio";
native_class Thread in "libthread";
native_class String in "libstring";
native_class System in "libsys";
native_class Array in "libarray";

def test (a) {
    IO.println(String.fromInt(a.length()));
    for (var i = 0;i < a.length();i += 1) {
        IO.println(String.fromInt(a[i]));
    }
    return 0;
}

def main () {
    var a = Array.fromBuffer([1, 2, 3]);
    test(a);
    return 0;
}