# The implementation of thread api

## Example code

```js
native_class IO in "libio.xnc.so";
native_class String in "libstring.xnc.so";
native_class Thread in "libthread.xnc.so";

def test_func (x, y) {
  for (var i = 0;i < 10;i += 1) {
    IO.println(String.fromBuffer("Here is thread ") + String.fromInt(Thread.id()) + String.fromBuffer(" o/"));
  }
  return x + y;
}

def main () {
  var result = Thread.start(test_func, 114, 514);
  return result.getResult();
}
```

## Progress

使用 `Thread.start(func, ...)` 来创建线程

`Thread.start()` 方法返回新启动线程的 `Identifier` , 然后程序调用 `Thread.getResult(thread_id)` 方法获取线程执行结果.

## Principle

`Thread.start()` 的实现

1. 创建线程, 并将`std::thread`保存到相应的 `EnvironmentThread` 结构体.
2. 返回一个 `XIndexType` 类型的ThreadID

`Thread.getResult()` 的实现

1. 查看线程是否处于运行状态, 如果不是, 返回 `InternalError`
2. 阻塞当前线程，等待指定线程完成运行.
3. 返回线程函数的返回值.

## Attention

一个线程被开启之后, 其线程并未被释放回收到线程池, 如果不及时调用 `getResult` 将 线程的 `IsBusy` 旗帜 置为 `false`,
有极大可能会导致线程池的枯竭, 无法开启新的线程, 从而在下一次 `Thread.start` 过程中返回 `InternalError`.