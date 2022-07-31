native_class IO in "libio.xnc";
native_class String in "libstring.xnc";
native_class Array in "libarray.xnc";
native_class FS in "libfs.xnc";

def main () {
    var file = FS.open("test.txt", "r+");
    var result = file.read();
    IO.println(String.fromBytes(result));
    file.close();
    return 0;
}