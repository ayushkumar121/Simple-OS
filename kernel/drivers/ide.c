int IDE_CONTROLLER = 1; // 1 for Primary and 2 for Secondary
int IDE_DRIVE = -1;     // 0 for Master drive 1 for Slave and -1 for does not exits
int DRIVE_SIZE = 0;     // in sectors

struct IDE_DEVICES
{
    int channel; // 1 for Primary and 2 for Secondary
    int drive; // 0 for Master drive 1 for Slave and -1 for does not exits
    int size;
} DRIVES[4];

void init_ide()
{
    outb(0x1F3, 0); // sending a random byte to primary controller
    uint8_t temp;

    if (inb(0x1F3) != 0)
        IDE_CONTROLLER = 2;

    if (IDE_CONTROLLER == 1)
    {
        outb(0x1F6, 0xA0);
        sleep(5); // you have to wait 400ns or 4 ms but for safety
        temp = inb(0x1F7);
    }
    else
    {
        outb(0x176, 0xA0);
        sleep(5); // you have to wait 400ns or 4 ms but for safety
        temp = inb(0x177);
    }

    if (temp & 0x40)
    {
        print("\MASTER DRIVE EXITS\n");
        IDE_DRIVE = 0;
    }
    else
    {
        print("\nMASTER DRIVE DO NOT EXITS\n");
    }

    if (IDE_CONTROLLER == 1)
    {
        outb(0x1F6, 0xB0);
        sleep(5); // you have to wait 400ns or 4 ms but for safety
        temp = inb(0x1F7);
    }
    else
    {
        outb(0x176, 0xB0);
        sleep(5); // you have to wait 400ns or 4 ms but for safety
        temp = inb(0x177);
    }

    if (temp & 0x40)
    {
        print("\nSLAVE DRIVE EXITS\n");
        IDE_DRIVE = 1;
    }
    else
    {
        print("\nSLAVE DRIVE DO NOT EXITS\n");
    }

    if (IDE_CONTROLLER == 1)
        DRIVE_SIZE = inw(0x1F2);
    else
        DRIVE_SIZE = inw(0x172);

    print("\nSIZE OF SELECTED DRIVE ");
    print_num(DRIVE_SIZE);

    print("\n\n");
}