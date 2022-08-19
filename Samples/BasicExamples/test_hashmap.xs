native_class IO in "libio";
native_class String in "libstring";
native_class Array in "libarray";
native_class FS in "libfs";
native_class HashMap in "libhash";

def main () {
    var s = HashMap.create();
    s.insert("a", "b");
    s.insert(1, "woshigeshabi");
    IO.println(s["a"]);
    IO.println(s[1]);
    return 0;
}
