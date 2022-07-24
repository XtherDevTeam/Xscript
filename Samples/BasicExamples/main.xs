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

class InheritTest {
    def constructor () {
        def parent in this;
        this.parent = String.fromBuffer("俺恁爹");
        return this;
    }
};

class ConstructTest extends InheritTest {
    def constructor () {
        def default in this;
        this.super.constructor();
        this.default = String.fromBuffer("我滴任务完成啦！哈哈哈哈哈哈哈");
        return this;
    }
};

def main () {
    var test = new ConstructTest();
    IO.println(String.fromBool(test instanceOf ConstructTest));
    IO.println(test.default);
    return 0;
}