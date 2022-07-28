native_class IO in "libio.xnc.so";
native_class String in "libstring.xnc.so";
native_class Array in "libarray.xnc.so";

def main () {
    var sum = 0;
    for (var i = 0;i <= 1048576;i += 1) {
        sum += i;
    }
    return 0;
}