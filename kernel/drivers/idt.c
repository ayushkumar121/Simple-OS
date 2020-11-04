int nextTimer = 0;
int timerRate = 1000;

struct IDT_entry
{
    unsigned short int offset_lowerbits;
    unsigned short int selector;
    unsigned char zero;
    unsigned char type_attr;
    unsigned short int offset_higherbits;
};

struct IDT_entry IDT[286];

char *exception_messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"};

void setup_handler(int i, uint32_t irq)
{
    uint32_t irq_address = (uint32_t)irq;
    IDT[i].offset_lowerbits = irq_address & 0xffff;
    IDT[i].selector = 0x08; /* KERNEL_CODE_SEGMENT_OFFSET */
    IDT[i].zero = 0;
    IDT[i].type_attr = 0x8e; /* INTERRUPT_GATE */
    IDT[i].offset_higherbits = (irq_address & 0xffff0000) >> 16;
}

void isr_handler(registers_t reg)
{
    print("\n");
    print_err("Received interrupt");
    print_err(exception_messages[reg.eflags]);
    print_custom(CURSOR_BITMAP);
    print("\n");
    print_num(reg.int_no);
    print("\n");
    print_num(reg.err_code);
    print("\n");
    print_num(reg.int_no);
    asm("cli");
    asm("hlt");
}

void irq0_handler()
{
    if (getTimems() >= nextTimer)
    {
        int tempx = startx;
        int tempy = starty;
        char buffer[80];

        setcursor(15, 10);

        print_custom(CLOCK_BITMAP);
        print(" ");
        itoa(getTime().hours, buffer);
        print(buffer);
        print(" : ");
        itoa(getTime().minutes, buffer);
        print(buffer);
        print(" : ");
        itoa(getTime().seconds, buffer);
        print(buffer);

        setcursor(tempx, tempy);

        nextTimer = getTimems() + timerRate;
    }
    outb(0x20, 0x20); //EOI
    asm("sti");
}

void irq1_handler()
{
    outb(0x20, 0x20); //EOI
    asm("sti");
}

void irq12_handler()
{
    outb(0xA0, 0x20);
    outb(0x20, 0x20); //EOI
}

void init_idt(void)
{
    nextTimer = getTimems();
    asm("sti");
    
    // Remapping PIC

    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 40);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
    


    for (int i = 0; i < 32; i++)
    {
        setup_handler(i, (uint32_t)isr_handler);
    }


    setup_handler(0x20, (uint32_t)irq0_handler);
    setup_handler(0x21, (uint32_t)irq1_handler);
    setup_handler(0x2C, (uint32_t)irq12_handler);

    // setting up the idt
    unsigned long idt_ptr[2];
    unsigned long idt_address;

    idt_address = (unsigned long)IDT;
    idt_ptr[0] = (sizeof(struct IDT_entry) * 286) + ((idt_address & 0xffff) << 16);
    idt_ptr[1] = idt_address >> 16;

    __asm__ __volatile__("lidtl (%0)"
                         :
                         : "r"(&idt_ptr));
}