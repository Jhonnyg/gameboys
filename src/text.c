#include <gb/gb.h>
#include <gb/drawing.h>

void draw_text(const char* text)
{
    const int x = 1;
    const int y = 16;
    const offset = 5;
    const x1 = offset, y1 = GRAPHICS_HEIGHT - offset - 16;
    const x2 = GRAPHICS_WIDTH - offset, y2 = GRAPHICS_HEIGHT - offset;
    color(BLACK, WHITE, SOLID);
    box(x1, y1, x2, y2, M_NOFILL);
    color(LTGREY, WHITE, SOLID);
    line(x1+1, y1+1, x2-1, y1 + 1);
    line(x1+1, y2-1, x2-1, y2 - 1);
    gotogxy(x, y);
    color(BLACK, WHITE, SOLID); 
    gprintf(text);
}

