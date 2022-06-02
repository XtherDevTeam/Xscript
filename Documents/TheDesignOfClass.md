# The design of class in XScript 2

There are 2 kinds of class structure in XScript 2 source codes.

One is for compiling time, the another is for bytecode interpreter.

Now let's take a look to the another one.

It saves `class id`, `methods`, `members` and `vtable`.

### The class id

It's a number of this class structure, just like an identifier.

### The methods

It saves all methods of this class structure (included bytecode array of methods)

### The members

It saves all member information of this class structure. (but no data, only typename and descriptions)

