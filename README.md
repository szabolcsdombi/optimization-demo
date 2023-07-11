# optimization-demo

This article is about optimizing a tiny bit of Python code by replacing it with its C++ counterpart.

Beware, geek stuff follows.

We are interested in implementing the [Opening Handshake](https://datatracker.ietf.org/doc/html/rfc6455#section-1.3) of [The Websocket Protocol](https://datatracker.ietf.org/doc/html/rfc6455).
It is a fairly simple to understand task, it involes sizeable number crunching and intermediate object allocations to see it pop out in the results.
To be clear, this is a demo project with no real world benefits except for the methodology used.

Let's get started.

First, we implement a function that returns the `Sec-WebSocket-Accept` calculated from the `Sec-WebSocket-Key`

```py
from base64 import b64encode
from hashlib import sha1


def py_accept(key: str) -> str:
    return b64encode(sha1((key + '258EAFA5-E914-47DA-95CA-C5AB0DC85B11').encode()).digest()).decode()
```

We can easily verify the sample value from the spec matches our return value.

```py
>>> py_accept('dGhlIHNhbXBsZSBub25jZQ==')
's3pPLMBiTxaQ9kYGzzhZRbK+xOo='
```

So far so good. Now let's dissamble it to see what is inside.

```py
>>> import dis
>>> dis.dis(py_accept)

  1           0 RESUME                   0

  2           2 LOAD_GLOBAL              1 (NULL + b64encode)
             14 LOAD_GLOBAL              3 (NULL + sha1)
             26 LOAD_FAST                0 (key)
             28 LOAD_CONST               1 ('258EAFA5-E914-47DA-95CA-C5AB0DC85B11')
             30 BINARY_OP                0 (+)
             34 LOAD_METHOD              2 (encode)
             56 PRECALL                  0
             60 CALL                     0
             70 PRECALL                  1
             74 CALL                     1
             84 LOAD_METHOD              3 (digest)
            106 PRECALL                  0
            110 CALL                     0
            120 PRECALL                  1
            124 CALL                     1
            134 LOAD_METHOD              4 (decode)
            156 PRECALL                  0
            160 CALL                     0
            170 RETURN_VALUE
```

Okay, this looks a bit messy. Here is a transformed version of it.

```py
             26 LOAD_FAST                0 (key)
             28 LOAD_CONST               1 ('258EAFA5-E914-47DA-95CA-C5AB0DC85B11')
             30 BINARY_OP                0 (+)
             60 CALL                     0 (encode)
             74 CALL                     1 (sha1)
            110 CALL                     0 (digest)
            124 CALL                     1 (b64encode)
            160 CALL                     0 (decode)
            170 RETURN_VALUE
```

Except for the temporary values generated within the steps, the code itself looks the fastest possible. All the methods invoked are implemented in C inside the CPython implementation.

Now, we are going to implement all this as a single step in C++. To do that, we can initialize a Python extension and add our new function.

```c++
#include <Python.h>

void sec_websocket_accept(const void * src, void * dst) {
    ...
}

PyObject * c_accept(PyObject * self, PyObject * arg) {
    char result[28];
    Py_ssize_t len = 0;
    const char * key = PyUnicode_AsUTF8AndSize(arg, &len);
    if (!key || len != 24) {
        PyErr_SetString(PyExc_ValueError, "invalid key");
        return NULL;
    }
    sec_websocket_accept(key, result);
    return PyUnicode_FromStringAndSize(result, 28);
}

PyMethodDef module_methods[] = {
    {"c_accept", (PyCFunction)c_accept, METH_O, NULL},
    {},
};

PyModuleDef module_def = {PyModuleDef_HEAD_INIT, "mymodule", NULL, -1, module_methods};

extern "C" PyObject * PyInit_mymodule() {
    return PyModule_Create(&module_def);
}
```

The implementation of `sec_websocket_accept()` is cumbersome enough to worth ommitting from this article.
Here is a [link](mymodule/mymodule.cpp) to the full code.

It might not be trivial to see, but neither the Python, nor the C++ variant contains micro-optimizations or any harware specific ones.
These are just naive implentations. We can achieve significant results without using any of that.

We can add our tests, and see the results.

```py
from base64 import b64encode
from hashlib import sha1

from mymodule import c_accept


def py_accept(key: str) -> str:
    return b64encode(sha1((key + '258EAFA5-E914-47DA-95CA-C5AB0DC85B11').encode()).digest()).decode()


def test_python_code(benchmark):
    assert benchmark(py_accept, 'dGhlIHNhbXBsZSBub25jZQ==') == 's3pPLMBiTxaQ9kYGzzhZRbK+xOo='


def test_optimized_code(benchmark):
    assert benchmark(c_accept, 'dGhlIHNhbXBsZSBub25jZQ==') == 's3pPLMBiTxaQ9kYGzzhZRbK+xOo='
```

## Results

```
--------------------------------------------------------------------------------------------------------
Name (time in ns)           Mean            StdDev              Median            OPS (Mops/s)
--------------------------------------------------------------------------------------------------------
test_optimized_code     208.0669 (1.0)      0.1062 (1.0)      208.0665 (1.0)            4.8061 (1.0)
test_python_code        893.2082 (4.29)     6.2278 (58.63)    889.6251 (4.28)           1.1196 (0.23)
--------------------------------------------------------------------------------------------------------
```

- It seems our Python code did really well. It can execute 1.1m calls per second.
- It is also clear our C++ variant is 4.29x faster, clocking at 4.8m calls per second.

Amazing! Replacing a tiny bit of code that seems not optimizable has a significant effect.

If you wish to run these tests yourself, you will find all the necessary steps in the github actions [here](https://github.com/szabolcsdombi/optimization-demo/actions/runs/5423258436/jobs/9860949567).

## No-Goals of this Article

- This article does not address maintainability or any other burden introduced with replacing simple Python code with cumbersome low level C code.
- We are not interested in micro-optimization, using SSE or hardware implemented hashing.
- Not interested in multi-threaded approaches, concurrency.
- Not interested in implementing it in Rust or any other language not supported out of the box for Python Extensions.

## Fun Fact

We can implement a magic function that may also work.

```py
def magic_accept(key: str) -> str:
    return 's3pPLMBiTxaQ9kYGzzhZRbK+xOo='
```

Silly, but indeed it passes the test.

```
--------------------------------------------------------------------------------------------------------
Name (time in ns)           Mean            StdDev              Median            OPS (Mops/s)
--------------------------------------------------------------------------------------------------------
test_magic_code          70.7236 (1.0)      0.0584 (1.0)       70.7438 (1.0)           14.1396 (1.0)
test_optimized_code     210.7457 (2.98)     0.2183 (3.74)     210.7261 (2.98)           4.7451 (0.34)
test_python_code        912.7083 (12.91)    5.5000 (94.24)    912.7722 (12.90)          1.0956 (0.08)
-------------------------------------------------------------------------------------------------------
```

The dissambled version seems to be simple too.

```py
>>> dis.dis(magic_accept)
  1           0 RESUME                   0

  2           2 LOAD_CONST               1 ('s3pPLMBiTxaQ9kYGzzhZRbK+xOo=')
              4 RETURN_VALUE
```

So, how this new method compares to our existing ones that do real work?

Supprising as it may sound but our C++ implementation is just 2.98x slower.
(From measurements and interpretations we are now entering a realm of guessings).
This could be because of the overhead introduced by calling functions, the interpreter parsing bytecode or our mearuring tools used.
At 14m calls per second on a single core this is inevitable.

## Summary

By implementing a simple task in C++ instead of Python, where the underlying function calls are already implemented in C++, we still can get a significant boost.
