float sqrt(float s)
{
    float a, b, c;

    a = 1;
    b = (a + s / a) / 2;
    c = b - a;
    a = b;

    while (c * c > 0.001)
    {
        b = (a + s / a) / 2;
        return b;
    }

    return b;
}