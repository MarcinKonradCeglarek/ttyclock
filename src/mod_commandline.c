#include "mod_commandline.h"


void TC_check_parameters(int argc, char *argv[])
/* based on a unix getopt liblary. For specific information
 * consult 'man 3 getopt'. Structure "option" is already
 * declared in getopt.h */
{
    int op=0,op_tmp;
    int *optindex=&op_tmp;
    int flags[10] = {0,0,0,0,0,0,0,0,0,0};
    int exitcode;
    
    struct option long_opts[] = {
	{"help",0,&op_tmp,'h'},
	{"language",1,&op_tmp,'l'},
	{"color",1,&op_tmp,'c'},
	{"count",1,&op_tmp,'u'},
	{"countdown",1,&op_tmp,'u'},
	{"stoper",0,&op_tmp,'s'},
	{"timer",0,&op_tmp,'t'},
	{"run",1,&op_tmp,'r'},
	{"notify",1,&op_tmp,'n'},
	{0,0,0,0}
    };
    
    TC_debug("check_parameters()",0,0);

    // while op is not equal -1 (which means that getopt has found an option) do:
    while (op!=-1)
    {
	/* invoke getopt(). It's bahavior varies depend on what type of option 
	 * has been found. For short option it returns the char of an option which
	 * was found, and optionaly a string 'optarg' which contains it's arguments
	 * For long option getopt return '0', and the char of the option is returned
	 * to the memory adress &op_tmp. Yet argument of an option is still returned
	 * in optarg string */
    	op=getopt_long_only(argc, argv, "hl:c:u:str:n:", long_opts, optindex);
		

	// if option has been found check for returned code (it's char)	
	if (op==0)
	{
	    TC_debug("long option found",0,0);
	    op=op_tmp;
	    
	}
	switch (op) 
	{
	    case -1:
	    break;
	    
	    case 'h':
	        TC_found_flag_help(argv[0]);
	    break;
		
	    case 'l':
		TC_found_flag_languages(flags,optarg);
	    break;	

	    case 'c':
		TC_found_flag_colors(flags,optarg);
	    break;
		
	    case 't':
		TC_found_flag_timer(flags);
	    break;
	
	    case 'u':
		TC_found_flag_counter(flags,optarg);
	    break;
	
	    case 'r':
		TC_found_flag_run(flags,optarg);
	    break;

	    case 'n':
		TC_found_flag_notify(flags,optarg);
	    break;

	    case 's':
		TC_found_flag_stoper(flags);
	    break;
	
	    default:
		TC_debug("check_parameters() -> case default",0,0);
		exitcode=TC_ARGUMENT_IS_INVALID;
		fprintf(stderr, ":: %d: %c\n",op, op);
		TC_abnormal_termination(exitcode, "opt");
	    break;
	}
	
	/* before leaving check for --countdown and --system flag.
	 * it might be invoked in command line BEFORE the --timer flag
	 * which makes it impossible to guess whenever it is correct or not before
	 * checking for all options */
	TC_debug("check countdown flag",0,0);
	exitcode=TC_check_flags(flags, TC_CHECK_COUNTDOWN);
	TC_abnormal_termination(exitcode, "--countdown");

	exitcode=TC_check_flags(flags, TC_CHECK_SYSTEM);
	TC_abnormal_termination(exitcode, "--system");
	/* the same applies to --run flag */

    }
}


/* This is a set of functions for each of flag that can be given on command line
 * for greater modularity i put them here (they are doubled for short and long
 * options */

void TC_found_flag_help(char *name)			// --help
{
	TC_debug("option -h found",0,0);
	TC_print_help(name);
	exit(0);
}


void TC_found_flag_stoper(int flags[10])		// --stoper
{
	int exitcode;

	TC_debug("option -s found",0,0);
	exitcode=TC_check_flags(flags, TC_SET_STOPER);
	TC_abnormal_termination(exitcode, "--stoper");		
	
	mode=STOPER_MODE;
	timer0=time(0);
}

void TC_found_flag_timer(int flags[10])		// --timer
{
	int exitcode;

	TC_debug("option -t found",0,0);
	exitcode=TC_check_flags(flags, TC_SET_TIMER);
	TC_abnormal_termination(exitcode,"--timer");
	
	mode=TIMER_MODE;
	timer0=time(0)+3600-(time(0)%3600);
}


