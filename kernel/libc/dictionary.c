struct pair
{
    int key;
    int value;
};

struct dict
{
    int size;
    struct pair data[100];
};

typedef struct dict dict_t;

int dict_find(int key, dict_t d)
{
    for (int i = 0; i < d.size; i++)
    {
        if (d.data[i].key == key)
            return d.data[i].value;
    }

    return '\0';
}

void dict_add(int key, int value, dict_t *d)
{
    d->size++;
    d->data[d->size].key = key;
    d->data[d->size].value = value;
}