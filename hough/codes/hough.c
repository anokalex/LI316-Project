#include <inrimage/image.h>
#include <math.h>
#include <stdlib.h>




typedef struct{
	float x,y;
	float val;
	}point;




point* creer_point(float x,float y,float val){
	point* a=malloc(sizeof(point));
	a->x=x;
	a->y=y;
	a->val=val;
	return a;
	}

void liberer_point(point* a){
	free(a);
	}

/* retourne 1 si (ix,iy) appartient a la droite
 * d'equation x*cos(theta) + y*sin(theta) = rho
 */

int pixelinline( int ix, int iy, float theta, float rho, float tolerance) {
  if ((abs(ix*cos(theta)+iy*sin(theta)-rho))<tolerance)
	return 1;
  else
	return 0;
}

/**
 * Transformee de Hough (pour les droites): la fonction calcule le nombre
 * d'intersections entre l'image et la droite d'equation
 *      x.cos(theta) + y.sin(theta) = rho
 * avec x=0...dimx-1 et y=0...dimy-1
 *      et theta=-PI/2..PI et rho=0...rhomax
 *      rhomax est la longueur de la diagonale de l'image
 *
 * @param buf, dimx, dimy: tampon d'entree et sa taille. Les valeurs au
 *        dessus d'un seuil sont considerees comme des points de contour
 * @param dtheta, drho : pas de variation de theta et rho
 * @param tolerance tolerance pour le test d'appartenance a la droite
 * @param ntheta,nrho: nombre de colonnes et de lignes pour le tampon
 *         d'accumulation retournee par la fonction.
 *         nrho depend de la taille de l'image et du pas drho, ntheta
 *         ne depend que du pas dtheta.
 * @return le tampon de l'accumulateur de hough, alloue par la fonction.
 */

int *hough( int *ntheta, int *nrho,
	    float dtheta, float drho,
	    float tolerance,
	    unsigned char *bufin, int dimx, int dimy) {
  	*ntheta=((1.5*M_PI)*(1/dtheta));
	float rmax=sqrt(dimx*dimx+dimy*dimy);
	*nrho=(rmax*(1/drho));
	int* hou=(int*)malloc(sizeof(int)*(*ntheta)*(*nrho));
	int a,b;
	for (a=0;a<*ntheta;a++)
		for(b=0;b<*nrho;b++)
			hou[a+b*(*ntheta)]=0;
	int x,y,t,r;
	float theta=0.0,rho=0.0;
	for (x=0;x<dimx;x++)
		for(y=0;y<dimy;y++)
			for(t=0;t<*ntheta;t++)
				for(r=0;r<*nrho;r++){
					theta=(-M_PI/2 + t*(dtheta));
					rho=r*(drho);
					if ((bufin[x+dimx*y]!=0)&&(pixelinline(x,y,theta,rho,tolerance)!=0))
						hou[t+r*(*ntheta)]++;
					}


	return hou;
}

int arrondi(float a){
	return a+0.5;
}

void houghlines(float theta, float r, int dimx, int dimy){

int nb=0;
float x,y;
int x1=0,y1=0,x2=0,y2=0;
if (nb<2){
	x=1.0;
	y=(r-cos(theta))/sin(theta);
	if (y>=1&&y<=dimy){
		if (nb==0){
		x1=1;
		y1=arrondi(y);
		}
		else{
		x2=1;
		y2=arrondi(y);
		}
		nb++;
		}
	}

if (nb<2){
	y=1.0;
	x=(r-sin(theta))/cos(theta);
	if (x>=1&&x<=dimx){
		if (nb==0){
		x1=arrondi(x);
		y1=1;
			}
		else{
			x2=arrondi(x);
			y2=1;
		}
		nb++;
		}
	}

if (nb<2){
	x=dimx;
	y=(r-dimx*cos(theta))/sin(theta);
	if (y>=1&&y<=dimy){
		if (nb==0){
			x1=dimx;
			y1=arrondi(y);
			}
		else{
			x2=dimx;
			y2=arrondi(y);
		}
		nb++;
		}
	}
if (nb<2){
	y=dimy;
	x=(r-dimy*sin(theta))/cos(theta);
	if (x>=1&&x<=dimx){
		if (nb==0){
			x1=arrondi(x);
			y1=dimy;
			}
		else{
			x2=arrondi(x);
			y2=dimy;
			}
		nb++;
		}
	}
if (nb==2){
	printf("##!draw(p %d %d)\n",x1,y1);
	printf("##!draw(l %d %d)\n",x2,y2);



}



}

