#include <Python.h>

void sec_websocket_accept(const void * src, void * dst) {
    unsigned char * const salt = (unsigned char *)src;
    char * const result = (char *)dst;

    const char * const table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    unsigned block0[16] = {
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x32353845, 0x41464135,
        0x2d453931, 0x342d3437, 0x44412d39, 0x3543412d, 0x43354142, 0x30444338, 0x35423131, 0x80000000,
    };
    unsigned block1[16] = {
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
        0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000001e0,
    };

    unsigned a = 0x67452301;
    unsigned b = 0xEFCDAB89;
    unsigned c = 0x98BADCFE;
    unsigned d = 0x10325476;
    unsigned e = 0xC3D2E1F0;
    unsigned ta, tb, tc, td, te;

    block0[0] = salt[0] << 24 | salt[1] << 16 | salt[2] << 8 | salt[3];
    block0[1] = salt[4] << 24 | salt[5] << 16 | salt[6] << 8 | salt[7];
    block0[2] = salt[8] << 24 | salt[9] << 16 | salt[10] << 8 | salt[11];
    block0[3] = salt[12] << 24 | salt[13] << 16 | salt[14] << 8 | salt[15];
    block0[4] = salt[16] << 24 | salt[17] << 16 | salt[18] << 8 | salt[19];
    block0[5] = salt[20] << 24 | salt[21] << 16 | salt[22] << 8 | salt[23];

    #define rol(value, bits) (((value)<<(bits))|((value)>>(32-(bits))))
    #define blk(i) (block[i&15]=rol(block[(i+13)&15]^block[(i+8)&15]^block[(i+2)&15]^block[i&15],1))
    #define R0(v,w,x,y,z,i) z+=((w&(x^y))^y)+block[i]+0x5A827999+rol(v,5);w=rol(w,30);
    #define R1(v,w,x,y,z,i) z+=((w&(x^y))^y)+blk(i)+0x5A827999+rol(v,5);w=rol(w,30);
    #define R2(v,w,x,y,z,i) z+=(w^x^y)+blk(i)+0x6ED9EBA1+rol(v,5);w=rol(w,30);
    #define R3(v,w,x,y,z,i) z+=(((w|x)&y)|(w&x))+blk(i)+0x8F1BBCDC+rol(v,5);w=rol(w,30);
    #define R4(v,w,x,y,z,i) z+=(w^x^y)+blk(i)+0xCA62C1D6+rol(v,5);w=rol(w,30);

    #define block block0
    R0(a, b, c, d, e, 0);
    R0(e, a, b, c, d, 1);
    R0(d, e, a, b, c, 2);
    R0(c, d, e, a, b, 3);
    R0(b, c, d, e, a, 4);
    R0(a, b, c, d, e, 5);
    R0(e, a, b, c, d, 6);
    R0(d, e, a, b, c, 7);
    R0(c, d, e, a, b, 8);
    R0(b, c, d, e, a, 9);
    R0(a, b, c, d, e, 10);
    R0(e, a, b, c, d, 11);
    R0(d, e, a, b, c, 12);
    R0(c, d, e, a, b, 13);
    R0(b, c, d, e, a, 14);
    R0(a, b, c, d, e, 15);
    R1(e, a, b, c, d, 16);
    R1(d, e, a, b, c, 17);
    R1(c, d, e, a, b, 18);
    R1(b, c, d, e, a, 19);
    R2(a, b, c, d, e, 20);
    R2(e, a, b, c, d, 21);
    R2(d, e, a, b, c, 22);
    R2(c, d, e, a, b, 23);
    R2(b, c, d, e, a, 24);
    R2(a, b, c, d, e, 25);
    R2(e, a, b, c, d, 26);
    R2(d, e, a, b, c, 27);
    R2(c, d, e, a, b, 28);
    R2(b, c, d, e, a, 29);
    R2(a, b, c, d, e, 30);
    R2(e, a, b, c, d, 31);
    R2(d, e, a, b, c, 32);
    R2(c, d, e, a, b, 33);
    R2(b, c, d, e, a, 34);
    R2(a, b, c, d, e, 35);
    R2(e, a, b, c, d, 36);
    R2(d, e, a, b, c, 37);
    R2(c, d, e, a, b, 38);
    R2(b, c, d, e, a, 39);
    R3(a, b, c, d, e, 40);
    R3(e, a, b, c, d, 41);
    R3(d, e, a, b, c, 42);
    R3(c, d, e, a, b, 43);
    R3(b, c, d, e, a, 44);
    R3(a, b, c, d, e, 45);
    R3(e, a, b, c, d, 46);
    R3(d, e, a, b, c, 47);
    R3(c, d, e, a, b, 48);
    R3(b, c, d, e, a, 49);
    R3(a, b, c, d, e, 50);
    R3(e, a, b, c, d, 51);
    R3(d, e, a, b, c, 52);
    R3(c, d, e, a, b, 53);
    R3(b, c, d, e, a, 54);
    R3(a, b, c, d, e, 55);
    R3(e, a, b, c, d, 56);
    R3(d, e, a, b, c, 57);
    R3(c, d, e, a, b, 58);
    R3(b, c, d, e, a, 59);
    R4(a, b, c, d, e, 60);
    R4(e, a, b, c, d, 61);
    R4(d, e, a, b, c, 62);
    R4(c, d, e, a, b, 63);
    R4(b, c, d, e, a, 64);
    R4(a, b, c, d, e, 65);
    R4(e, a, b, c, d, 66);
    R4(d, e, a, b, c, 67);
    R4(c, d, e, a, b, 68);
    R4(b, c, d, e, a, 69);
    R4(a, b, c, d, e, 70);
    R4(e, a, b, c, d, 71);
    R4(d, e, a, b, c, 72);
    R4(c, d, e, a, b, 73);
    R4(b, c, d, e, a, 74);
    R4(a, b, c, d, e, 75);
    R4(e, a, b, c, d, 76);
    R4(d, e, a, b, c, 77);
    R4(c, d, e, a, b, 78);
    R4(b, c, d, e, a, 79);
    #undef block

    a += 0x67452301;
    b += 0xEFCDAB89;
    c += 0x98BADCFE;
    d += 0x10325476;
    e += 0xC3D2E1F0;

    ta = a;
    tb = b;
    tc = c;
    td = d;
    te = e;

    #define block block1
    R0(a, b, c, d, e, 0);
    R0(e, a, b, c, d, 1);
    R0(d, e, a, b, c, 2);
    R0(c, d, e, a, b, 3);
    R0(b, c, d, e, a, 4);
    R0(a, b, c, d, e, 5);
    R0(e, a, b, c, d, 6);
    R0(d, e, a, b, c, 7);
    R0(c, d, e, a, b, 8);
    R0(b, c, d, e, a, 9);
    R0(a, b, c, d, e, 10);
    R0(e, a, b, c, d, 11);
    R0(d, e, a, b, c, 12);
    R0(c, d, e, a, b, 13);
    R0(b, c, d, e, a, 14);
    R0(a, b, c, d, e, 15);
    R1(e, a, b, c, d, 16);
    R1(d, e, a, b, c, 17);
    R1(c, d, e, a, b, 18);
    R1(b, c, d, e, a, 19);
    R2(a, b, c, d, e, 20);
    R2(e, a, b, c, d, 21);
    R2(d, e, a, b, c, 22);
    R2(c, d, e, a, b, 23);
    R2(b, c, d, e, a, 24);
    R2(a, b, c, d, e, 25);
    R2(e, a, b, c, d, 26);
    R2(d, e, a, b, c, 27);
    R2(c, d, e, a, b, 28);
    R2(b, c, d, e, a, 29);
    R2(a, b, c, d, e, 30);
    R2(e, a, b, c, d, 31);
    R2(d, e, a, b, c, 32);
    R2(c, d, e, a, b, 33);
    R2(b, c, d, e, a, 34);
    R2(a, b, c, d, e, 35);
    R2(e, a, b, c, d, 36);
    R2(d, e, a, b, c, 37);
    R2(c, d, e, a, b, 38);
    R2(b, c, d, e, a, 39);
    R3(a, b, c, d, e, 40);
    R3(e, a, b, c, d, 41);
    R3(d, e, a, b, c, 42);
    R3(c, d, e, a, b, 43);
    R3(b, c, d, e, a, 44);
    R3(a, b, c, d, e, 45);
    R3(e, a, b, c, d, 46);
    R3(d, e, a, b, c, 47);
    R3(c, d, e, a, b, 48);
    R3(b, c, d, e, a, 49);
    R3(a, b, c, d, e, 50);
    R3(e, a, b, c, d, 51);
    R3(d, e, a, b, c, 52);
    R3(c, d, e, a, b, 53);
    R3(b, c, d, e, a, 54);
    R3(a, b, c, d, e, 55);
    R3(e, a, b, c, d, 56);
    R3(d, e, a, b, c, 57);
    R3(c, d, e, a, b, 58);
    R3(b, c, d, e, a, 59);
    R4(a, b, c, d, e, 60);
    R4(e, a, b, c, d, 61);
    R4(d, e, a, b, c, 62);
    R4(c, d, e, a, b, 63);
    R4(b, c, d, e, a, 64);
    R4(a, b, c, d, e, 65);
    R4(e, a, b, c, d, 66);
    R4(d, e, a, b, c, 67);
    R4(c, d, e, a, b, 68);
    R4(b, c, d, e, a, 69);
    R4(a, b, c, d, e, 70);
    R4(e, a, b, c, d, 71);
    R4(d, e, a, b, c, 72);
    R4(c, d, e, a, b, 73);
    R4(b, c, d, e, a, 74);
    R4(a, b, c, d, e, 75);
    R4(e, a, b, c, d, 76);
    R4(d, e, a, b, c, 77);
    R4(c, d, e, a, b, 78);
    R4(b, c, d, e, a, 79);
    #undef block

    #undef rol
    #undef blk
    #undef R0
    #undef R1
    #undef R2
    #undef R3
    #undef R4

    a += ta;
    b += tb;
    c += tc;
    d += td;
    e += te;

    result[0] = table[a >> 26 & 63];
    result[1] = table[a >> 20 & 63];
    result[2] = table[a >> 14 & 63];
    result[3] = table[a >> 8 & 63];
    result[4] = table[a >> 2 & 63];
    result[5] = table[(a << 4 & 48) | (b >> 28 & 15)];
    result[6] = table[b >> 22 & 63];
    result[7] = table[b >> 16 & 63];
    result[8] = table[b >> 10 & 63];
    result[9] = table[b >> 4 & 63];
    result[10] = table[(b << 2 & 60) | (c >> 30 & 3)];
    result[11] = table[c >> 24 & 63];
    result[12] = table[c >> 18 & 63];
    result[13] = table[c >> 12 & 63];
    result[14] = table[c >> 6 & 63];
    result[15] = table[c & 63];
    result[16] = table[d >> 26 & 63];
    result[17] = table[d >> 20 & 63];
    result[18] = table[d >> 14 & 63];
    result[19] = table[d >> 8 & 63];
    result[20] = table[d >> 2 & 63];
    result[21] = table[(d << 4 & 48) | (e >> 28 & 15)];
    result[22] = table[e >> 22 & 63];
    result[23] = table[e >> 16 & 63];
    result[24] = table[e >> 10 & 63];
    result[25] = table[e >> 4 & 63];
    result[26] = table[e << 2 & 60];
    result[27] = '=';
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
