native_class IO in "libio.xnc.so";
native_class String in "libstring.xnc.so";
native_class Array in "libarray.xnc.so";
native_class FS in "libfs.xnc.so";

def main () {
    var file = FS.open("test.txt", "r+");
    var result = file.read();
    IO.println(String.fromBytes(result));
    file.close();
    return 0;
}