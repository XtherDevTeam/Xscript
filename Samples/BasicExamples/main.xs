native_class IO in "libio";
native_class String in "libstring";
native_class Array in "libarray";
native_class FS in "libfs";
native_class Thread in "libthread";
native_class System in "libsys";

def main () {
    var S = String.fromBuffer("1+1==2");
    if(S.find("3")) {
        IO.println("我宣布个事！1+1==2里面有3！");
    }
    return 0;
}
