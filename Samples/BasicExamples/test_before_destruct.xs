native_class IO in "libio";
native_class Thread in "libthread";

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
    for (var i = 0;i < 500;i += 1) {
        before_destruct_test_1();
    }
    IO.println("wocao wotuichule");
    return 0;
}

def main () {
    before_destruct_test();
    return 0;
}