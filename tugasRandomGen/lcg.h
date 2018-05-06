/**********************************************/
/* linear congruential generator              */
/* copyleft (c). Ridlo W. Wibowo              */
/* based on Microsoft formula                 */
/**********************************************/
#ifndef LCG_H
#define LCG_H
#include <math.h>
#define MAX_RAND 32767

/* default seed */
static unsigned long int state = 1;

/* change seed */
void rseed(unsigned int s){
    state = s;
}
 
/* Linear Congruential Generator */
int randu(){
    unsigned int multiplier = 214013;
    unsigned int increment = 2531011;
    unsigned int modulo = pow(2,31);
    
    state = (state*multiplier + increment)%modulo;
    return state/pow(2,16);
}
#endif
