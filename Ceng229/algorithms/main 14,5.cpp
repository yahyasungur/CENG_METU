#include<stdio.h>
#include<string.h>
struct ogrenci {
	char isim[20];
	char soyiisim[20];
	int yas;
};
void show(struct ogrenci x){
	printf(" \n%s %s %d",x.isim,x.soyiisim,x.yas);
}
struct ogrenci degerAl() {
	struct ogrenci Y;
	printf(" Please enter the informations of student :");
	scanf("%s %s %d",&Y.isim,&Y.soyiisim,Y.yas);
	return Y;
}

int main (){
	struct ogrenci YAHYA = degerAl();	
	show(YAHYA);
	
	
	getchar ();
	return 0;
}
