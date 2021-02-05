#include <stdio.h>
#include <assert.h>
#include <gmp.h>
#include <stdlib.h>
#include <string.h>


void puissance(int v){
	v =v*2 ;

}

void square_multiply(mpz_t a,mpz_t h, mpz_t n, mpz_t r ){ // r = a^h mod n
	
	//mpz_set_str(h, "h", 10); // pour dire que le nombre h est en base 10
	
    char * res = mpz_get_str(NULL,2,h); // convertir le nombre h qui est en base 10 en base 2
    int i = 1  ;
    mpz_set(r,a); // r= a 
    int taille = strlen(res);
    while (i<taille )
    {                        
		mpz_mul(r,r,r);// r = r*r
		mpz_mod(r,r,n); // r=r[n]:
		if(res[i] == '1')
		{
			mpz_mul(r,r,a);// r = r*a;
			mpz_mod(r,r,n);// r = r[n] ;
		}
		i++ ;
	}
	
}

int decompose(mpz_t t, mpz_t d, int s){

  mpz_set(d,t);
  int trouve = 0;

	while(trouve==0){
    if(mpz_even_p(d)!=0){ // si  d est  impair 
      mpz_divexact_ui(d,d,2);// d =d /2 ;
      puissance(s); // s =s*2 ;
    }else{
      trouve=1;
    }
  }
  return 0;
}


void millerrabin(mpz_t n, int k){
	 
	if(mpz_get_ui(n) % 2 == 0)   //Si N pair alors renvoyer composé sauf si N=2
	{
		if(mpz_cmp_ui(n,2) == 0)
			printf("Le nombre est premier \n");
        else
            printf("Le nombre est composé car il est pair \n");
			return ;
	}
	
  // déclaration de toutes les variables gmp utilisés
  mpz_t d; mpz_init(d);
  mpz_t y; mpz_init(y);
  mpz_t a; mpz_init(a);
  mpz_t t; mpz_init(t);
  mpz_t deux; mpz_init(deux);
  mpz_t p; mpz_init(p);
  
  // initialisations 
  mpz_set_ui(deux,2); // deux = 2 
  mpz_sub_ui(p,n,1); // P = n-1
  
 
  int i,j,s;
  
 
  gmp_randstate_t state;
  gmp_randinit_mt(state);

  for(i=0;i<k;i++){
    s=1;
    mpz_urandomm(a,state,p); // un nombre aléatoire entre 1 et n-1 inclus 
    mpz_add_ui(a,a,1);

    mpz_sub_ui(t,n,1); // t = n-1
    decompose(t,d,s); // n-1= 2^s * d
    square_multiply(a,d,n,y); // y = a^d[n]
      
      
      if(mpz_cmp_ui(y,1)!=0 && mpz_cmp(y,t)!=0){ // si y != 1 et y!=-1 ( n-1[n]= -1[n])
        printf("D'après le test de Miller_Rabin votre nombre est composé \n");
        return ;
      }

      for(j=0;j<s;j++){
		 square_multiply(y,deux,n,y);// y = y^2 [n]
        if(mpz_cmp_ui(y,1)!=0){
          printf("D'après le test de Miller_Rabin votre nombre est  composé \n");
          return ;
        }
      }
  }

  printf("D'après le test de Miller_rabin votre nombre est premier\n");
  // libération de nos variables gmp 
  mpz_clear(y);
  mpz_clear(a);
  mpz_clear(d);
  mpz_clear(t);
  mpz_clear(p);
  gmp_randclear(state);
}



int main(){
  
	int t=0;
	mpz_t n;
	mpz_init(n);
	int rep ;
	printf("Test de Miller_Rabbin\n");
    while(t==0)
    {
        printf("\n");
        printf("Choisir votre entier à tester : ");
        gmp_scanf("%Zd", &n);
        if(mpz_cmp_ui(n,1)<=0)
        {	
			printf("\n Veuillez choisir un entier supérieur à 1 !");
		}
		else
		{
			printf("Choisir le nombre de répétitions souhaité : ");
			gmp_scanf("%d", &rep);
			printf("\n********************************************************\n");
			millerrabin(n,rep);
			printf("********************************************************\n");
			printf("\n");
			printf("Si vous voulez tester un autre nombre taper 0 :");
			scanf("%d",&t);
		}	
	}

	mpz_clear(n);	
	
	return 0;

}
