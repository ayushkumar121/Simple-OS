#define NMI_disable_bit 0x80
#define OPTIMISED_BINARY(bcd) ( ((bcd & 0xF0) >> 1) + ((bcd & 0xF0) >> 3) + (bcd & 0xf) )

void set_rtc_register(int reg)
{
    outb (0x70, (NMI_disable_bit << 7) | (reg)); 
}

void init_rtc()
{
    unsigned long f = save_irqdisable();
    
    outb(0x70,0x8A);
    outb(0x71,0x20);
    
    irqrestore(f);
}

date_t getDate()
{
    struct date current_date;
    
    set_rtc_register(0x07);
    current_date.day = OPTIMISED_BINARY(inb(0x71));
    
    set_rtc_register(0x08);
    current_date.month = OPTIMISED_BINARY(inb(0x71));
    
    set_rtc_register(0x09);
    int yy = OPTIMISED_BINARY(inb(0x71));
    
    set_rtc_register(0x32);
    int century = OPTIMISED_BINARY(inb(0x71));
    
    current_date.year = century * 100 + yy;

    return current_date;
}

struct time getTime()
{
    struct time current_time;

    set_rtc_register(0x00);
    current_time.seconds = OPTIMISED_BINARY(inb(0x71));
    
    set_rtc_register(0x02);
    current_time.minutes = OPTIMISED_BINARY(inb(0x71));
    
    set_rtc_register(0x04);
    current_time.hours =  OPTIMISED_BINARY(inb(0x71));

    return current_time;
}

int getTimems()
{
    struct time t = getTime();

    return ((t.hours * 60 * 60) + t.minutes * 60 + t.seconds) * 1000;
}

void sleep(int ms)
{
    int _time = getTimems();

    while(getTimems() < _time + ms);
}