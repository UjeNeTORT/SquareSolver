//-----------------------------------------------------
/**
 * @enum input_errs
*/
//-----------------------------------------------------
enum input_errs {
    ERR_OVERFLOW_INPUT = 1, ///< if too many mistakes 
    ERR_EOF = 2             ///< if EOF occures
};

int getCoefs (struct equation *eq);
void printResult(struct equation *eq);
