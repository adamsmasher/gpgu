/* NOTE: Don't bother typing this out - we won't be using it. But read it over
         carefully anyway! */

/* shorts store 16-bit values on the 386 */
void plot_pixel(unsigned short x, unsigned short y, unsigned char colour) {
    __dpmi_regs r;

    /* recall that, when using the BIOS video interrupt, AH stores the
       particular video function we want the BIOS to perform. 0x0C is the
       "plot pixel" function. */
    r.h.ah = 0x0C;

    /* for the plot pixel function, AL contains the colour of pixel that we
       want to draw */
    r.h.al = colour;

    /* the CX and DX registers respectively store the X and Y coordinates where
       the pixel will be drawn.
       the "X location" is which column the pixel is in. The left-most column
       is 0 and the right-most column is 319 (as the screen is 320 pixels wide)
       the "Y location" corresponds to the pixel's row. The top row is 0, the
       bottom row is 199 */
    r.x.cx = x;
    r.x.dx = y;

    __dpmi_int(VIDEO_INT, &r);
}

