
// See this----https://tronche.com/gui/x/xlib/graphics/images.html
// To compile: gcc -shared -O3 -lX11 -fPIC -Wl,-soname,screen -o screen.so screen.c
#include <stdio.h>
#include <X11/X.h>
#include <X11/Xlib.h>
//#include <X11/Xutil.h>

void XDestroyImage(XImage *img);
unsigned long XGetPixel(XImage *img,int x, int y);
void getScreen(const int, const int, const int, const int, unsigned char *);
void getScreen(const int xx,const int yy,const int W, const int H, /*out*/ unsigned char * data)
{
   Display *display = XOpenDisplay(NULL);
   Window root = DefaultRootWindow(display);

   XImage *image = XGetImage(display,root, xx,yy, W,H, AllPlanes, ZPixmap);

   unsigned long red_mask   = image->red_mask;
   unsigned long green_mask = image->green_mask;
   unsigned long blue_mask  = image->blue_mask;
   unsigned long pixel;
   unsigned char blue;
   unsigned char green;
   unsigned char red;
   int x, y;
   int ii = 0;
   for (y = 0; y < H-1; y++) {
       for (x = 0; x < W; x++) {
          pixel = XGetPixel(image,x,y);

          blue  = (pixel & blue_mask);
          green = (pixel & green_mask) >> 8;
          red   = (pixel & red_mask) >> 16;

         data[ii + 2] = blue;
         data[ii + 1] = green;
         data[ii + 0] = red;

         ii += 3;

      }

   }
   XDestroyImage(image);
   XDestroyWindow(display, root);
   XCloseDisplay(display);
}

