#include <inrimage/image.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
	float x,y;
	float val;
	float r;
	}point;




point* creer_point(float x,float y,float r,float val){
	point* a=malloc(sizeof(point));
	a->x=x;
	a->y=y;
	a->r=r;
	a->val=val;
	return a;
	}

void liberer_point(point* a){
	free(a);
	}

/* retourne 1 si (ix,iy) appartient au cercle
 * d'equation (x-xc)*(x-xc)+(y-yc)*(y-yc) = rho*rho
 */

int pixelincircle( int ix, int iy, int xc, int yc,float r, float tolerance) {
  if ((abs((ix-xc)*(ix-xc)+(iy-yc)*(iy-yc)-r*r)<tolerance))
	return 1;
  else
	return 0;
}

int arrondi(float a){
	return a+0.5;
}
/**
 * Transformee de Hough (pour les cercles): la fonction calcule le nombre
 * d'intersections entre l'image et le cercle de centre (xc,yc) d'equation
 * (x-xc)*(x-xc)+(y-yc)*(y-yc)=rho*rho
 * avec x=0...dimx-1 et y=0...dimy-1
 *
 *
 *
 * @param bufin, dimx, dimy: tampon d'entree et sa taille. Les valeurs au
 *        dessus d'un seuil sont considerees comme des points de contour
 * @param d
 * @param tolerance tolerance pour le test d'appartenance au cercle
 * @param nxc,nyc,nr: dimensions du tampon
 *         d'accumulation retournee par la fonction.
 *         nr depend de la taille de l'image et du pas dr, nxc
 *          dépend  de dimx et du pas dxc, nyc dépend de dimy et du pas nyc.
 * @return le tampon de l'accumulateur de hough, alloue par la fonction.
 */

int *hough_c( int *nxc, int *nyc, int *nr,
	    float dxc, float dyc,float dr,
	    float tolerance,
	    unsigned char *bufin, int dimx, int dimy) {
	float rmax=sqrt(dimx*dimx+dimy*dimy);
  	 *nxc=arrondi(dimx/dxc);
        *nyc=arrondi(dimy/dyc);
        *nr=arrondi(rmax/dr);
	int* hou=(int*)malloc(sizeof(int)*(*nxc)*(*nyc)*(*nr));
	int a,b,c;
	for (a=0;a<*nxc;a++)
		for(b=0;b<*nyc;b++)
			for (c=0;c<*nr;c++)
				hou[a+b*(*nxc)+c*(*nxc)*(*nyc)]=0;
	int x,y,t,u,v;
	int xcercle=0,ycercle=0;
	float rayon=0.0;

			for(t=0;t<*nxc;t++)
				for(u=0;u<*nyc;u++)
					for (v=0;v<*nr;v++)
						for (x=0;x<dimx;x++)
							for(y=0;y<dimy;y++){
								xcercle=t*dxc;
								ycercle=u*dyc;
								rayon=v*dr;
								if ((bufin[x+dimx*y]!=0)&&(pixelincircle(x,y,xcercle,ycercle,rayon,tolerance)==1)){
									hou[t+u*(*nxc)+v*(*nxc)*(*nyc)]++;
							}
					}


	return hou;
}




int cmp(const void* a, const void* b){
	point* pa=(point*)a; point* pb=(point*)b;
	return pb->val-pa->val;
}


/**
 * Cherche les n maxima locaux dans l'accumulateur et pour chacun
 * affiche les intersections du cercle qu'ils représentent avec
 * les bords de l'image.
 */
