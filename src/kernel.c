#include "kernel.h"
#include <stddef.h>
#include <stdint.h>

uint16_t *vidmem = 0;

uint16_t term_row = 0;
uint16_t term_col = 0;

uint16_t terminal_mk_char(char c, char clr) {
    return (clr << 8) | c;
}

void terminal_putc(int x, int y, char c, char clr) {
    vidmem[y * VGA_WIDTH + x] = terminal_mk_char(c, clr);
}

void terminal_writechar(char c, char clr) {
    if (c == '\n') {
        term_row += 1;
        term_col = 0;
    } else {
        terminal_putc(term_col, term_row, c, clr);
        term_col += 1;
        if (term_col >= VGA_WIDTH) {
            term_col = 0;
            term_row += 1;
        }
    }
}

void term_init() {
    vidmem = (uint16_t*)(0xB8000);
    for (int y = 0; y < VGA_HEIGHT; y++) {
        for (int x = 0; x < VGA_WIDTH; x++) {
            terminal_putc(x, y, ' ', 0);
        }
    }
}

size_t strlen(const char *sz) {
    size_t len = 0;
    while (sz[len]) {
        len++;
    }
    return len;
}

void print(const char *sz) {
    size_t len = strlen(sz);
    for (int i = 0; i < len; i++) {
        terminal_writechar(sz[i], 15);
    }
}

void kernel_main() {
    term_init();
    print("Hi world!\nnew line");
}
