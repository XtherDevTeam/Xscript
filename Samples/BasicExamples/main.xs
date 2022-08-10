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
    for (var i = 0;i < 10000000;i += 1) {
        var Arr = Array.create();
        Arr.resize(512);
        Arr.resize(512);
    }
    return 0;
}