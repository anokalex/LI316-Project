#include "splitmerge.h"
/* tme 8 */
int predsplit( region *r, float threshold) {
    return r->var > threshold;
}

float maxnb(float a,float b){
    if (a>=b)
        return a;
    else
        return b;
}
/* tme 9 */
int predmerge( region *a, region *b, float thresh) {

    float mu,var;
    mu = (a->n*a->mu + b->n*b->mu) / (a->n + b->n);
    var = (a->n * (a->var + a->mu*a->mu) + b->n * (b->var + b->mu*b->mu)) / (a->n + b->n)
        - mu*mu;

    if(var <= thresh|| var <= maxnb(a->var,b->var)){
        a->var = var;
        a->mu = mu;
        a->n += b->n;
        return 1;
    }

    return 0;

}
