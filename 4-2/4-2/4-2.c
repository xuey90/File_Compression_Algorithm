//
//  main.c
//  4-2
//
//  Created by Xueyong Qian on 09/04/14.
//  Copyright (c) 2014 Xueyong Qian. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>

double qatof(char *s)
{
    double val, power;
    int i, sign, sign_exp, exp;
    
    for (i = 0; isspace(s[i]); ++i) {
        ;
    }
    sign = (s[i] =='-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        ++i;
    }
    for (val = 0.; isdigit(s[i]); ++i) {
        val = 10. * val + s[i] - '0';
    }
    if (s[i] == '.') {
        ++i;
    }
    for (power = 1.; isdigit(s[i]); ++i) {
        val = 10. *val + s[i] - '0';
        power *= 10.;
    }
    if (s[i] == 'e' || s[i] =='E') {
        ++i;
        sign_exp = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-') {
            ++i;
        }
        for (exp = 0; isdigit(s[i]); ++i) {
            exp = 10 * exp + s[i] - '0';
        }
        if(sign_exp < 0)
        {
            while (exp) {
                val /= 10.;
                --exp;
            }
        }
        else
        {
            while (exp) {
                val *= 10.;
                --exp;
            }
        }
    }
    return sign * val / power;
}
int main(int argc, const char * argv[])
{
    printf("%f\n", qatof("-12.34e-4"));
    return 0;
}

