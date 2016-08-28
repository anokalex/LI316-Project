#include <inrimage/image.h>
#include "splitmerge.h"


int main( int argc, char **argv) {
  struct image *nf;
  Fort_int lfmt[9];
  unsigned char *buf;
  char nom[128];
  GNode *qt;
  float split_thresh = 200;
  float merge_thresh=200;
  int count, xmin = 2, ymin = 2;
  int nbits;
  int nb_regions;
  GSList* melange;
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
  igetopt1( "-mt", "%f", &merge_thresh);
  igetopt2( "-min", "%d", &xmin, "%d", &ymin);

  qt = split( buf, DIMX, DIMY, split_thresh, xmin, ymin);

  /* Compléter cette partie pour répondre à la question
     1.3: appel à split_segment() et écriture image */
    nb_regions=split_segment( qt,buf,DIMY);

  /* Compléter cette partie pour répondre à la question
     1.4 : affichage des statistiques */
    //split_print_regions(qt);
    fprintf(stderr,"nombre de régions avant fusion: %d\n",nb_regions);
    /* Pourquoi est-il utile de connaître la variance de l'image?*/
    //Pour savoir quel est le seuil de découpage optimal à utiliser (il faut un
    //seuil assez petit pour que le nombre de pixels dans chaque région obtenue
    //ne soit pas trop élevé


    GSList* liste_regions=merge_list_regions(qt);
    melange=merge(liste_regions,merge_thresh);
    merge_segment(melange,buf,DIMY);
    fprintf(stderr,"nb de régions après fusion: %d\n",g_slist_length(melange));
    //Ecriture de l'image
    outfileopt(nom);
    nf = c_image(nom, "c", "", lfmt);
    c_ecr( nf, DIMY, buf);
    fermnf_( &nf);


  fprintf( stderr, "stats image: %g %g\n",
	   ((region*)qt->data)->mu, ((region*)qt->data)->var);


  //  i_Free((void*)&buf);


    return 0;

}
