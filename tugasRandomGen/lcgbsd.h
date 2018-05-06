/**********************************************/
/* linear congruential generator              */
/* copyleft (c). Ridlo W. Wibowo              */
/* based on BSD LCG                           */
/**********************************************/
#ifndef LCG_H
#define LCG_H
#define MAX_RAND 2147483646

/* default seed */
int state = 1;

/* change seed */
int rseed(int s){
    state = s;
}
 
/* Linear Congruential Generator */
int randu(){
    unsigned int multiplier = 1103515245;
    unsigned int increment = 12345;
    unsigned int modulo = 2147483647;
    
    state = (state*multiplier + increment)%modulo;
    return state;
}

#endif
