/*
 * Detecteur Harris, fichier à compléter
 * gcc harris.c -o harris -linrimage -lm
 */

#include <inrimage/image.h>
#include <math.h>

/*
 * Convolution 2D. 
 * Important: les bords de l'image ne sont pas traités!
 */
void convol( float *out, float *in, int dimx, int dimy,
	     float *noy, int n, int m) {
  int i,j,x,y;
  double s;
  int n2 = n/2, m2 = m/2;

    for( y=0; y<dimy; y++)
    	for( x=0; x<dimx; x++) {
    		s = 0.;
   		for( j=-m2; j<=m2; j++)
		for( i=-n2; i<=n2; i++)
		
	  	if( x>=i && y>=j && x-i<dimx && y-j<dimy)
	    		s += in[(x-i)+dimx*(y-j)] * noy[i+n2+(j+m2)*n];
      		*out++ = s;
    		}
}

void derivex(float* Ix,float* in,int dimX,int dimY){
	float noy[9]={-1,0,1,-2,0,2,-1,0,1};	
	convol(Ix,in,dimX,dimY,noy,3,3);
	}

void derivey(float* Iy,float* in,int dimX,int dimY){
	float noy[9]={-1,-2,-1,0,0,0,1,2,1};	
	convol(Iy,in,dimX,dimY,noy,3,3);
	}

void gaussian(float sigma, float* G, int n){
	int i,j;
	for (i=0;i<n;i++)
		for (j=0;j<n;j++)
			G[i+n*j]=(1.0/(2*M_PI*sigma*sigma))*exp(-((i-n/2)*(i-n/2)+(j-n/2)*(j-n/2))/(2*sigma*sigma));
}

void harris(float* out, float* in, int dimX, int dimY, float kappa, float sigma){
	float* Ix = (float*)i_malloc( sizeof(float)*dimX*dimY);
	float* Iy = (float*)i_malloc( sizeof(float)*dimX*dimY);
	float* A11 = (float*)i_malloc( sizeof(float)*dimX*dimY);
	float* A22 = (float*)i_malloc( sizeof(float)*dimX*dimY);
	float* A12 = (float*)i_malloc( sizeof(float)*dimX*dimY);
	int n=2*ceil(3*sigma)+1;
	derivex(Ix,in,dimX,dimY);
	derivey(Iy,in,dimX,dimY);
	int i=0,j=0;
	for (i=0;i<dimX;i++){
		for (j=0;j<dimY;j++){
			A11[i+dimX*j]=Ix[i+dimX*j]*Ix[i+dimX*j];
			A22[i+dimX*j]=Iy[i+dimX*j]*Iy[i+dimX*j];
			A12[i+dimX*j]=Ix[i+dimX*j]*Iy[i+dimX*j];
	}
	}
	float* noyau = (float*)i_malloc( sizeof(float)*n*n);
	gaussian(sigma,noyau,n);
	convol(A11,A11,dimX,dimY,noyau,n,n);
	convol(A22,A22,dimX,dimY,noyau,n,n);
	convol(A12,A12,dimX,dimY,noyau,n,n);

	int u,v;
	for (u=0;u<dimX;u++)
		for(v=0;v<dimY;v++)
			out[u+dimX*v]=A11[u+dimX*v]*A22[u+dimX*v]-A12[u+dimX*v]*A12[u+dimX*v]-kappa*(A11[u+dimX*v]+A22[u+dimX*v])*(A11[u+dimX*v]+A22[u+dimX*v]);


	i_Free( (void*)&Ix);
 	i_Free( (void*)&Iy);
 	i_Free( (void*)&A11);
 	i_Free( (void*)&A22);
 	i_Free( (void*)&A12);
	i_Free( (void*)&noyau);
}






int main( int argc, char **argv) {
  struct image *nf;
  Fort_int lfmt[9];
  float *bufI, *bufH, *bufH2; 
  float kappa = 0.02, sigma = 1;//defaut 1
  char nom[128];

  inr_init( argc, argv, "", "", "");

  infileopt( nom);
  /* lecture en mode flottant => fonctionne avec tout type d'image */
  nf = c_image( nom, "e", "", lfmt);
  bufI = (float*)i_malloc( sizeof(float)*DIMX*DIMY);
  c_lecflt( nf, DIMY, bufI);
  fermnf_( &nf);

  /* paramètres utiles au futur filtre Harris */
  igetopt1( "-K", "%f", &kappa);
  igetopt1( "-s", "%f", &sigma);
  bufH = (float*)i_malloc( sizeof(float)*DIMX*DIMY);

  /* traitement */
  harris(bufH,bufI,DIMX,DIMY,kappa,sigma);
  /* sauvegarde, au format virgule flottante */
  outfileopt( nom);
  TYPE =  REELLE; BSIZE = sizeof(float);
  nf = c_image( nom, "c", "", lfmt);
  c_ecr( nf, DIMY, bufH);
  fermnf_( &nf);
  i_Free( (void*)&bufI);
  i_Free( (void*)&bufH);
}

