void solveSquare (struct equation *eq);
void solveQuadrEq (const double a, const double b, const double c, double *x1, double *x2, int *nRoots);
void solveLinEq (const double b, const double c, double *x, int *nRoots);
void solveInfRoots (int *nRoots);
void handleCoefError (int *nRoots);
int isEqual(const double a, const double b);

const double EPS = 1e-6;
