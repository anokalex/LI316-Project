/*
 * Calcul et affichage de maxima locaux dans une image
 */
#include <inrimage/image.h>


/* calcul des max locaux: à vous ! (question 1) */

/*Code fourni*/
void seuilloc( float *out, float *in, int dimx, int dimy, float seuil){
  int x, y;
  int x0,y0,x1,y1;
  for( y=1; y<dimy-1; y++)
    for( x=1; x<dimx-1; x++){
	x0=x-1;
	x1=x+1;
	y0=y-1;
	y1=y+1;
	if (x0<0)
		x0=0;
	if (x1>dimx-1)
		x1=dimx-1;
	if (y0<0)
		y0=0;
	if (y0>dimy-1)
		y1=dimy-1;
      out[x+dimx*y] = (in[x+y*dimx]>seuil)&&
	(in[x+y*dimx] > in[x1+y*dimx]) &&
	(in[x+y*dimx] > in[x0+y*dimx]) &&
	(in[x+y*dimx] > in[x+y1*dimx]) &&
	(in[x+y*dimx] > in[x+y0*dimx]) &&
	(in[x+y*dimx] > in[x1+y0*dimx]) &&
	(in[x+y*dimx] > in[x1+y1*dimx]) &&
	(in[x+y*dimx] > in[x0+y0*dimx]) &&
	(in[x+y*dimx] > in[x0+y1*dimx]);
	}
}
/*Code personnel*/

/*void seuilloc( float *out, float *in, int dimx, int dimy, float seuil) {
	int i,j;
	for (i=1;i<dimx-1;i++){
			for(j=1;j<dimy-1;j++){
				float pivot=in[i*dimy+j];
				if (pivot>seuil&&
				    pivot>in[(i-1)*dimy+(j-1)]&&
				    pivot>in[(i-1)*dimy+j]&&
				    pivot>in[(i-1)*dimy+j+1]&&
				    pivot>in[i*dimy+j-1]&&
				    pivot>in[i*dimy+j+1]&&
			            pivot>in[(i+1)*dimy+j+1]&&
				    pivot>in[(i+1)*dimy+j]&&
				    pivot>in[(i+1)*dimy+j-1])
					out[i*dimy+j]=pivot;
				else
					out[i*dimy+j]=0.0;
			 }
		}
}
*/
int main( int argc, char **argv) {
  struct image *nf;
  Fort_int lfmt[9];
  float *bufI, *bufO; 
  float seuil=1;
  char nom[128];

  inr_init( argc, argv, "", "", "");

  infileopt( nom);
  nf = c_image( nom, "e", "", lfmt);
  bufI = (float*)i_malloc( sizeof(float)*DIMX*DIMY);
  c_lecflt( nf, DIMY, bufI);
  fermnf_( &nf);

  bufO = (float*)i_malloc( sizeof(float)*DIMX*DIMY);

  /* traitement */
  igetopt1( "-n", "%f", &seuil);
  seuilloc( bufO, bufI, DIMX, DIMY, seuil);
 
 /* affichage des coordonnées des max locaux*/
  int i,j;
  int x0=0,y0=0,x1=0,y1=0;
  printf("##!draw(C 254 0 0)");
  for (i=3;i<DIMY-3;i++)
	for(j=3;j<DIMX-3;j++){
		x0=j-2;
		y0=i-2;
		x1=j+2;
		y1=i+2;
		if (x0<0)
		   x0=0;
		if (x1>DIMX-1)
		   x1=DIMX-1;
		if (y0<0)
		   y0=0;
		if (y1>DIMY-1)
		   y1=DIMY-1;	
		if(bufO[(j-1)+(i-1)*DIMX]>seuil) printf("##!draw(L %d %d %d %d, L %d %d %d %d)\n",x0, i,x1,i,j,y0,j,y1);
	}
  /* sauvegarde, pour répondre à la question 1 */
  outfileopt( nom);
  TYPE = PACKEE; BSIZE = -1; EXP=0;
  nf = c_image( nom, "c", "", lfmt);
  c_ecrflt( nf, DIMY, bufO);
  fermnf_( &nf);
 

  i_Free( (void*)&bufI);
  i_Free( (void*)&bufO);
  return 0;
}
