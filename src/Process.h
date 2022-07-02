#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NRM "\x1B[0m"
#define NRM_ENDL "\n"
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"

#define AIS "[Arch installer script]"
#define PRINT_ERROR(message) printf(RED AIS "<Error: %s>" NRM_ENDL, message);

static int RunProcess(const char* process, const char* sinp) // stdin pipe
{
    fflush(stdout);
    FILE* p = popen(process, "w");
    if(p == NULL)
    {
        printf(RED AIS "<Error: couldn't start subprocess [%s]" NRM_ENDL, process);
        return -1;
    }
    printf(GRN AIS "<Successfully started subprocess [%s]" NRM_ENDL, process);

    if(sinp != NULL)
    {
        if(fprintf(p, "%s", sinp) < 0) {
            printf(MAG AIS "<Error: writing to stdin of subprocess [%s] | stdin: %s" NRM_ENDL, process, sinp);
        }
        else {
            printf(BLU AIS "<Successfully wrote to stdin of subprocess [%s] | stdin: %s" NRM_ENDL, process, sinp);
        }
    }

    int status;
    if((status = pclose(p)) == -1) {
        printf(RED AIS "<Error: failed to close subprocess [%s]" NRM_ENDL, process);
        return status;
    }
    printf(GRN AIS "<Successfully finished subprocess [%s]" NRM_ENDL, process);
    return WEXITSTATUS(status);
}
