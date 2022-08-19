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
    IO.println(String.formatter("${str}, ${str}!\nNumsTest: ${int bs=bin} ${bool} ${deci pre=6}", "Hello", "world", 114514, True, 3.14));
    return 0;
}