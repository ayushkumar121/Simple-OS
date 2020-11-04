char *freebase = (char *)0x00000500; 
char *freetop = (char *)0x00007BFF;

void poke(int addr,int offset,int value)
{
    char *_buffer = (char *)addr;

    *(_buffer + offset) = value;
}

int peek(int addr,int offset)
{
    char *_buffer = (char *)addr;

    return *(_buffer + offset);
}

uint16_t get_memory()
{
    unsigned short total;
    unsigned char lowmem,highmem;

    outb(0x70,0x30);
    lowmem = inb(0x71);
    outb(0x70,0x31);
    highmem = inb(0x71);

    total = lowmem | highmem << 8;

    return total;
}

uint32_t* malloc(uint32_t size)
{
    char *temp = freebase;
    freebase += size;

    return temp;
}
