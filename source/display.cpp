#include "display.h"
#include "string.h"
#include <unistd.h>
#include "X11/Xlib.h"

Display * gfx_display;
Window  gfx_window;
int gfx_fast_color_mode = 1;
GC gfx_gc;
Colormap gfx_colormap;

void d_open(int size_x, int size_y, const char * name)
{
    gfx_display = XOpenDisplay(0);
    gfx_window = XCreateSimpleWindow(gfx_display, DefaultRootWindow(gfx_display), 0, 0, size_x, size_y, 0, 0, 0);

    XSetWindowAttributes attr;
	attr.backing_store = Always;

	XChangeWindowAttributes(gfx_display,gfx_window,CWBackingStore,&attr);

    XStoreName(gfx_display,gfx_window, name);

    XSelectInput(gfx_display, gfx_window, StructureNotifyMask|KeyPressMask|ButtonPressMask);
	XMapWindow(gfx_display,gfx_window);

    gfx_gc = XCreateGC(gfx_display, gfx_window, 0, 0);

    gfx_colormap = DefaultColormap(gfx_display,0);

    XSetForeground(gfx_display, gfx_gc, 0x00ffffff);

    auto * font = XLoadQueryFont(gfx_display, "10x20");
    XSetFont(gfx_display, gfx_gc, font->fid);

    for(;;) {
		XEvent e;
		XNextEvent(gfx_display, &e);
		if (e.type == MapNotify)
			break;
	}
}

void d_close()
{
    XFreeGC(gfx_display, gfx_gc);
	XDestroyWindow(gfx_display, gfx_window);
	XCloseDisplay(gfx_display);		
}

void d_color(int r, int g, int b)
{
    unsigned int color = (r << 16 | g << 8 | b);

    XSetForeground(gfx_display, gfx_gc, color);
}

void d_pixel(int pos_x, int pos_y)
{
    XDrawPoint(gfx_display, gfx_window, gfx_gc, pos_x, pos_y);
}

void d_line(int start_x, int start_y, int end_x, int end_y)
{
    XDrawLine(gfx_display, gfx_window, gfx_gc, start_x, start_y, end_x, end_y);
}

void d_square(int start_x, int start_y, int size_x, int size_y)
{
    XFillRectangle(gfx_display, gfx_window, gfx_gc, start_x, start_y, size_x, size_y);
}

void d_text(int pos_x, int pos_y, const char * text)
{
    XDrawString(gfx_display, gfx_window, gfx_gc, pos_x, pos_y, text, strlen(text));
}

void d_clear(int start_x, int start_y, int size_x, int size_y)
{
    XClearArea(gfx_display, gfx_window, start_x, start_y, size_x, size_y, false);
}

void d_flush()
{
    XFlush(gfx_display);
}

char d_input_wait()
{
    XEvent event;

	d_flush();

	while(1) 
    {
		XNextEvent(gfx_display,&event);

		if(event.type==KeyPress) {

			return XLookupKeysym(&event.xkey,0);
		} else if(event.type==ButtonPress) {

			return event.xbutton.button;
		}
	}
}

void d_sleep(int ms)
{
    usleep(ms * 1000);
}