#ifndef FONT_H
#define FONT_H

extern void plot(int pos_x, int pos_y, const char * fmt, ...);
extern void plot_shaded(int pos_x, int pos_y, const char * fmt, ...);
extern void plot_alpha(unsigned char alpha);

#endif