#include <time.h>
#include <stdlib.h>
#include <stdio.h>

char colours[5][10] = {"red", "blue", "yellow", "white", "black"};

int wireToCut(int numWir, char wire[6])
{
    int col[5] = {0};
    for (int i = 0 ; i < numWir ; i++)
    {
        col[wire[i]]++;
    }

    switch (numWir)
    {
        case 3:
            if (!col[0]) { return 2; } // If no red, cut 2.
            if (wire[numWir-1] == 3) { return numWir; } // If last wire is white, cut last wire.
            if (col[1] > 1) // If more than one blue wire, cut last blue wire.
            {
                for (int i = numWir-1 ; i > 0 ; i --)
                {
                    if (wire[i] == 1) { return i+1; };
                }
            } 
            return numWir; // Otherwise cut last wire.
        case 4:
            if (col[0] > 1 /*&& SERIAL % 2 */) // If more than 1 red, and odd serial number. Cut last red wire.
            {
                for (int i = numWir-1 ; i > 0 ; i --)
                {
                    if (wire[i] == 0) { return i+1; };
                }
            }
            if (wire[numWir-1] == 2 && !col[0]) { return 1; }// If last wire is yellow and no red wires, cut first wire.
            if (col[1] == 1) { return 1; } // If exactly one blue wire, cut first wire.
            if (col[2] > 1 ) { return numWir; } // If more than one yellow wire, cut last wire.
            return 2; // Otherwise cut secodn wire.
        case 5:
            if (wire[numWir-1] == 4 /*&& SERIAL % 2 */ ) { return 4; } // Last wire black, odd seriel digit. Cut fourth wire.
            if (col[0] == 1 && col[2] > 1) { return 1; } // If exactly one red, more than one yellow. Cut first.
            if (!col[4]) { return 2; } // If no black, cut second.
            return 1; // Otherwise, cut first.
        case 6:
            if (!col[2] /*&& SERIAL % 2 */) { return 3; } // No yellow, odd serial. Cut third.
            if (col[2] == 1 && col[3] > 1) { return 4; } // Exactly one yellow, more than one white. Cut fourth.
            if (!col[0]) { return numWir; } // No red, cut last.
            return 4; // Cut fourth.
    }

    return 0;
}

int wires(int seed)
{
    int numWir = (seed % 4) + 3;

    char wires[6];
    int numCol = sizeof(colours)/sizeof(colours[0]);
    for (int i = 0 ; i < sizeof(wires) ; i++)
    {
        wires[i] = ((seed >> (i*4)) & 7) % numCol;
    }
    printf("Wires: %i\n", numWir);
    for (int i = 0 ; i < numWir ; i++)
    {
        printf("Wire: %s (%i)\n", colours[wires[i]], wires[i]);
    }

    int cutting = wireToCut(numWir, wires);
    printf("Wire to cut: %i\n", cutting);
}

int main()
{
    srand(time(NULL));

    int r = rand();
    wires(r);

    return 0;
}