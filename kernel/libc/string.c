int strlen(const char *text)
{
    int len = 0;
    while (text[len])
        len++;
    return len;
}

void reverse(char *str, int length)
{
    char temp;
    int i = 0;
    int j = strlen(str) - 1;

    while (i < j)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

void itoa(int num, char *buffer)
{
    int i = 0;
    int temp = num;

    if (num == 0)
    {
        buffer[i++] = '0';
    }

    if (num < 0)
    {
        num = -num;
    }

    while (num != 0)
    {
        int rem = num % 10;
        buffer[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / 10;
    }

    if (temp < 0)
    {
        buffer[i++] = '-';
    }

    buffer[i] = '\0';
    reverse(buffer, i);
}

int atoi(char *str) 
{ 
    int res = 0; 
   
    for (int i = 0; str[i] != '\0'; ++i) 
        res = res*10 + str[i] - '0'; 
   
    return res; 
} 


int strcmp(char *s1, char *s2)
{
    int len = (strlen(s1) > strlen(s2)) ? strlen(s1) : strlen(s2);
    for (int i = 0; i < len; i++)
    {
        if (s1[i] != s2[i])
        {
            return 0;
        }
    }

    return 1;
}

int isalpha(char c)
{
    return (c >= 'a' && c <= 'z');
}