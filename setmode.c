/* this line includes DJGPP's DPMI functions and data structures so we can use them in our
   program. This lets us set registers to specific values and call interrupts - things
   we normally can't do in C. */
#include <dpmi.h>


/* this line creates a constant, TEXT_MODE. Anywhere in our code that TEXT_MODE appears from
   now on, it'll be replaced by 3. This is done for clarity purposes - instead of making
   the reader wonder what 3 means, they'll know immediately we're specifying text mode.*/
#define TEXT_MODE 3

#define SET_MODE 0
#define VIDEO_INT 0x10

/* A function is a piece of independent code that optionally takes some parameters and 
   optionally gives back a value. For example, we might have a function add_five(), which
   would take a number and give back that number plus 5. In our code we'd call add_five():

   x = add_five(7);

   And, if add_five() was working properly, x would equal 12 (because 7+5=12, of course).

   This line is a function prototype. It 'declares' the function - it tells the compiler (from
   left to right) the function's return type (void means it returns nothing), name, and
   the arguments it takes - here, it takes only one argument, an unsigned char called mode.
   That it's a char means that it's one byte. That it's unsigned, as opposed to signed,
   means that it stores numbers from 0-255, rather than -127-128.

   In C we like to declare functions before we 'define' them - i.e. provide their code. This
   way we can use the function before it's defined. If we keep all our declarations 
   up front, before all our code, we never need to worry about making sure we never call a
   function before it's declared. In the main() function below, we call set_video_mode(). If
   not for this declaration up above, we'd need to move set_video_mode()'s definition above
   main(). In large programs with lots of functions, putting defintions in the right order
   would be a burden. So let's just declare all our functions ahead of time. Except for
   main(), because main() is a special function that needs no declaration.
*/
void set_video_mode(unsigned char mode);


/* main() is a special function - the entry point - for all C programs. When your program
   starts, it starts in main(). It must return an int - this is a 32-bit value that it gives back
   to DOS to say whether or not the program was successful. It can either take no arguments,
   or it can take an int and a char** - I'll explain this later, I promise! - that includes
   the arguments given on the command line */
int main() {
    /* here we call set_video_mode() twice, each time with a different argument. Inside
       the function, the argument will be copied into a variable called mode.

       In the first case, we provide 0x13, because we want to switch into mode 13h. In the
       second case, we want to return to text mode, so we pass it TEXT_MODE - which, because
       of the constant we defined earlier, is replaced by 3. 
    */
    set_video_mode(0x13);
    set_video_mode(TEXT_MODE);

    /* this returns 0 back to DOS. By convention, a 0 means success - anything else means
       something went wrong */
    return 0;
}

/* here is our actual function definition for set_video_mode() */
void set_video_mode(unsigned char mode) {
    /* here we create a __dpmi_regs structure called r. A structure is a way of clustering
       related data together - this particular structure contains variables for all the different
       registers in the CPU. By setting the 'fields' inside our structure to certain
       values, we're specifying what we want the registers to be set to when we make our
       interrupt call */
    __dpmi_regs r;

    /* here we set AL to the mode we want to change to */
    r.h.al = mode;

    /* and AH to the set mode function, designated by 0 */    
    r.h.ah = SET_MODE;
  
    /* this calls a DPMI function that performs the interrupt
       the VIDEO_INT (0x10) means we want interrupt 0x10, which calls the video function
       selected by the contents AH
       the &r means we're telling the function where r is located in memory - its address,
       so it can access it */
    __dpmi_int(VIDEO_INT, &r);
}