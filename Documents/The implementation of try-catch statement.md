# The implementation of try-catch statement in XScript 2

### Example codes

```c++
try {
    throw new DivisionByZeroException.constructor();
} catch as e {
    if (e instanceOf DivisionByZeroException) {
        return 0;
    } else {
        return 4;
    }
};
```

### Compiling-time

