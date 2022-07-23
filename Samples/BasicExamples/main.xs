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

class ConstructTest {
    def constructor () {
        def default in this;
        this.default = String.fromBuffer("我滴任务完成啦！哈哈哈哈哈哈哈");
        return this;
    }
};

def main () {
    var test = new ConstructTest();
    IO.println(test.default);
    return 0;
}