native_class IO in "libio.xnc.so";
native_class String in "libstring.xnc.so";

class InternalException {
    def ZeroDivision () {
        def __exception_name__ in this;
        def __exception_message__ in this;
        this.__exception_name__ = "ZeroDivisionException";
        this.__exception_message__ = "Division by zero";
        return this;
    }
};

def main () {
    try {
        IO.println(String.fromBuffer("Trying to throw a exception..."));
        throw new InternalException.ZeroDivision();
    } catch as E {
        IO.println(String.fromBuffer(E.__exception_name__));
    };
    IO.println(String.fromBuffer("你好，世界！"));
    return 0;
}