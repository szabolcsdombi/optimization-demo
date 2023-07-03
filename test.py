from base64 import b64encode
from hashlib import sha1

from mymodule import c_accept


def py_accept(key: str) -> str:
    return b64encode(sha1((key + '258EAFA5-E914-47DA-95CA-C5AB0DC85B11').encode()).digest()).decode()


# def magic_accept(key: str) -> str:
#     return 's3pPLMBiTxaQ9kYGzzhZRbK+xOo='


def test_python_code(benchmark):
    assert benchmark(py_accept, 'dGhlIHNhbXBsZSBub25jZQ==') == 's3pPLMBiTxaQ9kYGzzhZRbK+xOo='


def test_optimized_code(benchmark):
    assert benchmark(c_accept, 'dGhlIHNhbXBsZSBub25jZQ==') == 's3pPLMBiTxaQ9kYGzzhZRbK+xOo='


# def test_magic_code(benchmark):
#     assert benchmark(magic_accept, 'dGhlIHNhbXBsZSBub25jZQ==') == 's3pPLMBiTxaQ9kYGzzhZRbK+xOo='

