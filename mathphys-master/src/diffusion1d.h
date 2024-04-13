
/*
 * diffusion1d(...)             solves a 1-dimensional diffusion equation
 *              \partial^2 u / \partial x^2 = \partial u / \partial t
 *              and prints u(*,t_j) into "diffusion1d.txt"
 * double xa
 * double xb                    x zone [xa, xb]
 * double (*g_initial)(...)     u(x, t=0)
 * double ta
 * double tb                    t zone [ta, tb]
 * double (*boundary_a)(...)    u(xa, t)
 * double (*boundary_b)(...)    u(xb, t)
 * int Nx                       grid point number in (xa,xb)
 * int Nt                       grid point number in (ta,tb)
 */
void diffusion1d( double xa, double xb, double (*g_initial)(double x), double ta, double tb, double (*boundary_a)(double t), double (*boundary_b)(double t), int Nx, int Nt);