void findmax( int *acc, int sizex, int sizey,int sizez,float dxc, float dyc, float dr,
	      int n, int dimx, int dimy) {
	 int x, y,z;
	  int x0,y0,x1,y1,z0,z1;
	point* out=(point*)calloc(sizex*sizey*sizez,sizeof(point));
  	for( x=1; x<sizex-1; x++)
   		 for( y=1; y<sizey-1; y++)
			for (z=1;z<sizez-1;z++){
				x0=x-1;
				x1=x+1;
				y0=y-1;
				y1=y+1;
				z0=z-1;
				z1=z+1;
				if ((acc[x+y*sizex+z*sizex*sizey] >= acc[x1+y1*sizex+z1*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x1+y1*sizex+z*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x1+y1*sizex+z0*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x1+y*sizex+z1*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x1+y*sizex+z*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x1+y*sizex+z0*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x1+y0*sizex+z1*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x1+y0*sizex+z*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x1+y0*sizex+z0*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x+y1*sizex+z1*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x+y1*sizex+z*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x+y1*sizex+z0*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x+y*sizex+z1*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x+y*sizex+z0*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x+y0*sizex+z1*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x+y0*sizex+z*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x+y0*sizex+z0*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x0+y1*sizex+z1*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x0+y1*sizex+z*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x0+y1*sizex+z0*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x0+y*sizex+z1*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x0+y*sizex+z*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x0+y*sizex+z0*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x0+y0*sizex+z1*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x0+y0*sizex+z*sizex*sizey]) &&
					(acc[x+y*sizex+z*sizex*sizey] >= acc[x0+y0*sizex+z0*sizex*sizey])){
						out[x+y*sizex+z*sizex*sizey].x=x;
						out[x+y*sizex+z*sizex*sizey].y=y;
						out[x+y*sizex+z*sizex*sizey].r=z;
						out[x+y*sizex+z*sizex*sizey].val =acc[x+y*sizex+z*sizex*sizey];
				}


			}
	qsort(out,sizex*sizey*sizez,sizeof(point),cmp);
	int i;
	int ix,iy,iz;
	printf("##!draw(C 254 0 0)\n");
	for (i=0;i<n;i++){
		ix=(out[i].x)*dxc;
		iy=(out[i].y)*dyc;
		iz=(out[i].r)*dr;
		printf("##!draw(a %d %d %d)\n",((int)(ix-iz+1)),((int)(iy-iz+1)),(int)(iz*2));
	}

	free(out);

}
int main( int argc, char **argv) {
  Fort_int lfmt[9];
  struct image *nf;
  char nom[256];
  unsigned char *buf;
  int *acc=NULL;
  float tolerance = 0.05;
  float dxc=1, dyc=1, dr=0.5;
  int dimx, dimy,dimr;

  inr_init( argc, argv, "1.0", "[input][output] options",
	    "Compute the Hough transform. Options are\n"
	    "  -t %f: tolerance\n"
	    "  -sx %f: increment size for x\n"
	    "  -sy %f: increment size for y\n"
	    "  -sr %f: increment size for r\n");


  infileopt(nom);

  /* lecture image: c'est une image de contours codée sur 1 octet */
  nf = image_(nom,"e","",lfmt);
  if( BSIZE != 1 || TYPE != FIXE)
    imerror( 6, "Codage non accepté\n");
  buf= (unsigned char*)i_malloc(DIMX*DIMY*sizeof(unsigned char));
  c_lect(nf, NDIMY, buf);
  fermnf_(&nf);


  /* à compléter: lecture des paramètres de l'algo, question 3 */
   igetopt1( "-t", "%f", &tolerance);
   igetopt1( "-sx", "%f", &dxc);
   igetopt1( "-sy", "%f", &dyc);
   igetopt1( "-sr", "%f", &dr);

  /* calcul de l'accumulateur de Hough */
  acc = hough_c( &dimx, &dimy, &dimr,dxc,dyc,dr,tolerance, buf, DIMX,DIMY);

findmax( acc, dimx, dimy, dimr, dxc,dyc,dr,3, DIMX, DIMY);
  /* écriture de l'accumulateur (pour répondre à la question 3) */
  outfileopt( nom);
  NDIMX = DIMX = dimx;/* à compléter, question 3 */
  NDIMY = DIMY = dimy*dimr;/* à compléter, question 3 */
  NDIMZ = NDIMV = 1;
  /* codage sur 4 octets en virgule fixe */
  BSIZE=sizeof(int);TYPE=FIXE;EXP=0;
  nf = image_( nom, "c", "", lfmt);
  c_ecr( nf, DIMY, acc);
  fermnf_(&nf);
  free(acc);

  i_Free( (void*)&buf);
  return 0;
}
