native_class IO in "libio";
native_class String in "libstring";
native_class Array in "libarray";

var N = 0;
var M = 0;
var W = Array.create();
var V = Array.create();
var dp = Array.create();

def max (a, b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

def main () {
    N = IO.readInt();
    M = IO.readInt();
    V.resize(1010);
    W.resize(1010);

    dp.resize(1010);

    for (var i = 1;i <= M;i += 1) {
        W[i] = IO.readInt();
        V[i] = IO.readInt();
    }
    
    for (var i = 1; i <= M;i += 1) {
        for (var j = N;j >= W[i];j -= 1) {
            dp[j] = max(dp[j], dp[j - W[i]] + V[i]);
        }
    }
    
    IO.println(String.fromInt(dp[N]));
    return 0;
}