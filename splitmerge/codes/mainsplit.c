#include <inrimage/image.h>
#include "splitmerge.h"


int main( int argc, char **argv) {
  struct image *nf;
  Fort_int lfmt[9];
  unsigned char *buf;
  char nom[128];
  GNode *qt;
  float split_thresh = 100;
  int count, xmin = 2, ymin = 2;
  int nbits;
  int nb_regions;
  inr_init ( argc, argv, "1.0",
	     "[input] [output] [-min xmin ymin] -s seuil",
	     "segmentation par split");

  infileopt( nom);
  nf = image_( nom, "e", "", lfmt);
  if ( TYPE != FIXE || BSIZE != 1)
    imerror( 6, "Codage non acceptable\n");
  buf = i_malloc(DIMX*DIMY);
  c_lect( nf, DIMY, buf);
  fermnf_( &nf);

  igetopt1( "-s", "%f", &split_thresh);
  igetopt2( "-min", "%d", &xmin, "%d", &ymin);

  qt = split( buf, DIMX, DIMY, split_thresh, xmin, ymin);

  /*fprintf( stderr, "stats image: %g %g\n",
	   ((region*)qt->data)->mu, ((region*)qt->data)->var);*/

    //split_print_regions(qt);

  /* Compléter cette partie pour répondre à la question
     1.3: appel à split_segment() et écriture image */
    nb_regions=split_segment( qt,buf,DIMX);

  /* Compléter cette partie pour répondre à la question
     1.4 : affichage des statistiques */
        fprintf(stderr,"nombre de régions: %d\n",nb_regions);
    /* Pourquoi est-il utile de connaître la variance de l'image?*/

    //Ecriture de l'image
    outfileopt(nom);
    nf = c_image(nom, "c", "", lfmt);
    c_ecr( nf, DIMY, buf);
    fermnf_( &nf);
    //i_Free((void*)&buf);

    return 0;

}
