native_class IO in "libio";
native_class String in "libstring";
native_class Array in "libarray";
native_class FS in "libfs";
native_class Map in "libmapping";
native_class System in "libsys";

def main () {
    var s = Map.create();
    s.insert("a", "b");
    s.insert(1, "woshigeshabi");
    IO.println(s["a"]);
    IO.println(s[1]);
    s = System.clone(s);
    IO.println(s["a"]);
    IO.println(s[1]);
    return 0;
}
