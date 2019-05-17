#if defined DEBUG
#include<stdio.h>
#define DEBFILE "log.txt"
FILE *logF;
#define DEBUG_INT(i) {\
                        if(logF == NULL)\
                            logF = fopen(DEBFILE,"w");\
                        fprintf(logF,"%d", i);\
                        fclose(logF);\
                        logF = fopen(DEBFILE,"a");\
                     } 
#define DEBUG_STR(String) {\
                            if(logF == NULL)\
                                logF = fopen(DEBFILE,"w");\
                            fprintf(logF,"%s", String);\
                            fclose(logF);\
                            logF = fopen(DEBFILE,"a");\
                          } 
#define DEBUG_CHR(c) {\
                      if(logF == NULL)\
                        logF = fopen(DEBFILE,"w");\
                      fprintf(logF,"%c", c);\
                      fclose(logF);\
                      logF = fopen(DEBFILE,"a");\
                     }  


#else 

#define DEBUG_INT(i)  
#define DEBUG_STR(String)   
#define DEBUG_CHR(c) 

#endif

#define Lucas ;
