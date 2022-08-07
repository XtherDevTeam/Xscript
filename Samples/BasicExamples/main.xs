native_class IO in "libio";
native_class String in "libstring";
native_class Array in "libarray";
native_class File in "libfs";
native_class FS in "libfs";
native_class Thread in "libthread";

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
    IO.println(S.numWays(8));
    return 0;
}
