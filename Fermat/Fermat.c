#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

void square_multiply(mpz_t a,mpz_t h,mpz_t n, mpz_t r)// r = a^h mod n
{
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

void testFermat(mpz_t n, mpz_t k)

{
	if(mpz_get_ui(n) % 2 == 0)   
	{
		if(mpz_cmp_ui(n,2) == 0) // //Si N pair alors renvoyer composé sauf si N=2
			printf("Le nombre est premier \n");
        else
            printf("Le nombre est composé  car il est pair \n");
        return;
	}
	

		
	 
	// déclaration de toutes les variables gmp 
	mpz_t i;
	mpz_t a;
	mpz_t m;
	mpz_t r;
	mpz_t d ;
	// initialisation de toutes les variables gmp 
	mpz_init(i);
	mpz_init(a);
	mpz_init(m);
	mpz_init(r);
	mpz_init(d);
	
	
    mpz_set_si(i,1); // on initialise i a 1 // i=1
	mpz_sub_ui(m,n,1);
	mpz_sub_ui(d,n,2);

	gmp_randstate_t state; 	
	gmp_randinit_mt(state);
	//for (int i =1 ; i<= k ; i++ )
	while(mpz_cmp(i,k)<=0 )
	{
		mpz_urandomm(a,state,d);// un nombre aléatoire entre 2 et n-1 
		mpz_add_ui(a,a,2); 
	    square_multiply(a,m,n,r);// 
	    if(mpz_cmp_si(r,1)!=0)
		{
			printf("D'après le test de Fermat le nombre est composé\n");
			return ;
		}
		mpz_add_ui(i,i,1); // i = i+1 ;
	
   }	
		printf("D'après le test de Fermat Le nombre est premier \n");
		mpz_clear(i);
		mpz_clear(m);
		mpz_clear(a);mpz_clear(r);
		gmp_randclear(state);
		
}



int main()
{
	int y = 0;
	mpz_t n;
	mpz_init(n);
	mpz_t k;
	mpz_init(k);
	printf("Tests de primalité de Fermat  \n");
    while(y==0)
    {
        printf("\n");
        printf("Choisir votre entier à tester : ");
        gmp_scanf("%Zd", &n);
        printf("\n");
        if(mpz_cmp_ui(n,1)<=0)
        {	
			printf("\n Veuillez choisir un entier supérieur à 1 !");
		}
		else
		{
			printf("Choisir le nombre de répétitions k souhaité : ");
			gmp_scanf("%Zd", &k);
			printf("\n****************************************************\n");
			testFermat(n,k);
			printf("****************************************************\n");
			printf("\n");
			printf("Si vous voulez tester un autre nombre taper 0 :  ");
			scanf("%d",&y);
		}	
	}
	mpz_clear(n);	
	mpz_clear(k);
	return 0;
}
	



    
