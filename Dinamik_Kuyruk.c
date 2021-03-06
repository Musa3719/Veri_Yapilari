#include <stdio.h>
#include <stdlib.h>
struct kuyruktut{//kuyruga erisim
    struct kuyruk *bas;
    struct kuyruk *son;
};
//----------------------------------------------------------------------------------------//
struct kuyruk{
    int veri;
    struct kuyruk *link;
};
//----------------------------------------------------------------------------------------//
struct kuyruktut* kuyrukyarat(int sayi){
    struct kuyruktut *yenikuyruktut;
    struct kuyruk *yenikuyruk;
    yenikuyruktut=(struct kuyruktut*)malloc(sizeof(struct kuyruktut));
    yenikuyruk=(struct kuyruk*)malloc(sizeof(struct kuyruk));
    yenikuyruk->link==NULL;
    yenikuyruk->veri=sayi;
    yenikuyruktut->bas=yenikuyruk;
    yenikuyruktut->son=yenikuyruk;
    return yenikuyruktut;
}
//----------------------------------------------------------------------------------------//
void kuyrukelemanekle(struct kuyruktut *kuyruktutfonk, int sayi){
    if(kuyruktutfonk==NULL){
        printf("Kuyruk bulunamadi...");
        return;
    }
    struct kuyruk *yeni;
    yeni=(struct kuyruk*)malloc(sizeof(struct kuyruk));
    kuyruktutfonk->son->link=yeni;
    yeni->veri=sayi;
    kuyruktutfonk->son=yeni;
    yeni->link=NULL;
}
//----------------------------------------------------------------------------------------//
void kuyrukyaz(struct kuyruktut *kuyruktutfonk){
    struct kuyruk *gecici=kuyruktutfonk->bas;
    while(gecici!=NULL){
        printf("%d ",gecici->veri);
        gecici=gecici->link;
    }
    printf("\n");
}
//----------------------------------------------------------------------------------------//
void kuyrukkopar(struct kuyruktut *kuyruktutfonk){
    struct kuyruk *silinecek;
    silinecek=kuyruktutfonk->bas;
    kuyruktutfonk->bas=kuyruktutfonk->bas->link;
    printf("%d silindi\n",silinecek->veri);
    free(silinecek);
}
//----------------------------------------------------------------------------------------//
int main()
{
    struct kuyruktut *kuyruk1;
    kuyruk1=kuyrukyarat(5);
    kuyrukelemanekle(kuyruk1,10);
    kuyrukelemanekle(kuyruk1,15);
    kuyrukelemanekle(kuyruk1,20);
    kuyrukyaz(kuyruk1);
    kuyrukkopar(kuyruk1);
    kuyrukkopar(kuyruk1);
    kuyrukyaz(kuyruk1);
    return 0;
}
