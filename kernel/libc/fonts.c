#include "raster8x8.h"

typedef struct font
{
    line_t lines[5];
    int len;
} font_t;

void drawline(line_t l, uint32_t color)
{
    float m = l.slope;
    int len = l.len;

    for (int i = 0; i < len; i++)
    {
       
       for(int j = 0; j < 3; j++)
            putpixel(j+(int)(l.start.x + i * (1 / sqrt(m * m + 1))), (int)(l.start.y + i * (m / sqrt(m * m + 1))), color);
    }
}

font_t fonts[26] =
    {
        /// for  'A'
        {{{500, 100, (point_t){0, 0}},
          {500, 100, (point_t){10, 0}},
          {10, 0, (point_t){0, 0}},
          {10, 0, (point_t){0, 10}}},
         4},

        /// for 'B'
        {{
             {500, 100, (point_t){0, 0}},
             {500, 100, (point_t){10, 0}},
             {10, 0, (point_t){0, 0}},
             {10, 0, (point_t){0, 10}},
             {10, 0, (point_t){0, 20}},
         },
         5},

        /// for 'C'
        {{{500, 100, (point_t){0, 0}},
          {10, 0, (point_t){0, 0}},
          {10, 0, (point_t){0, 20}}},
         3},

        /// for 'D'
        {{
             {500, 100, (point_t){0, 0}},
             {14, 1, (point_t){0, 0}},
             {14, -1, (point_t){0, 20}},
         },
         3},

        /// for 'E'
        {{{500, 100, (point_t){0, 0}},
          {10, 0, (point_t){0, 0}},
          {10, 0, (point_t){0, 10}},
          {10, 0, (point_t){0, 20}}},
         4},

        //// for 'F'
        {{{500, 100, (point_t){0, 0}},
          {10, 0, (point_t){0, 0}},
          {10, 0, (point_t){0, 10}}},
         3},

        /// for 'G'
        {{{500, 100, (point_t){0, 0}},
          {250, 100, (point_t){10, 10}},
          {10, 0, (point_t){0, 0}},
          {10, 0, (point_t){0, 10}},
          {10, 0, (point_t){0, 20}}},
         5},

        /// for 'H'
        {{{500, 100, (point_t){0, 0}},
          {500, 100, (point_t){10, 0}},
          {10, 0, (point_t){0, 10}}},
         3},

        /// for 'I'
        {
            {{10, 0, (point_t){0, 0}},
             {500, 100, (point_t){5, 0}},
             {10, 0, (point_t){0, 20}}},
            3},

        /// for 'J'
        {{
             {250, 100, (point_t){0, 10}},
             {500, 100, (point_t){10, 0}},
             {10, 0, (point_t){0, 0}},
             {10, 0, (point_t){0, 20}},
         },
         4},

        /// for 'K'
        {{{500, 100, (point_t){0, 0}},
          {250, 100, (point_t){10, 10}},
          {14, -1, (point_t){0, 10}},
          {10, 0, (point_t){0, 10}}},
         4},

        /// for 'L'
        {{{500, 100, (point_t){0, 0}},
          {10, 0, (point_t){0, 20}}},
         2},

        /// for 'M'
        {{{500, 100, (point_t){0, 0}},
          {500, 100, (point_t){10, 0}},
          {7, 1, (point_t){0, 0}},
          {7, -1, (point_t){5, 5}}},
         4},

        /// for 'N'
        {{{500, 100, (point_t){0, 0}},
          {500, 100, (point_t){10, 0}},
          {14, 1, (point_t){0, 0}}},
         3},

        /// for 'O'
        {{{500, 100, (point_t){0, 0}},
          {500, 100, (point_t){10, 0}},
          {10, 0, (point_t){0, 0}},
          {10, 0, (point_t){0, 20}}},
         4},

        /// for 'P'
        {{{500, 100, (point_t){0, 0}},
          {250, 100, (point_t){10, 0}},
          {10, 0, (point_t){0, 0}},
          {10, 0, (point_t){0, 10}}},
         4},

        /// for 'Q'
        {{
             {500, 100, (point_t){0, 0}},
             {500, 100, (point_t){10, 0}},
             {10, 0, (point_t){0, 0}},
             {10, 0, (point_t){0, 20}},
             {7, 1, (point_t){5, 15}},
         },
         5},

        /// for 'R'
        {{
             {500, 100, (point_t){0, 0}},
             {250, 100, (point_t){10, 0}},
             {10, 0, (point_t){0, 0}},
             {10, 0, (point_t){0, 10}},
             {14, 1, (point_t){0, 10}},
         },
         5},

        /// for 'S'
        {{
             {250, 100, (point_t){0, 0}},
             {250, 100, (point_t){10, 10}},
             {10, 0, (point_t){0, 0}},
             {10, 0, (point_t){0, 10}},
             {10, 0, (point_t){0, 20}},
         },
         5},

        /// for 'T'
        {
            {
                {10, 0, (point_t){0, 0}},
                {500, 100, (point_t){5, 0}},
            },
            2
        },
       
       /// for 'U'
        {{{500, 100, (point_t){0, 0}},
          {500, 100, (point_t){10, 0}},
          {10, 0, (point_t){0, 20}}},
         3},

        /// for 'V'
        {{
          {250, 100, (point_t){0, 0}},
          {300, 100, (point_t){10, 0}},
          {12, 2, (point_t){0, 10}},
          {10, -1.5, (point_t){5, 20}}
        },
         4},

         /// for 'W'
        {{{500, 100, (point_t){0, 0}},
          {500, 100, (point_t){10, 0}},
          {7, -1, (point_t){0, 20}},
          {7, 1, (point_t){5, 15}}},
         4},

          /// for 'X'
        {{{24, 2, (point_t){0, 0}},
          {22, -2, (point_t){0, 18}}},
         2},

          /// for 'Y'
        {{
          {24, -2, (point_t){0, 20}},
          {9, 1, (point_t){0, 0}}},
         2},
          
         /// for 'Z'
        {{
          {10, 0, (point_t){0, 0}},
          {24, -2, (point_t){0, 20}},
          {10, 0, (point_t){0, 20}}},
         3}

};

int font_space = 15;

void drawfont(char c, int x, int y, uint32_t color,int size)
{
    int j = c - 'a';

    if(j > 25 || j < 0)
        return;

    font_t f = fonts[j];

    for (int i = 0; i < f.len; i++)
    {
        f.lines[i].start.x += x;
        f.lines[i].start.y += y;

        f.lines[i].start.x *=size;
        f.lines[i].start.y *=size;

        f.lines[i].len  *=size;
        drawline(f.lines[i], color);
    }
}

void drawstring(char *str,int x,int y,uint32_t color,int size)
{
    for(int i = 0; i < strlen(str); i++)
    {
        drawfont(str[i],x + i*font_space,y,color,size);
    }
    
}

typedef struct bitmap
{
    char width,height;
} bitmap_t;


bitmap_t _FONT = {8,8};

void draw_bitmap(char *bitmap,int start_x,int start_y,uint32_t fcolor,uint32_t bcolor)
{
    uint64_t set;
    int x,y;

    for(y = 0; y < _FONT.height; y++)
    {
        for(x = 0; x < _FONT.width; x++)
        {
            set = (bitmap[x] >> y) &  1UL;
            putpixel(start_x + x,start_y + y, set ? fcolor : bcolor);
        }
    }
}