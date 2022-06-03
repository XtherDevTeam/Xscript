# The functions in X Script 2

函数分为 函数主体（存放在包里的字节码） 以及 函数指针（一个`XIndexType`类型的`Static`或`Member`变量）

## 包内函数

包内函数在创建时会创建一个同名的`Static`变量，其内容为指向函数主体的函数指针.

例

```javascript
def Hello () {
    return 114 + 514 + 1919810;
}
```

Hello()的字节码输出为

```asm
hello:
	push_integer 114
	push_integer 514
	calculation_add
	push_integer 1919810
	calculation_add
	func_return
```

包初始化代码为

```asm
switch_package 0 ; MainPackage
stack_push_function <Hash StringValue="hello">
static_store 0 ; function pointer
```

## 类方法函数

类方法函数会在编译器的 `ExpressionCompiler::ParseMemberExpression` 里面自动筛选起始为 `ClassName` 的 `MemberExpression` 然后交给 `ExpressionCompiler::ParseClassMethodInvoke()` 进行编译

例

```javascript
class A {
	function constructor () {
		member test_member = 0;
		member test_number = 114514;
    }
};

function PackageEntry() {
    var ClassA = new A.constructor();
    return ClassA.test_number;
}
```

在这个例子里，`PackageEntry()` 的 `A.constructor` 就会自动转化为一个类方法函数指针



