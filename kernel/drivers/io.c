static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile("inb %1, %0"
                 : "=a"(ret)
                 : "Nd"(port));
    return ret;
}

static inline uint16_t inw(uint16_t port)
{
    uint16_t ret;
    asm volatile("inw %1, %0"
                 : "=a"(ret)
                 : "Nd"(port));
    return ret;
}

static inline uint32_t inl(uint16_t port)
{
    uint32_t ret;
    asm volatile("inl %1, %0"
                 : "=a"(ret)
                 : "Nd"(port));
    return ret;
}

static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile("outb %0, %1"
                 :
                 : "a"(val), "Nd"(port));
}

static inline void outw(uint16_t port, uint16_t val)
{
    asm volatile("outw %0, %1"
                 :
                 : "a"(val), "Nd"(port));
}

static inline void outl(uint16_t port, uint32_t val)
{
    asm volatile("outl %0, %1"
                 :
                 : "a"(val), "Nd"(port));
}

static inline void io_wait(void)
{
    asm volatile("outb %%al, $0x80"
                 :
                 : "a"(0));
}
/*
static inline bool are_interrupts_enabled()
{
    unsigned long flags;
    asm volatile ( "pushf\n\t"
                   "pop %0"
                   : "=g"(flags) );
    return flags & (1 << 9);
}*/

static inline unsigned long save_irqdisable(void)
{
    unsigned long flags;
    asm volatile("pushf\n\tcli\n\tpop %0"
                 : "=r"(flags)
                 :
                 : "memory");
}

static inline void irqrestore(unsigned long flags)
{
    asm("push %0\n\tpopf"
        :
        : "rm"(flags)
        : "memory", "cc");
}