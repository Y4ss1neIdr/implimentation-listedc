#include<stdio.h>
#include<stdlib.h>

typedef struct cellule{
    struct cellule* suiv;
    struct cellule* prec;
    int data;
}cellule;
typedef struct cellule* liste;
struct listeDC{
    liste debut;
    liste fin;
    int taille;
};
typedef struct listeDC listedc;

liste Create(int val){
    liste nv;
    nv=(liste)malloc(sizeof(cellule));
    nv->data=val;
    nv->prec=nv->suiv=NULL;
    return nv;
}

 /* listedc ajout_debut( int x){
  listedc l;
  liste nv=Create(x);
  if(l.taille==0){
        l.debut=nv;
        l.taille++;
        return l;
    }
    nv->suiv=l->debut;
    l.debut->prec=nv;
    l.debut=nv;
    l.taille++;
    return l;
} */
liste ajoutDebut(liste l, int x){
    liste nv=Create(x);
    if(!l)
    return nv;
    nv->suiv=l;
    l->prec=nv;
    return nv;
}


void AddBegin(listedc *l , int x){
    l->debut=ajoutDebut(l->debut,x);
    if(l->taille==0)
    l->fin=l->debut;
    l->taille++;
}


void afficher(listedc l){
    liste p;
    printf("\n==================\n");
    printf("LA LISTE DOUBLE EST : \n");
    for(p=l.debut;p;p=p->suiv)
    printf("%d  ", p->data);
    printf("\n");
    printf("LA TAILLE EST : %d !! \n", l.taille);

}


void afficherinvers(listedc l){
    liste p;
    printf("\n==================\n");
    printf("LA LISTE DOUBLE EST : \n");
    for(p=l.fin;p;p=p->prec)
    printf("%d  ", p->data);
    printf("\n");
    printf("LA TAILLE EST : %d !! \n", l.taille);

}


void AddEnd(listedc *l , int x){
    liste nv= Create(x);
    if(!l->taille)
    l->debut=l->fin=nv;
    else{
        l->fin->suiv=nv;
        nv->prec=l->fin;
        l->fin=nv;
    }
    l->taille++;
}


void suppirmer(listedc *l, int x){
    liste p;
    while(l->debut&&l->debut->data==x){ // on supprime tout les x en debut 
        l->debut=l->debut->suiv;
        l->taille--;
    }
    if(!l->debut){ //la liste ne contnait que des x 
        l->debut=l->fin=NULL;
        return ;
    }
    l->debut->prec=NULL;
    for(p=l->debut;p;p=p->suiv){
        if(p->data==x){
           p->prec->suiv=p->suiv;
           if(p!=l->fin){
            p->suiv->prec=p->prec;
           }
           else{
            l->fin=p->prec; // on maj la fin 
           }
        l->taille--;
        }
    }
}

int taille(liste l){
    if(!l)
    return 0;
    return 1+taille(l->suiv);
}

void addPos(listedc* l, int x, int j){
    liste p,nv=Create(x);
    int i;
    if(l&&l->debut->data==x){
        ajoutDebut(l->debut,x);
    }
    else{
        for(p=l->debut,i=0;p&&i!=(j-1);p=p->suiv,i++);
        if(p){
            nv->suiv=p;
            p->prec->suiv=nv;
            nv->prec=p->prec;
            p->prec=nv;
            l->taille++;
        }
        else{
            printf("LA POSITION QUE VOUS CHERCHEZ N EXISTE PAS!!!!\n");
            AddEnd(l,x);
        }
        
    }
}

void deletePos(listedc* l, int pos){
    liste p=l->debut;
    int i,j;
    if(pos>l->taille||pos<=0){
        printf("\nLA POS N EXISTE PAS !!\n");
        return ;
    }
    if(pos == 1){
        l->debut=l->debut->suiv;
        l->debut->prec=NULL;
        if(l->taille==1){
            l->fin=l->debut;
        }
    }
    else{
        for(p=l->debut,i=1;i!=pos;i++,p=p->suiv);
            p->prec->suiv=p->suiv;
            if(p!=l->fin)
            p->suiv->prec=p->prec; 
            else
            l->fin->suiv=NULL;        
    }
    l->taille--;

}
void supprimerpos(listedc* l, int pos){
    liste  p;
    int i,j ;
    if(pos>l->taille||pos<=0){
        printf("L ELEMNT N EXISTE PAS !!");
        return ;
    }
    if(pos == 1){
        if(l->taille==1){//liste ne contient qu'un seul element
            l->debut=l->debut->suiv;
            l->debut->prec=NULL;
        }
        else{//liste contient au moins deux entier
            l->debut=l->debut->suiv;
            l->debut->prec=NULL;
        }

    }
    else{//pos!=1
        if(pos==l->taille){//remove end
            l->fin=l->fin->prec;
            l->fin->suiv=NULL;
        }
        else{//remove milieu
            for(p=l->debut,i=1;i<pos;i++,p=p->suiv);
            p->prec->suiv=p->suiv;
            p->suiv->prec=p->prec;
        }
    }
    l->taille--;
}

int main(){
    listedc L;
    L.debut=L.fin=NULL;
    L.taille=0;
    AddEnd(&L,1);
    AddBegin(&L,2);
    AddBegin(&L,7);
    AddBegin(&L,3);
    AddEnd(&L,7);
    afficher(L);
    deletePos(&L,3);
    afficher(L);

    return 0;
}