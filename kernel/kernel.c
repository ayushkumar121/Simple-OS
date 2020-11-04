
//libraries not requiring drivers
//#include <stdarg.h>
#include "libc/glyphs.h"
#include "libc/stdlib.c"
#include "libc/string.c"
#include "libc/multiboot.h"
#include "libc/math.c"

//drivers
#include "drivers/io.c"
#include "drivers/rtc.c"
#include "drivers/serial.c"
#include "drivers/vga.c"
#include "drivers/keyboard.c"

#include "libc/memory.c"
//#include "filesytem/fat.c"

//libs requring driver
#include "libc/fonts.c"
#include "libc/random.c"
#include "libc/terminal.c"

//drivers
#include "drivers/pci.c"
#include "drivers/idt.c"
//#include "drivers/ide.c"
#include "ramdisk.c"
#include "cmd/command.c"

void init_shell()
{
   // drawstring("ABX", 300, 0, GREEN, 1);
    fillrect(BLUE, (rect_t){0, 25, VGA_WIDTH, 3});
}

void kernel_main(multiboot_info_t *mboot)
{
    init_serial();
    init_vga(mboot);
    init_keyboard();
    init_idt();
    init_rtc();
    init_pci();
    //init_ramdisk(mboot->mmap_addr);
    //init_ide();
    init_shell();
    //init_terminal();
    init_cmd();

    print("\nWelcome to worktogether\n\n");
    print_num(get_memory());
    print(" Ram available.\n\n");
    print_num(files);
    print(" file(s) found\n\n");

    char *cmd = "sample-cmd-not-too-long";

    while (TRUE)
    {
        int temp = terminal_fcolor;
        setcolor(0x9C1DCF, terminal_bcolor);
        print("\n@ ");
        setcolor(temp, terminal_bcolor);

        gets(cmd);

        if (strlen(cmd) > 3)
        {
            print_err("COMMAND TOO LONG");
            cmd[3] = '\0';
        }
        else
        {
            run_cmd(cmd);
        }
    }
}
