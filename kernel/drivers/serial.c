#define PORT 0x3f8   /* COM1 */
 
void init_serial() {
   outb(PORT + 1, 0x00);    // Disable all interrupts
   outb(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
   outb(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
   outb(PORT + 1, 0x00);    //                  (hi byte)
   outb(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
   outb(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
   outb(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

int serial_received() {
   return inb(PORT + 5) & 1;
}
 
char serial_read() {
   while (serial_received() == 0);
 
   return inb(PORT);
}

int is_transmit_empty() {
   return inb(PORT + 5) & 0x20;
}
 
void serial_print(char a) {
   while (is_transmit_empty() == 0);
 
   outb(PORT,a);
}

void serial_println(char *str)
{
    for(int i = 0; i < strlen(str); i++)
    {
        serial_print(str[i]);
    }  

    serial_print('\n'); 
}

void serial_int(int num)
{
    char buffer[80];
    itoa(num,buffer);
    serial_println(buffer);
}