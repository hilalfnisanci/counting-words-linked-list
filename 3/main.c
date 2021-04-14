#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define DOSYA_YOLU "Deneme.txt"

typedef struct _node
{
    int adet;
    char *str;
    struct _node * next;
} node;

node *ilk = NULL, *son=NULL;

void basaEkle(char *kelime, int adet)
{
    node *yeni = (node *)malloc(sizeof(node));
    yeni->str = (char*)malloc(20*sizeof(char));
    strcpy(yeni->str,kelime);
    yeni->adet = adet;

    if(ilk==NULL)
    {
        ilk = yeni;
        ilk->next = NULL;
        son=ilk;
    }
    else{
        yeni->next = ilk;
        ilk=yeni;
    }
}

void sonaEkle(char *kelime, int adet)
{
    node *yeni = (node *)malloc(sizeof(node));
    yeni->str = (char*)malloc(20*sizeof(char));
    strcpy(yeni->str,kelime);
    yeni->adet = adet;

    if(ilk==NULL)
    {
        ilk=yeni;
        son=yeni;
        son->next = NULL;
    }
    else{
        son->next = yeni;
        son = yeni;
        son->next = NULL;
    }
}

void arayaEkle(node* onceki, char *kelime,int adet)
{
    if(onceki == NULL)
    {
        printf("Verilen dugum NULL olamaz\n");
        return;
    }
    node *new_node = (node *)malloc(sizeof(node));
    new_node->str = (char*)malloc(20*sizeof(char));
    strcpy(new_node->str,kelime);
    new_node->adet = adet;
    new_node->next = onceki->next;
    onceki->next = new_node;
}

int adetBul(char *kelime)
{
    FILE *dosya = fopen(DOSYA_YOLU,"r");
    char *okunan;
    okunan = (char*)malloc(20*sizeof(char));

    int adet=0;
    while(!feof(dosya))
    {
        fscanf(dosya,"%s",okunan);
        if(strcmp(okunan,kelime)==0)
            adet++;
    }
    return adet;
}

int kontrol(char *kelime)
{
    node *current = ilk;

    while(current!=NULL)
    {
        if(strcmp(kelime,current->str)==0){
            return 0;
        }
        current=current->next;
    }
    return 1;
}

void yazdir()
{
    node* head = (node *)malloc(sizeof(node));
    head = ilk;
    printf("-----LISTE-----\n");
    int i=1;
    while(head != NULL)
    {
        if(head->adet ==0)
            break;
        printf("%d. %s:%d\n",i,head->str,head->adet);
        head = head->next;
        i++;
    }
}

void ekle(int adet, char *kelime)
{

    node *current = ilk;

    while(current!=NULL)
    {
        if(current==ilk && (current->adet) < adet)
        {
            basaEkle(kelime,adet);
            return;
        }
        if(current == son && (current->adet)>=adet)
        {
            sonaEkle(kelime,adet);
            return;
        }
        if((current->adet) >= adet && (current->next->adet)< adet)
        {
            arayaEkle(current,kelime,adet);
            return;
        }
        current=current->next;
    }
}



int main()
{

    int adet = 0;

    FILE *dosya;

    if((dosya = fopen(DOSYA_YOLU,"r")) != NULL)
    {
        char *ptr;
        ptr = (char*)malloc(20*sizeof(char));

        while(!feof(dosya))
        {
            fscanf(dosya,"%s",ptr);

            if(ilk == NULL) // eger liste bossa ilk dugumu ekler
            {
                adet = adetBul(ptr);
                basaEkle(ptr,adet);
                continue;
            }

            if(kontrol(ptr)==1) //kelime listeye onceden eklenmemisse listeye ekler
            {
                adet = 0;
                adet = adetBul(ptr);
                ekle(adet,ptr);
            }
        }

    }
    else
    {
        printf("Dosya acilamadi\n");
        return -1;
    }


    fclose(dosya);
    yazdir();

    return 0;
}
