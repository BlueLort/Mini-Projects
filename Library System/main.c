/*
                        DEVELOPED BY OMAR NASR IBRAHIM - Univ.ID:4730
                        emaranasr@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>

#include "menuEventHandler.h"

int main()
{

    progStart();
    while(RUNNING)
    {
        menuHandler();
    }

    return 0;
}
