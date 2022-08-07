native_class IO in "XScript2Stdlib/NativeLibraries/libio";
native_class String in "XScript2Stdlib/NativeLibraries/libstring";
native_class Array in "XScript2Stdlib/NativeLibraries/libarray";
native_class File in "XScript2Stdlib/NativeLibraries/libfs";
native_class FS in "XScript2Stdlib/NativeLibraries/libfs";
native_class Thread in "XScript2Stdlib/NativeLibraries/libthread";
native_class Error in "XScript2Stdlib/NativeLibraries/liberror";

class Solution {
    def constructor () {
        return this;
    }

    def numWays(n) {
        var array = Array.create();
        array.resize(101);
        array[0] = 1;
        array[1] = 1;
        for (var i = 2;i <= n;i++) {
            array[i] = array[i-1] + array[i-2];
            array[i] = array[i] % 1000000007;
        }
        return array[n];
    }
};

def main () {
    var S = new Solution();
    var n = IO.readInt();
    IO.println(S.numWays(n));
    return 0;
}
