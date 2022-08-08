native_class IO in "libio";
native_class String in "libstring";
native_class Array in "libarray";
native_class FS in "libfs";
native_class Thread in "libthread";
native_class System in "libsys";

class GCTestItem {
    def constructor () {
        def test_arr in this;
        this.test_arr = Array.create();
        this.test_arr.resize(128);
        return this;
    }
};

def io_test () {
    IO.println(String.fromBuffer("IO test starting..."));
    var Start = System.boot_time_ms();

    for (var i = 0;i < 50000;i += 1) {
        IO.println(String.fromBuffer("XScript2 is under the MIT license. Developed by Jerry Chou! ZoengJyutJing, ngo zungji nei!"));
    }
    var Duration = System.boot_time_ms() - Start;
    IO.println(String.fromBuffer("IO test ended."));
    return Duration;
}

def fs_test () {
    IO.println(String.fromBuffer("FS test starting..."));
    var Start = System.boot_time_ms();

    var file = File.open("test.txt", "w+");
    for (var i = 0;i < 50000;i += 1) {
        file.write("ZoengJyutJing, ngo zungji nei!\n");
    }
    file.close();
    file = File.open("test.txt", "r+");
    var dest = file.read();
    IO.println(String.fromBytes(dest));
    file.close();

    var Duration = System.boot_time_ms() - Start;
    IO.println(String.fromBuffer("FS test ended."));
    return Duration;
}

def array_test () {
    IO.println(String.fromBuffer("Array test starting..."));
    var Start = System.boot_time_ms();

    var arr = Array.create();
    for (var i = 0; i < 50000; i += 1) {
        arr.push_back(i);
    }
    for (var i = 0; i < 50000; i += 1) {
        arr.pop_back();
    }
    for (var i = 0; i < 50000; i += 1) {
        arr.push_back(i);
        arr.pop_back();
    }

    var Duration = System.boot_time_ms() - Start;
    IO.println(String.fromBuffer("Array test ended."));

    return Duration;
}

def gc_test () {
    IO.println(String.fromBuffer("GC test starting..."));
    var Start = System.boot_time_ms();

    for (var i = 0;i < 50000; i += 1) {
        var Str = String.fromBuffer("ZoengJyutJing, ngo zungji nei!");
        var Item = new GCTestItem();
    }

    var Duration = System.boot_time_ms() - Start;
    IO.println(String.fromBuffer("GC test ended."));
    IO.println(String.fromInt(Start) + " " + String.fromInt(System.boot_time_ms()));
    return Duration;
}

def main () {
    var th_io = Thread.start(io_test);
    var th_fs = Thread.start(fs_test);
    var th_arr = Thread.start(array_test);
    var th_gc = Thread.start(gc_test);
    var res_io = Thread.getResult(th_io);
    var res_fs = Thread.getResult(th_fs);
    var res_arr = Thread.getResult(th_arr);
    var res_gc = Thread.getResult(th_gc);
    var Result =
        String.fromBuffer("XScript 2 Performance report: \n") +  String.fromBuffer("\n") +
        String.fromBuffer("Test Items(4): IO, FS, Array, GC\n") + String.fromBuffer("\n") +
        String.fromBuffer("IO test duration: ") + String.fromInt(res_io) + String.fromBuffer("\n") +
        String.fromBuffer("FS test duration: ") + String.fromInt(res_fs) + String.fromBuffer("\n") +
        String.fromBuffer("Array test duration: ") + String.fromInt(res_arr) + String.fromBuffer("\n") +
        String.fromBuffer("GC test duration: ") + String.fromInt(res_gc) + String.fromBuffer("\n");

    IO.println(Result);
    return 0;
}
