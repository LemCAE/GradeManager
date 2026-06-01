#include "data.h"

//UTF-8字符的字节数（根据首字节判断）
int utf8CharLen(unsigned char c) {
    if (c < 0x80) return 1;
    else if ((c & 0xE0) == 0xC0) return 2;
    else if ((c & 0xF0) == 0xE0) return 3;
    else if ((c & 0xF8) == 0xF0) return 4;
    else return 1; 
}

// UTF-8在屏幕上的显示宽度（中文占2，英文占1）
int utf8DisplayWidth(const char *str) {
    int width = 0;
    while (*str) {
        unsigned char c = (unsigned char)*str;
        int len = utf8CharLen(c);
        if (len == 1) width += 1;      // ASCII
        else width += 2;               // 多字节字符
        str += len;
    }
    return width;
}