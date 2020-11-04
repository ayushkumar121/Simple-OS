int VGA_WIDTH = 1024;
int VGA_HEIGHT = 768;
int PITCH = 3200;
int PIXEL_WIDTH = 4;
uint8_t *VED_MEM = (uint8_t *)0xA0000;

enum colors
{
    ORANGE = 0xf78223,
    LIGHT_GREEN = 0x51ff00,
    WHITE = 0xffffff,
    BLACK = 0x000000,
    RED = 0xff0000,
    GREEN = 0x00ff00,
    BLUE = 0x0000ff,
    CYAN = 0x00ffff,
    GREY = 0xAADEF2,
    DARK_GREY = 0x444444,
    MAGENTA = 0xED0571,
    PURPLE = 0xCC44CC
};

unsigned long RGB(int r, int g, int b)
{
    return ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

struct rect
{
    int x, y, w, h;
};

typedef struct rect rect_t;

typedef struct point
{
    int x, y;
} point_t;

typedef struct line
{
    int len;
    float slope;
    point_t start;
} line_t;

void putpixel(int x, int y, uint32_t color)
{
    if (x < 0 || y < 0 || x > VGA_WIDTH || y > VGA_WIDTH)
    {
        return;
    }

    unsigned where = x * PIXEL_WIDTH + y * PITCH;
    VED_MEM[where] = color & 255;             // BLUE
    VED_MEM[where + 1] = (color >> 8) & 255;  // GREEN
    VED_MEM[where + 2] = (color >> 16) & 255; // RED
}

static void fillrect(uint32_t color, rect_t r)
{
    uint8_t *where = VED_MEM;
    int i, j;

    for (i = r.y; i < r.y + r.h; i++)
    {
        for (j = r.x; j < r.x + r.w; j++)
        {
            where[i * PITCH + j * PIXEL_WIDTH] = color & 255;
            where[i * PITCH + j * PIXEL_WIDTH + 1] = (color >> 8) & 255;
            where[i * PITCH + j * PIXEL_WIDTH + 2] = (color >> 16) & 255;
        }
    }
}

void init_vga(multiboot_info_t *mboot)
{
    VGA_WIDTH = mboot->framebuffer_width;
    VGA_HEIGHT = mboot->framebuffer_height;

    VED_MEM = (uint8_t *)mboot->framebuffer_addr;
    PITCH = mboot->framebuffer_pitch;
    PIXEL_WIDTH = mboot->framebuffer_bpp / 8;
}