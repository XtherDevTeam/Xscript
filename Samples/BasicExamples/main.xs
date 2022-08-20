native_class IO in "libio";
native_class String in "libstring";
native_class Bytes in "libbytes";
native_class Array in "libarray";
native_class File in "libfs";
native_class FS in "libfs";
native_class Thread in "libthread";
native_class Error in "liberror";
native_class Math in "libmath";
native_class System in "libsys";

var Arr = Array.fromBuffer([]);

class TreeNode {
    def constructor () {
        def val in this;
        def left in this;
        def right in this;
        this.val = 0;
        this.left = 0;
        this.right = 0;
        return this;
    }
};

class Solution {
    def constructor () {
        return this;
    }
    def Fucker (T, nums, L, R) {
        var maxv = L;
        for (var i = L + 1; i < R;i += 1) {
            if (nums[i] > nums[maxv]) {
                maxv = i;
            }
        }
        T.val = nums[maxv];
        if (maxv != L) {
            T.left = new TreeNode();
            this.Fucker(T.left, nums, L, maxv);
        }
        if (maxv != R - 1) {
            T.right = new TreeNode();
            this.Fucker(T.right, nums, maxv + 1, R);
        }
        return 0;
    }
    def constructMaximumBinaryTree (nums) {
        var T = new TreeNode();
        this.Fucker(T, nums, 0, nums.length());
        return T;
    }
};

def getArray(T) {
    Arr.push_back(T.val);
    if (T.left == 0) {
        Arr.push_back(-1);
    } else {
        getArray(T.left);
    }
    if (T.right == 0) {
        Arr.push_back(-1);
    } else {
        getArray(T.right);
    }
    return 0;
}

def main () {
    // var arr = Array.fromBuffer([3,2,1,6,0,5]);
    // var S = new Solution();
    // var T = S.constructMaximumBinaryTree(arr);
    // getArray(T);
    // for (var i = 0;i < Arr.length();i += 1) {
    //    IO.println(String.fromInt(Arr[i]));
    // }
    if (1 + 1 == 2) {
        IO.println("yes");
    } else {
        IO.println("no");
    }
    return 0;
}