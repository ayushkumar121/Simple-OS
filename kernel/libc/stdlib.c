#define lengthof(x) sizeof(x) / sizeof(x[0])

#define TRUE 1
#define FALSE 0

typedef struct date
{
    int day;
    int month;
    int year;
} date_t;

struct time
{
    int seconds;
    int minutes;
    int hours;
};

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

typedef int *int_arr;
typedef char *char_arr;

typedef struct registers
{
    uint32_t ds;                                     /* Data segment selector */
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; /* Pushed by pusha. */
    uint32_t int_no, err_code;                       /* Interrupt number and error code (if applicable) */
    uint32_t eip, cs, eflags, useresp, ss;           /* Pushed by the processor automatically */
} registers_t;