void TC_found_flag_counter(int flags[10], char *optarg)	// --countdown, --count
{
	int exitcode;
	int i=0;
	int tmp=0;

	// used while checking for letters
	int time_flags[3]={0,0,0};

   	TC_debug("option -u found",0,0);	    
	exitcode=TC_check_flags(flags, TC_SET_COUNTDOWN);
	TC_abnormal_termination(exitcode,"--countdown");
	timer0=time(0);

	TC_debug(optarg,0,0);

	// checking if in argument string there are only correct characters: 0-9, 'd', 'm' or 's'
	while (i!=strlen(optarg))
	{
		if (!( ( optarg[i]>='0' && optarg[i]<='9') || optarg[i]=='h' ||  optarg[i]=='m' || optarg[i]=='s' ))
			TC_abnormal_termination(TC_ARGUMENT_IS_INVALID, optarg);
		i++;
	}

	TC_debug("string has valid characters",0,0);	
	/* here the function checks what did a user put as an argument. The most part of this code is
	 * checking for possible errors in argument */
	i=0;
	while (i!=strlen(optarg))
        {
		// if current char is an ordinary digit add it to the tmp
		if (optarg[i]>='0' && optarg[i]<='9')
			tmp=tmp*10 + optarg[i]-'0';
		else

			// else ckeck what of thise three letters it is:
			switch (optarg[i])
			{

				case 'h': 
					TC_debug("adding hours",0,0);
					// hours cannot be AFTER minutes or seconds in the string
					if (! ( time_flags[0] || time_flags[1] || time_flags[2] ) )
					{
						timer0+=(tmp*3600); 
						tmp=0; 
						time_flags[0]=1;
					} else 
						// if they are then raport invalid format
						TC_abnormal_termination(TC_ARGUMENT_HAS_WRONG_FORMAT, optarg);
				break;


				case 'm': 
					TC_debug("adding minutes",0,0);
					// minutes cannot be before seconds in the string
					if (! ( time_flags[1] || time_flags[2] ) )
                    {
                        timer0+=(tmp*60);
                        tmp=0;
                        time_flags[1]=1;
                    } else
                        TC_abnormal_termination(TC_ARGUMENT_HAS_WRONG_FORMAT, optarg);
				break;

				case 's': 
					TC_debug("adding seconds",0,0);
					if (! (  time_flags[2] ) )
					{
						timer0+=(tmp); 
						tmp=0; 
						time_flags[2]=1; 
					} else 
						TC_abnormal_termination(TC_ARGUMENT_HAS_WRONG_FORMAT, optarg);

				break;
			}
		i++;
	}
	
}


void TC_found_flag_run(int flags[10], char *optarg)		// --run
{
	TC_debug("option -r found",0,0);
}


void TC_found_flag_notify(int flags[10], char *optarg)	// --notify
{
	TC_debug("option -n found",0,0);
}

void TC_found_flag_languages(int flags[10],char *optarg)	// --languages
{
	int exitcode;

	TC_debug("option -l found",0,0);
	exitcode=TC_check_flags(flags, TC_SET_LANGUAGE);
	TC_abnormal_termination(exitcode, "--language");
	
	TC_debug("checking language",0,0);	
	
	if (! strcmp( optarg, "digital" ) )
	{
	    TC_debug("setting 'digital' language",0,0);
	    use_lang=0;
	} 
	else if (! strcmp( optarg, "bcd" ) ) 
	{
	    TC_debug("setting 'bcd' language",0,0);
	    use_lang=1;
	} 
	else if (! strcmp( optarg, "binary" ) ) 
	{
	    TC_debug("setting 'binary' language",0,0);
	    use_lang=2;
	} 
	else if (! strcmp( optarg, "predator" ) ) 
	{
	    TC_debug("setting 'predator' language",0,0);
	    use_lang=3;
	} 
	else if (! strcmp( optarg, "roman" ) ) 
	{
	    TC_debug("setting 'roman' language",0,0);
	    use_lang=4;
	} 
	else 
	    TC_abnormal_termination(TC_UNKNOWN_LANGUAGE, optarg);
}


