#include <inrimage/image.h>

int main( int argc, char **argv) {
  struct image *nf;
  Fort_int lfmt[9];
  unsigned char *buf;
  char nom[128];
  int color = 255;
  int size = 0;
  long xC = 0;
  long yC = 0;
  int i, j;

  inr_init ( argc, argv, "1.0",
	     "[input] [output] [-c couleur]",
	     "Trouve le centre de gravité et le nombre des points d'une couleur donnée");
  infileopt( nom);
  nf = image_( nom, "e", "", lfmt);
  if ( TYPE != FIXE || BSIZE != 1)
    imerror( 6, "Codage non acceptable\n");
  buf = i_malloc(DIMX*DIMY);
  c_lect( nf, DIMY, buf);
  fermnf_( &nf);
  igetopt1( "-c", "%d", &color);
  for (i = 0; i < DIMX; ++i)
    for (j = 0; j < DIMY; ++j)
      if (buf[i + j * DIMX] == color)
	{
	  ++size;
	  xC += i;
	  yC += j;
	}
  i_Free((void*)&buf);
  if (size == 0)
    {
      fprintf( stderr, "Region non trouvée \n");
      return -1;
    }
  xC /= size;
  yC /= size;
  printf("%d\t%ld\t%ld\n", size, xC, yC);
  return 0;
}
