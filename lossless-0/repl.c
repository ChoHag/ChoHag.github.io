/*500:*/
#line 9401 "lossless.w"

#include "lossless.h"

int
main(int argc,
char**argv __unused)
{
char wbuf[BUFFER_SEGMENT]= {0};
vm_init();
if(argc> 1){
printf("usage: %s",argv[0]);
return EXIT_FAILURE;
}
vm_prepare();
while(1){
vm_reset();
printf("> ");
Acc= read_form();
if(eof_p(Acc)||Interrupt)
break;
interpret();
if(!void_p(Acc)){
write_form(Acc,wbuf,BUFFER_SEGMENT,0);
printf("%s\n",wbuf);
}
}
if(Interrupt)
printf("Interrupted");
return EXIT_SUCCESS;
}

/*:500*/
