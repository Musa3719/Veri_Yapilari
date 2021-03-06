#include <stdio.h>
#include <stdlib.h>
struct agac{
	int veri;
	struct agac *sag;
	struct agac *sol;
	int yukseklik;
};
///--------------Sağ Rotasyon--------------------------------------------------------------///
struct agac* rr(struct agac *root){
	struct agac *child=root->sol;
	root->sol=child->sag;
	child->sag=root;
	root->yukseklik=max(yukseklikbul(root->sag),yukseklikbul(root->sol))+1;//ilk önce her zaman rotation ile aşağı inenin yüksekliği hesaplanır
	child->yukseklik=max(yukseklikbul(child->sag),yukseklikbul(child->sol))+1;
	return child;
}
///--------------Sol Rotasyon--------------------------------------------------------------///
struct agac* lr(struct agac *root){
	struct agac *child=root->sag;
	root->sag=child->sol;
	child->sol=root;
	root->yukseklik=max(yukseklikbul(root->sag),yukseklikbul(root->sol))+1;
	child->yukseklik=max(yukseklikbul(child->sag),yukseklikbul(child->sol))+1;
	return child;
}
///--------------Maximum--------------------------------------------------------------///
int max(int a,int b){
	return (a>b)? a : b;
}
///--------------Yükseklik------------------------------------------------------------///
int yukseklikbul(struct agac *root){
	if(root==NULL) return 0;
	return root->yukseklik;
}
///--------------Denge----------------------------------------------------------------///
int denge(struct agac *root){
	if(root==NULL)	return 0;
	return(yukseklikbul(root->sol) - yukseklikbul(root->sag));
}
///--------------Agac Olustur---------------------------------------------------------///
struct agac* olustur(int sayi){
	struct agac *yeni=(struct agac*)malloc(sizeof(struct agac));
	yeni->sag=NULL;
	yeni->sol=NULL;
	yeni->veri=sayi;
	yeni->yukseklik=1;
	return yeni;
}
///--------------Ekle-----------------------------------------------------------------///
struct agac* ekle(struct agac *root,int sayi){//ekle,yukseklik ayarla,dengeyi bul,rotation bak(4 case)
	//bst recursive eklemesi yapılır
	if(root==NULL)
		return(olustur(sayi));
	if(sayi > root->veri)
		root->sag=ekle(root->sag,sayi);
	else if(sayi < root->veri)
		root->sol=ekle(root->sol,sayi);
	else//aynı sayı girilirse
		return root;
	//yukseklik ayarla
	root->yukseklik=max(yukseklikbul(root->sag),yukseklikbul(root->sol))+1;
	//her bir recursive çağrı için geri dönerken denge sayısı bulunur
	int dengesayi=denge(root);
	//Burda da denge bozulmuş mu bakılır
	if(dengesayi>1 && sayi < root->sol->veri){//sol sol durumu
		return rr(root);
	}
	if(dengesayi<-1 && sayi > root->sag->veri){//sag sag durumu
		return lr(root);
	}
	if(dengesayi>1 && sayi > root->sol->veri){//sol sag durumu
		root->sol=lr(root->sol);
		return rr(root);
	}
	if(dengesayi<-1 && sayi< root->sag->veri){//sag sol durumu
		root->sag=rr(root->sag);
		return lr(root);
	}
	//4 koşula da girilmezse değişmemiş olan root döndürülür. 
	return root;
}
///--------------Yazdır(preorder)------------------------------------------------///
void yaz(struct agac *root){
	if(root==NULL)	return;
	printf("%d:%d ",root->veri,root->yukseklik);
	yaz(root->sol);
	yaz(root->sag);
}
///--------------Sil-------------------------------------------------------------///
struct agac * sil(struct agac *root,int sayi){
	//silme işlemi aynı ağaçlardaki gibi yapılır
	if(root==NULL)
		return root;
	if(sayi > root->veri)
		root->sag=sil(root->sag,sayi);
	else if(sayi < root->veri)
		root->sol=sil(root->sol,sayi);
	else{//bulundu
		if(root->sag==NULL && root->sol==NULL)
			return NULL;
		if(root->sag !=NULL){
			struct agac *gecici=root->sag;
			struct agac *geri=gecici;
			while(gecici->sol!=NULL){
				geri=gecici;
				gecici=gecici->sol;
			}
			root->veri=gecici->veri;
			if(gecici->sag!=NULL){
				if(root==geri)
					geri->sag=gecici->sag;
				else
					geri->sol=gecici->sag;
			}
			gecici->sag=NULL;
			root->sag=sil(root->sag,gecici->veri);
		}
		else{//ikisi de null değil ve sag yoksa son seçenek sol vardır, soldan alınır leaf silinir. Aynısının ters yönlüsü
			struct agac *gecici=root->sol;
			struct agac *geri;
			while(gecici->sag!=NULL){
				geri=gecici;
				gecici=gecici->sag;
			}
			root->veri=gecici->veri;
			if(gecici->sol!=NULL){
				if(root==geri)
					geri->sol=gecici->sol;
				else
					geri->sag=gecici->sol;
			}
			gecici->sol=NULL;
			root->sol=sil(root->sol,gecici->veri);
		}
	}
	//sildikten sonra ise AVL ağacı bozulmuş mu bakılır
	if(root == NULL)//agacın sadece kökü varsa
		return root;
	//yukseklik hesapla
	root->yukseklik=max(yukseklikbul(root->sag),yukseklikbul(root->sol))+1;
	//getbalance
	int dengesayi=denge(root);
	//durumlar
	if(dengesayi>1){
		if(denge(root->sol)>=0)//sol sol durumu
			return rr(root);
		else{
			root->sol=lr(root->sol);//sol sag durumu
			return rr(root);
		}
	}
	else if(dengesayi<-1){
		if(denge(root->sag)<=0)//sag sag durumu
			return lr(root);
		else{
			root->sag=rr(root->sag);//sag sol durumu
			return lr(root);
		}
	}
	//4 duruma da girilmezse o düğüm için sıkıntı yok demektir. root döndürülür
	return root;
}
///--------------main------------------------------------------------------------///
int main(int argc, char *argv[]) {
	struct agac *avl=NULL;
	avl=ekle(avl,40);
	avl=ekle(avl,15);
	avl=ekle(avl,30);
	avl=ekle(avl,50);
	avl=ekle(avl,60);
	yaz(avl);
	avl=sil(avl,50);
	printf("\n");
	yaz(avl);
	system("pause");
	return 0;
}







