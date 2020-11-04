static const char *pci_class_codes[] = {
    "UNCLASSIFIED",
    "MASS_STORAGE",
    "NETWORK_CONTROLLER",
    "DISPLAY_CONTROLLER",
    "MULTIMEDIA_DEVICE",
    "MEMOMEY_CONTROLLER",
    "BRIDGE_DEVICE",
    "SIMPLE_COMM_CONTROLLER",
    "BASE_SYSTEM_PERIPHERAL",
    "INPUT_DEVICE_CONTROLLER",
    "DOCING_STATION",
    "PROCESSOR",
    "SERIAL_BUS_CONTROLLER",
    "WIRELESS_CONTROLLER",
    "INTELLIGENT_CONTROLLER",
    "SATTELITE_COMMUNICATION_CONTROLLER"};


typedef struct device
{
    uint16_t bus;
    uint8_t device;
    uint8_t func;

    uint8_t classid;
    uint8_t subclass;
    uint16_t venderid;
    uint16_t deviceid;
} device_t;

device_t devices[10];
int devices_total = 0;


uint16_t pciConfigReadWord(uint8_t bus, uint8_t device, uint8_t func, uint8_t offset)
{
    uint32_t address;
    uint32_t lbus = bus;
    uint32_t ldevice = device;
    uint32_t lfunc = func;
    uint16_t tmp = 0;

    address = (uint32_t)((lbus << 16) | (ldevice << 11) |
                         (lfunc << 8) | (offset & 0xfc) | ((uint32_t)0x80000000));

    outl(0xCF8, address);
    tmp = (uint16_t)((inl(0xCFC) >> ((offset & 2) * 8)) & 0xffff);
    return (tmp);
}

int checkDevice(uint8_t bus, uint8_t device, uint8_t func)
{
    return (pciConfigReadWord(bus, device, func, 0x00) != 0xFFFF) && (pciConfigReadWord(bus, device, func, 10) >> 8 != 0xFF);
}

void listpci()
{
    print("\n\n\n");

    for(int i = 0; i < devices_total; i++)
    {
        print(pci_class_codes[devices[i].classid]);
        print("\n\n");
    }
}


void init_pci()
{
    uint16_t bus;
    uint8_t device;
    uint8_t func;

    for (bus = 0; bus < 256; bus++)
    {
        for (device = 0; device < 32; device++)
        {
            for (func = 0; func < 8; func++)
            {
                if (checkDevice(bus, device, func))
                {
                    uint8_t classid = pciConfigReadWord(bus, device, func, 10) >> 8;
                    uint8_t subclass = pciConfigReadWord(bus, device, func, 10);
                    uint16_t venderid = pciConfigReadWord(bus, device, func, 0);
                    uint16_t deviceid = pciConfigReadWord(bus, device, func, 2);
                    
                    devices[devices_total].bus = bus;
                    devices[devices_total].device = device;
                    devices[devices_total].func = func;
                    devices[devices_total].classid = classid;
                    devices[devices_total].subclass = subclass;
                    devices[devices_total].venderid = venderid;
                    
                    devices_total++;
                }
            }
        }
    }
}

device_t getdrive()
{
    device_t drive;

    for(int i = 0; i < devices_total; i++)
    {
        if(devices[i].classid == 0x01 && devices[i].subclass == 0x01)
        {
            drive = devices[i];
            break;
        }
    }
}