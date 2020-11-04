#include "../libc/dictionary.c"

dict_t scancodes = {.size = 0};

void init_codes()
{
    dict_add(0x1e, 'a', &scancodes);
    dict_add(0x1f, 's', &scancodes);
    dict_add(0x20, 'd', &scancodes);
    dict_add(0x21, 'f', &scancodes);
    dict_add(0x22, 'g', &scancodes);
    dict_add(0x23, 'h', &scancodes);
    dict_add(0x24, 'j', &scancodes);
    dict_add(0x25, 'k', &scancodes);
    dict_add(0x26, 'l', &scancodes);
    dict_add(0x10, 'q', &scancodes);
    dict_add(0x11, 'w', &scancodes);
    dict_add(0x12, 'e', &scancodes);
    dict_add(0x13, 'r', &scancodes);
    dict_add(0x14, 't', &scancodes);
    dict_add(0x15, 'y', &scancodes);
    dict_add(0x16, 'u', &scancodes);
    dict_add(0x17, 'i', &scancodes);
    dict_add(0x18, 'o', &scancodes);
    dict_add(0x19, 'p', &scancodes);
    dict_add(0x2c, 'z', &scancodes);
    dict_add(0x2d, 'x', &scancodes);
    dict_add(0x2e, 'c', &scancodes);
    dict_add(0x2f, 'v', &scancodes);
    dict_add(0x30, 'b', &scancodes);
    dict_add(0x31, 'n', &scancodes);
    dict_add(0x32, 'm', &scancodes);
    dict_add(0x39, ' ', &scancodes);
    dict_add(0x04, '3', &scancodes);
    dict_add(0x08, '7', &scancodes);
    dict_add(0x02, '1', &scancodes);
    dict_add(0x06, '5', &scancodes);
    dict_add(0x0A, '9', &scancodes);
    dict_add(0x03, '2', &scancodes);
    dict_add(0x0B, '0', &scancodes);
    dict_add(0x07, '6', &scancodes);
    dict_add(0x05, '4', &scancodes);
    dict_add(0x09, '8', &scancodes);

    // special characters
    dict_add(0x34, '.', &scancodes);
    dict_add(0x0D, '=', &scancodes);
    dict_add(0x0C, '-', &scancodes);
    dict_add(0x27, ';', &scancodes);
    dict_add(0x33, ',', &scancodes);
    dict_add(0x1B, ']', &scancodes);
    dict_add(0x1A, '[', &scancodes);
    dict_add(0x35, '/', &scancodes);
    
    // dict_add(0x1C, '\0', &scancodes); // enter
    // dict_add(0x01, '\0', &scancodes); // esc
}
