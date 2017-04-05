// This function is invoked from main() to initiate and fill the languages table with 
// correct values.
void TC_initiate_languages();


// Definition of main language char. It is used for displaying everything on screen
struct lang_char {
    char *name;
    int lp;
    int is_hor;
    int width, height;
    int segments;
    int x_rng, y_rng;
    int dwidth, dheight;


    int date_rng;
    int date_is_hor;
    int date_x_rng, date_y_rng3Q;
    int date_dwidth, date_dheight;
    int date_width, date_height;
};



/********************************************** EXTERNAL LANGUAGES *****/
extern struct lang_char lang_bcd;
extern struct lang_char lang_binary;
extern struct lang_char lang_digital;
//extern struct lang_char lang_predator;
//extern struct lang_char lang_roman;

/************************************************ EXTERNAL   DEBUG *****/
#ifdef DO_DEBUG
extern void TC_debug(char *info, int type, int stop);
#endif
#ifndef DO_DEBUG
extern inline void TC_debug(char *info, int type, int stop);
#endif
