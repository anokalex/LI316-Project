#include "splitmerge.h"


/* TME8 */
static
region *creer_region( unsigned char *buf, int ix, int iy, int x, int y, int dimx) {
  region *r = (region *) g_malloc( sizeof(region));
  int i,j;
  r->ix = ix;
  r->iy = iy;
  r->x  = x;
  r->y  = y;

  /* calcul des moyennes et variances de la region*/

  r -> n = x * y;
  r -> mu = r-> var = 0;
  for (j=iy;j<y+iy;j++){
	for (i=ix;i<x+ix;i++){
		unsigned char val=buf[(i-1)+(j-1)*dimx];
		r->mu+=val;
		r->var+=val*val;
		}
	}
  r->mu/=r->n;
  r->var/=r->n;
  r->var-=r->mu*r->mu;

  return r;
  
}


static
void split_rec( unsigned char *buf, int dimx, GNode *noeud, float t, int xmin, int ymin) {
  region *r = noeud -> data;
  region *sreg;

  if( r->x/2 >= xmin && r->y/2 >= ymin && 
      r->x % 2 == 0 && r->y % 2 == 0 &&
      predsplit( r, t) ) {
    sreg = creer_region( buf,r->ix,r->iy,r->x/2,r->y/2, dimx);
    split_rec( buf, dimx, g_node_append( noeud, g_node_new(sreg)), t, xmin, ymin);
    sreg = creer_region( buf,r->ix+r->x/2,r->iy,r->x/2,r->y/2, dimx);
    split_rec( buf, dimx, g_node_append( noeud, g_node_new(sreg)), t, xmin, ymin);
    sreg = creer_region( buf,r->ix,r->iy+r->y/2,r->x/2,r->y/2, dimx);
    split_rec( buf, dimx, g_node_append( noeud, g_node_new(sreg)), t, xmin, ymin);
    sreg = creer_region( buf,r->ix+r->x/2,r->iy+r->y/2,r->x/2,r->y/2, dimx);
    split_rec( buf, dimx, g_node_append( noeud, g_node_new(sreg)), t, xmin, ymin);
  }
}


GNode *split( unsigned char *buf, int dimx, int dimy, float threshold,
	      int xmin, int ymin) {
  region *racine;
  GNode *qt;
  racine = creer_region( buf, 1, 1, dimx, dimy, dimx);
  qt = g_node_new(racine);
  split_rec( buf, dimx, qt, threshold, xmin, ymin);
  return qt;
}
