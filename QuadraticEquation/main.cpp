/**
        \brief Main file in project.
        Handles user commands:
        -help show all commands to user.
        -solve start solving polynom.
        -menu return to menu.
        -quit exit program.
*/
#include <stdio.h>
#include <assert.h>
#include "errors.h"
#include "ui.h"

static const unsigned MAX_LINE   = 10;  ///< Maximum size of buffer.
static const unsigned MAX_DEGREE =  3;  ///< Maximum possible degree of polinomial.

int main()
{
        double coeffs[MAX_DEGREE + 1] = {0};
        double roots [MAX_DEGREE] = {0};

        int n_roots = 0;

        char buff[MAX_LINE] = {'\0'};

        while (strncmp(buff, "quit", strlen("quit"))) {
                zero_arr(buff, MAX_LINE);
                printf("*******************\n"
                       "\tMenu:\n ");

                while (get_line(buff, MAX_LINE) == BUFF_OVERFLOW)
                        print_too_long(MAX_LINE);

                if (!strncmp(buff, "solve", sizeof(buff))) {
                        long degree = 0;
                        while ((degree = get_degree(MAX_DEGREE, buff, MAX_LINE)) == INVLD_SYMB_ERROR)
                                print_enter_num();

                        while (get_coefficients(coeffs, buff, MAX_LINE, degree))
                                print_enter_num();

                        polynomial_t poly = {
                                .coeffs = coeffs,
                                .degree = degree
                        };

                        n_roots = solve_polynomial(roots, &poly);
                        if (n_roots != 3) {
                                give_answer(roots, n_roots);
                                zero_arr(buff, strlen(buff));
                        }
                } else if (!strncmp(buff, "menu", sizeof(buff))) {
                        zero_arr(buff, strlen("menu"));
                } else if (!strncmp(buff, "help", sizeof(buff))) {
                        printf("\n Help:                            \n"
                               "  \tsolve --> start solving polynom \n"
                               "  \tmenu --> return to menu         \n"
                               "  \tquit --> exit program.          \n\n");
                } else if (!strncmp(buff, "quit", sizeof(buff))) {
                        return 0;
                }  else {
                        printf("\nSorry, I can't understand you.\n ");
                }

                zero_arr(buff, MAX_LINE);
        }

        return 0;
}
