# 类的跨包继承机制

这玩意就俩个字，阴间。

首先，我们需要在`CompilingTimeClass`结构内做一些修改.

```diff
- XArray<XIndexType> ParentClasses;
+ XArray<ClassDescriptor> ParentClasses;
```

在XScript命名空间里加入结构`ClassDescriptor`用于全局描述某一个包的位置 (VM & Compiler 皆可)

``` c++
class ClassDescriptor {
public:
    XIndexType PackageID;
    XIndexType ClassID;

    ClassDescriptor(XIndexType PkgID, XIndexType CID);

    bool operator==(const ClassDescriptor &rhs) const;
    bool operator!=(const ClassDescriptor &rhs) const;
};
```


