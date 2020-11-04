#define CMD_COUND 10

typedef void (*function)(void);

function cmds[100];

char *cmd_names[CMD_COUND] =
    {
        "col",
        "cls",
        "rnd",
        "pci",
        "hlp",
        "dte",
        "hdd",
        "dir"};

void COL()
{
    char buffer;

    print("\n\n");
    print("color(hex) = #");
    gets(buffer);
    print("\n");

    setcolor(atoi(buffer), terminal_bcolor);
}

void DTE()
{
    date_t d = getDate();

    print("\n\n");

    print("date : ");
    print_num(d.day);
    print(" / ");
    print_num(d.month);
    print(" / ");
    print_num(d.year);

    print("\n");
}

void CLS()
{
    int tempy = starty;

    if (tempy > 746)
        tempy = 746;

    for (int i = 30; i < tempy + 8; i += 8)
    {
        for (int j = 15; j < 120 * 8; j += 8)
        {
            setcursor(j, i);
            print(" ");
        }
    }

    setcursor(7, 7);
}

void RND()
{
    srand(getTimems());
    print("\n\n");
    print_num(rand());
    print("\n");
}

void PCI()
{
    listpci();
}

void HLP()
{
    print("\n\n");

    for (int i = 0; i < CMD_COUND; i++)
    {
        print(cmd_names[i]);
        print("\n");
    }

    print("\n");
}

void HDD()
{
    /*
    print("\n\n");
    
    if(IDE_DRIVE == -1)
    {
        print("DRIVE NOT FOUND");
    }
    else
    {
        print("DRIVE CONNECTED");
    }

    print("\n");
    */
}

void DIR()
{
    print("\n\n");
    
    for(int i = 1; i <= files; i++)
    {
        print_num(i);
        print(". ");
        print(headers[i]->name);
        print(" : ");
        print_num(getsize(headers[i]->size));
        print("\n");
    }

    print("\n");   
}

void init_cmd()
{
    cmds[0] = &COL;
    cmds[1] = &CLS;
    cmds[2] = &RND;
    cmds[3] = &PCI;
    cmds[4] = &HLP;
    cmds[5] = &DTE;
    cmds[6] = &HDD;
    cmds[7] = &DIR;
}

void run_cmd(char *cmd)
{
    int flag = 0;

    for (int i = 0; i < CMD_COUND; i++)
    {
        if (strcmp(cmd, cmd_names[i]))
        {
            flag = 1;
            cmds[i]();
            break;
        }
    }

    if (!flag)
        print_err("COMMAND NOT FOUND");
}
