native_class IO in "libio";

class testDestructClass {
    def constructor () {
        return this;
    }

    def before_destruct () {
        IO.println("触发成功 对象将要被销毁.");
        return this;
    }
};

def before_destruct_test_1 () {
    var testObject = new testDestructClass.constructor();
    return testObject;
}

def before_destruct_test () {
    while (True) {
        before_destruct_test_1();
    }
    return 0;
}

def main () {
    before_destruct_test();
    return 0;
}