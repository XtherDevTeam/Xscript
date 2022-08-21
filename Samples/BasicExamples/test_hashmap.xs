native_class IO in "libio";
native_class String in "libstring";
native_class Array in "libarray";
native_class FS in "libfs";
native_class Map in "libmapping";
native_class System in "libsys";

def main () {
    var s = Map.create();
    s.insert("a", "b");
    s.insert("b", "b");
    IO.println(s["a"]);
    var a = Array.fromBuffer(s.keys());
    for (var i = 0;i < a.length();i += 1) {
        IO.println(a[i]);
        IO.println(s[a[i]]);
    }
    return 0;
}