int cmp(const void* a, const void* b){
	point* pa=(point*)a; point* pb=(point*)b;
	return pb->val-pa->val;
}


/**
 * Cherche les n maxima locaux dans l'accumulateur et pour chacun
 * affiche les intersections de la droite qu'ils représentent avec
 * les bords de l'image.
 */
void findmax( int *acc, int sizex, int sizey, float dr, float dt,
	      int n, int dimx, int dimy) {
	 int x, y;
	  int x0,y0,x1,y1;
	point* out=(point*)calloc(sizex*sizey,sizeof(point));
  	for( x=1; x<sizex-1; x++)
   		 for( y=1; y<sizey-1; y++){
			x0=x-1;
			x1=x+1;
			y0=y-1;
			y1=y+1;

		      		if ((acc[x+y*sizex] >= acc[x1+y*sizex]) &&
					(acc[x+y*sizex] >= acc[x0+y*sizex]) &&
					(acc[x+y*sizex] >= acc[x+y1*sizex]) &&
					(acc[x+y*sizex] >= acc[x+y0*sizex]) &&
					(acc[x+y*sizex] >= acc[x1+y0*sizex]) &&
					(acc[x+y*sizex] >= acc[x1+y1*sizex]) &&
					(acc[x+y*sizex] >= acc[x0+y0*sizex]) &&
					(acc[x+y*sizex] >= acc[x0+y1*sizex])){
					out[x+y*sizex].x=x;
					out[x+y*sizex].y=y;
					out[x+y*sizex].val =acc[x+y*sizex];
				}


			}
	qsort(out,sizex*sizey,sizeof(point),cmp);
	int i;
	printf("##!draw(C 139 190 110)\n");
	for (i=0;i<n;i++)
		houghlines((out[i].x)*dt -M_PI/2.0, (out[i].y)*dr, dimx,dimy);

	free(out);

}
int main( int argc, char **argv) {
  Fort_int lfmt[9];
  struct image *nf;
  char nom[256];
  unsigned char *buf;
  int *acc;
  float tolerance = 0.05;
  int n=20;
  float dtheta=0.01, drho=1;
  int dimtheta, dimrho;

  inr_init( argc, argv, "1.0", "[input][output] options",
	    "Compute the Hough transform. Options are\n"
	    "  -t %f: tolerance\n"
	    "  -st %f: increment size for angle\n"
	    "  -sr %f: increment size for distance\n"
        "  -n %d: number of local maxima\n");

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
   igetopt1( "-st", "%f", &dtheta);
   igetopt1( "-sr", "%f", &drho);
   igetopt1( "-n", "%d",&n);
  /* calcul de l'accumulateur de Hough */
  acc = hough( &dimtheta, &dimrho, dtheta, drho, tolerance, buf, DIMX,DIMY);

findmax( acc, dimtheta, dimrho, drho, dtheta,n, DIMX, DIMY);
  /* écriture de l'accumulateur (pour répondre à la question 3) */
  outfileopt( nom);
  NDIMX = DIMX = dimtheta;/* à compléter, question 3 */
  NDIMY = DIMY = dimrho;/* à compléter, question 3 */
  NDIMZ = NDIMV = 1;
  /* codage sur 4 octets en virgule fixe */
  BSIZE=sizeof(int);TYPE=FIXE;EXP=0;
  nf = image_( nom, "c", "", lfmt);
  c_ecr( nf, DIMY, acc);
  fermnf_(&nf);








  i_Free( (void*)&buf);
  return 0;
}
