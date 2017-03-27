#include <stdio.h>
#include "slp.h"
#include "prog1.h"
#include "program.h"

int main() {
    A_stm statement = prog();
    printf("the maximum number of arguments of any print statement is: %d\n", maxargs(statement));
    interp(statement);
}
