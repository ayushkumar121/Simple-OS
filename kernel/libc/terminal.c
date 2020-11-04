int startx = 15;
int starty = 30;

uint32_t terminal_fcolor = 0x2BF042;
uint32_t terminal_bcolor = BLACK;

void setcursor(int x, int y)
{
    startx = x;
    starty = y;
}

void setcolor(uint32_t fcolor, uint32_t bcolor)
{
    terminal_fcolor = fcolor;
    terminal_bcolor = bcolor;
}

void print(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '\n')
        {
            starty += 8;
            startx = 15;
            continue;
        }

        draw_bitmap(font8x8_basic[str[i]], startx, starty, terminal_fcolor, terminal_bcolor);
        startx += 8;
    }
}

void print_custom(char *_bitmap)
{
    draw_bitmap(_bitmap, startx, starty, terminal_fcolor, terminal_bcolor);
    startx += 8;
}

void print_num(int num)
{
    char buffer[80];
    itoa(num, buffer);

    print(buffer);
}

void gets(char *str)
{
    int code = '\0';
    int i = 0;

    // clearing buffer
    for (int j = 0; j < strlen(str); j++)
        str[j] = '\0';

    while (code != 0x1C)
    {
        code = getScancode();
        char ch = getkey(code);

        if (ch != '\0')
        {
            str[i++] = ch;

            draw_bitmap(font8x8_basic[ch], startx, starty, terminal_fcolor, terminal_bcolor);
            startx += 8;
        }
        else if (code == 0x0E) // for backspace
        {
            if (i > 0)
            {
                startx -= 8;
                str[i--] = '\0';
                draw_bitmap(font8x8_basic[0], startx, starty, terminal_fcolor, terminal_bcolor);
            }
        }
    }

    str[i++] = '\0';
}

void print_err(char *str)
{
    int temp = terminal_fcolor;
    setcolor(RED, terminal_bcolor);
    print("\n\nERROR : ");
    print(str);
    print("\n");
    setcolor(temp, terminal_bcolor);
}

void init_terminal()
{
    setcolor(terminal_fcolor, RGB(249, 241, 165));
}