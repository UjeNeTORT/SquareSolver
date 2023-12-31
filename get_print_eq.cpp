#include <assert.h>
#include <ctype.h>
#include <stdio.h>

#include "equation.h"
#include "get_print_eq.h"

//-----------------------------------------------------
/**
 * @brief clears buffer
 * @returns '\n' if the last symbol in buffer was '\n' \n
 *           EOF if the last symbol in buffer was EOF \n
 *           0   if it encountered not-space symbols while cleaning the buffer \n
*/
static int clearBuff(void);

int readCoefs(struct equation *eq) {
    assert (eq);

    static const int MAX_MISTAKES = 10;
    int buffClearRes = 0, cntWrngLines = 0, scanfRes = 0;

    printf("# Please, enter a, b, c coefs:\n");

    while (true) {

        buffClearRes = 0;

        if ((scanfRes = scanf("%lf %lf %lf", &eq->a, &eq->b, &eq->c)) == 3 && (buffClearRes = clearBuff()) != 0) break;

        if (scanfRes != 3)
            buffClearRes = clearBuff();

        if (buffClearRes == EOF)
            return ERR_EOF;

        printf("Incorrect input, try again\n");

        if (cntWrngLines++ >= MAX_MISTAKES)
            return ERR_OVERFLOW_INPUT;
    }

    return 0;
}

void printResult(struct equation *eq) {
    assert (eq);

    switch(eq->nRoots) {
        case 0:
            printf("no solutions\n");
            break;
        case 1:
            printf("1 solution:\n"
                   "%.3lf\n", eq->x1);
            break;
        case 2:
            printf("2 solutions:\n"
                   "%.3lf , %.3lf\n", eq->x1, eq->x2);
            break;
        case ROOTS_INF:
            printf("infinite solutions\n");
            break;
        default:
            printf("printResult: solveQuadrEq returned breeeed\n");
            break;
    }
}

static int clearBuff(void) {
    int garbage = 0, notStumble = 1;

    while ((garbage = getchar()) != '\n' && garbage != EOF) {
        if(!isspace(garbage))
            notStumble = 0;
    }

    return (notStumble) ? garbage : 0;
}
