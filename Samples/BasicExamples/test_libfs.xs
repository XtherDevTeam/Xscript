native_class IO in "libio";
native_class String in "libstring";
native_class Array in "libarray";
native_class FS in "libfs";

def main () {
    var file = FS.open("test.txt", "r+");
    var result = file.read();
    IO.println(String.fromBytes(result));
    file.close();
    return 0;
}