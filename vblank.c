/* to wait for vblank, we need to get information from the PC's "port" system.
   The PC contains a number of numbered "ports" - the principle is sort of like
   how memory cells are numbered. Unlike memory cells, however, some ports we
   can only read to, others we can only write to, and sometimes if we read from
   a port it won't contain what we wrote to it. We use ports for their 
   side-effects, rather than storage - typically they're connected to different
   devices inside the PC, like the graphics card or the sound card, and reading
   and writing to ports lets us find out whether we're in vblank or tell the
   sound card to play a note.

   To access the ports, we use the inportb() and outportb() functions. For
   inportb(), you'll give it a port to read from and it'll return a byte read
   from that port. We get access to these functions by #include'ing the
   pc.h file */
#include <pc.h>

void wait_for_vblank() {
    /* to wait for vblank, we query port 0x3DA. It returns a byte; when the 
       third bit of this byte is 1, we're in vblank. To determine if the third 
       bit is set, we perform a binary AND operation between the byte and 
       00000100b, or 8 in decimal. An AND operation very quickly goes through 
       each bit of the two numbers and produces a 1 only if the corresponding 
       bits are set in both numbers. So, for example, if port 0x3DA returns 
       11011101b:

          11011101
          00000100
       AND--------
          00000100

       So we're in vblank. But if it returns 01010001b:

          01010001
          00000100
       AND--------
          00000000

       So we're not. 

       Here we have a while loop. A while loop executes a piece of code as long
       as (that is, "while") some condition is true.

       In C, a condition is considered true if it's anything but 0. Here the 
       loops do nothing but wait - try to understand how they work. */

       /* wait until we're not in vblank */
       while(inportb(0x3DA) & 8){;}															    
       /* wait until vblank starts again - the ! means not. It's like we're 
       saying "wait until we're not(not in vblank)". */
       while(!(inportb(0x3DA) & 8)){;}
}