void TC_found_flag_colors(int flags[10], char *optarg)	// --colors
{
	int exitcode;
	int i=0, struct_ptr=0;
	int tmp;
	
   	TC_debug("option -c found",0,0);	    
	exitcode=TC_check_flags(flags, TC_SET_COLOR);
	TC_abnormal_termination(exitcode, "--color");	

	while ( strcmp(colors[i].name, optarg) && strcmp(colors[i].name,"end") )
	    i++;

   	TC_debug("checking the predefined color structure",0,0);	    	
	if ( strcmp(colors[i].name,"end") )
	{
	    color_sheme=colors[i].name;
	    TC_debug("setting predefined color",0,0);
	    fprintf(stderr, "%s\n",color_sheme);
	    return;
	} else {
	    if (strlen(optarg)==6)
	    {
	    	TC_debug("checking for web-like color sheme",0,0);
		i=0;
		while (i<6)
		{
			if (!(( optarg[i]>='0' && optarg[i]<='9' ) || ( optarg[i]>='a' && optarg[i]<='f' ) || ( optarg[i]>='A' && optarg[i]<='F' ) )) 
			    TC_abnormal_termination(TC_ARGUMENT_IS_INVALID, optarg);
			i++;
		}

		color_sheme="user";
		while ( strcmp(colors[struct_ptr].name,"user") )
		    struct_ptr++;

		
		// stepbystep 
		for (i=0; i<=4; i=i+2)
		{
		    tmp=0;
		    
    		    if ( optarg[i] >= '0' && optarg[i] <= '9')
		        tmp=16 * ( optarg[i] - '0');
		    else if ( optarg[i] >= 'a' && optarg[i] <= 'f') 
		        tmp=16 * ( optarg[i] - 'a' + 10);
		    else 
	    	        tmp=16 * ( optarg[i] - 'A' + 10);
		

    		    if ( optarg[i+1] >= '0' && optarg[i+1] <= '9')
		        tmp = tmp + ( optarg[i+1] - '0');
		    else if ( optarg[i+1] >= 'a' && optarg[i+1] <= 'f') 
		        tmp = tmp + ( optarg[i+1] - 'a' + 10);
		    else 
	    	        tmp = tmp + ( optarg[i+1] - 'A' + 10);

		    tmp*=4;
		    
		    if (tmp>999)
			tmp=999;

		    switch(i)
		    {
			case 0: colors[struct_ptr].r=tmp;
				fprintf(stderr, "user_color.red: %d\n", tmp);
			break;
			case 2: colors[struct_ptr].g=tmp;
				fprintf(stderr, "user_color.green: %d\n", tmp);			
			break;
			case 4: colors[struct_ptr].b=tmp;
				fprintf(stderr, "user_color.blue: %d\n", tmp);			
			break;
		    }
		}

	    } else {
		TC_debug("It's not a valid color scheme!",0,0);
		TC_abnormal_termination(TC_UNKNOWN_COLOR_SHEME, optarg);
	    }
	}
}




int TC_check_flags(int flags[10], const int flag)
/* this function check whenever there are already marked flags (which 
 * means that there are duplicated flags in command line) or is it 
 * possibble to mark this flags in configuration on input. lots of combinations 
 * are not possible! */

/* 
    flags[] - flag register
    flag - current flag (which is being checked
*/
{

    /* this routine is invoked at the end of check_parameters()
     * function to check for incorrect flags. Actually it only checkes
     * for two incorrect flag combinations:
     *  -countdown without -timer
     *  -run without -timer                                */
     
    /* checking for --countdown flag */
    if (flag==TC_CHECK_COUNTDOWN)
	if (flags[TC_SET_COUNTDOWN])
	    if (flags[TC_SET_TIMER])
		// if both countdown and timer are set - it's ok
		return TC_OK;
	    else
		// if not then we should return error
		return TC_FLAG_T_NOT_SET;
	else
	    return TC_OK;
    
    /* checking for --run flag */
    else if (flag==TC_CHECK_SYSTEM)
	if (flags[TC_SET_SYSTEM])
	    if (flags[TC_SET_TIMER])
		// if both countdown and timer are set - it's ok
		return TC_OK;
	    else
		// if not then we should return error	    
		return TC_FLAG_T_NOT_SET;
	else
	    return TC_OK;

    // if flags are duplicated it's permanent error :(	    
    else if (flags[flag]==1)
	return TC_DOUBLED_OPTION;
	
    flags[flag]=1;
    return TC_OK;	    
}
