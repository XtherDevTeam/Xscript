# The design of class in XScript 2

 ### Definition

```c++
class EnvClassObject {
public:
    XIndexType Parent;
    XMap<XIndexType, XHeapIndexType> Members;
    
    bool IsInstanceOf(XIndexType Idx);
    XHeapIndexType GetMember(XIndexType Name);
};
```

### Creation

First, use instruction `new_class <class name : hashed>` to create a class.
After, executor will create a new `EnvClassObject` with template.
Then, use `duplicate` to copy the object, push some necessary params into stack.
Finally, push the constructor into stack,
use `func_invoke <1(object pointer 'this') + params count>` to invoke the constructor.

### Destruction

Before class objects going to be destructed by GC, 
if there is a `before_destruct` method in the class object, GC will try to **execute it first at a new thread**.