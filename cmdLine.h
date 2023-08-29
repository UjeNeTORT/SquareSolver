#ifndef CMD_LINE_H
#define CMD_LINE_H

const char FLG_TEST[] = "--test";
const char FLG_HELP[] = "--help";

const char DFLT_TEST_FILE[] = "test_cases.txt";

//-----------------------------------------------------
/**
 * @brief processes cmd-line args and sets flags
 *
 * @param [in] argc                 copy of param *argc* from main
 * @param [in] argv                 copy of param *argv* from main
 *
 * @param [out] launchDefaultFlag   1 - if after flags handling we should run the main program, 0 - if not
 *
 * @details
 * Look through the argv, if some args are not allowed, print error message
*/
void processCmdFlags(int argc, const char *argv[], int *launchDefaultFlag);

#endif // CMD_LINE_H
