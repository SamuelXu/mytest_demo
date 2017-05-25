#include <stdio.h>

//方法1
#define _MKSTR(x) #x
#define MKSTR(x) _MKSTR(x)
const char* version = MKSTR(BUSSINESS_ID)"."MKSTR(PLATFORM_ID)"."MKSTR(MAIN_VERSION)"."MKSTR(SUBVERSION)"."MKSTR(COMPILE_TIME);

//方法二
//#define VERSION(x, y, m, n, t)  #x"."#y"."#m"."#n"."#t
//#define XVERSION(x, y, m, n, t)  VERSION(x, y, m, n, t)
//const char* version = XVERSION(BUSSINESS_ID, PLATFORM_ID, MAIN_VERSION, SUBVERSION, COMPILE_TIME);

int main(int argc, char* argv[])
{
    char ver[50] = { 0 };
    //方法三
    sprintf(ver, "%d.%d.%d.%d_%u", BUSSINESS_ID, PLATFORM_ID, MAIN_VERSION, SUBVERSION, COMPILE_TIME);
    printf("%s\n", ver);

    printf("%s\n", version);
    return 0;
}
