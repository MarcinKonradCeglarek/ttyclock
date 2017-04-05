/* Global constatn used in whole program */
#define NAME_ "TC_"
#define VERSION "0.3.4"
#define MODDATE "17.11.2004"

/* Main debbuging varaible: if it is defined the debug 
will be turned on */
//#define DO_DEBUG 1

/* here are some definitons of work modes */
#define NORMAL_MODE 0
#define STOPER_MODE 1
#define TIMER_MODE 2


/* here are definitions for possible languages: */
#define LANG_DIGITAL 0
#define LANG_BCD 1
#define LANG_BINARY 2
//#define LANG_PREDATOR 3
//#define LANG_ROMAN 4

/* here comes definitons of exitcodes for functions */
#define TC_OK 0
#define TC_DOUBLED_OPTION 255
#define TC_INVALID_OPTIONS 254
#define TC_FLAG_T_NOT_SET 253
#define TC_UNKNOWN_COLOR_SHEME 252
#define TC_OPTION_REQUIRE_ARG 251
#define TC_ARGUMENT_IS_INVALID 250
#define TC_ARGUMENT_HAS_WRONG_FORMAT 249
#define TC_UNKNOWN_LANGUAGE 248

