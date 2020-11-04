#include "keyboard_scancodes.c"


void init_keyboard()
{
    outb(0x21, 0xFD);
    init_codes();
}

char getScancode()
{
    while (!(inb(0x64) & 1))
        ;
    return inb(0x60);
}

char getkey(int scancode)
{
    return dict_find(scancode, scancodes);
}

char getch()
{
    int code = getScancode();
    return getkey(code);
}
