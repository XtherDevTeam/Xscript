native_class IO in "libio";
native_class String in "libstring";
native_class Array in "libarray";
native_class File in "libfs";
native_class FS in "libfs";
native_class Thread in "libthread";
native_class Error in "liberror";
native_class Math in "libmath";
native_class System in "libsys";

def main () {
    for (var i = 0;i + 1;i += 1) {
        var Arr = Array.create();
        Arr.resize(1024);
        Arr.resize(1024);
    }
    return 0;
}