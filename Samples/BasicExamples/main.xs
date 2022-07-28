native_class IO in "libio.xnc.so";
native_class String in "libstring.xnc.so";
native_class Array in "libarray.xnc.so";

var Arr = Array.create();
var Arr2 = Array.create();

def main () {
    Arr.resize(100);
    Arr2.resize(100);
    Arr[0] = IO.readInt();
    Arr[1] = IO.readInt();
    for (var i = 2;i < 100;i += 1) {
        Arr[i] = Arr[i-1] + Arr[i-2];
    }
    for (var i = 0;i < 100;i += 1) {
        IO.println(String.fromInt(Arr[i]));
    }
    return 0;
}