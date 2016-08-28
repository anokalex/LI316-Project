#include "splitmerge.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct _data {
    unsigned char *buf;
    int dimx;
    int n;//nb de régions
} data;

data *creer_data (unsigned char *im,int n, int dimx) {
    data* d = (data*)g_malloc(sizeof(data));
    d->buf = im; d->dimx = dimx;
    d->n=n;
    return d;
}


static gboolean fill_image (GNode *noeud, data *d) {

    region *r = noeud->data;

    int i, j;
    for (i = r->ix-1; i < r->ix+r->x-1; i++)
        for (j = r->iy-1; j < r->iy+r->y-1; j++)
            d->buf[i+j*d->dimx] = r->mu;

    // for (i = 0; i < d->dimx; i++)
    //         for (j = 0; j < d->dimx; j++) {
    //             printf("%d ", (d->buf)[i+j*d->dimx]);
    //             printf("\n");
    //         }
    (d->n)++;
    return 0;
}


int split_segment( GNode *qt, unsigned char *buf, int dimx) {

    data * d = creer_data(buf,0, dimx);
    g_node_traverse (qt, G_PRE_ORDER, G_TRAVERSE_LEAVES,
            -1, (GNodeTraverseFunc) fill_image, d);
    return d->n;

}



/* TME 9*/
void merge_segment( GSList *regions, unsigned char *buf, int dimx) {
  int i, j;
  float fillcol;
  while (regions){
      GSList * n = ((region*)regions->data)->merged;
      if(n) fillcol= ((region*)regions->data)->mu;
      while(n){
                region *r = n->data;
                for (i=r->ix -1;i<r->ix+r->x -1;i++)
                for (j=r->iy -1;j<r->iy+r->y -1;j++)
                        buf[i+j*dimx]=fillcol;
                n = n->next;
          }
      regions = regions->next;
  }

}

