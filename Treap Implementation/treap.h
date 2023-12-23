#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<time.h>
using std::cout;
using std::endl;
using std::ostream;
class Treap{
public:
    int key;
    int prio;
    Treap* left;
    Treap* right;

    Treap(){
    this->key = 0 ;
    this-> prio = 0;
    this->left = NULL;
    this->right = NULL;
    }

    Treap(int key,int prio, Treap* left,Treap* right){
        this->key = key;
        this->prio = prio;
        this->left = left;
        this->right = right;
    }
    bool operator ==(const Treap& obj){
    if(this->key = key && this->prio == prio && this->left == left && this->right == right) return 1;
    return 0;
    }
    friend ostream& operator<<(ostream& out,const Treap &obj){
        Treap gol;
        if(gol == obj){out<<NULL; return out;}
        out<<endl<<'('<<obj.key<<','<<obj.prio<<')'<<endl;
        out<<"CopSt:"<<obj.left<<endl;
        out<<"CopDr:"<<obj.right<<endl;
        out<<"Adresa:"<<&obj<<endl;
        return out;
    }
};

Treap* TreapNou(int key,int prio){
    Treap* nou = new Treap(key,prio,NULL,NULL);
    return nou;
}


Treap* cautare(Treap* &rad , int key){
    if(rad == NULL) return NULL;
    if(rad->key == key) return rad;
    if(rad->key < key) cautare(rad->right ,key);
    else cautare(rad->left ,key);
}

Treap* rotDr(Treap* &rad){
    Treap* aux = rad->left;
    Treap* aux2 = aux->right;
    aux->right =  rad;
    rad->left = aux2;
    return aux;
}
Treap* rotSt(Treap* &rad){
    Treap* aux = rad->right;
    Treap* aux2 = aux->left;
    aux->left = rad;
    rad->right = aux2;
    return aux;
}

void afisare(Treap* rad){
    if(rad != NULL){
        cout<<*rad<<endl;
        afisare(rad->left);
        afisare(rad->right);
    }
}

void inorder(Treap* rad)
{
    if (rad == NULL)
        return;

    inorder(rad->left);
    cout <<'('<< rad->key<<','<<rad->prio<<')' << " ";
    inorder(rad->right);
}
Treap* inserare(Treap* rad,int key){
    if(rad == NULL){
        rad = TreapNou(key,rand()%100000000);
        return rad;
    }
    if(key <= rad->key){
        rad->left = inserare(rad->left,key);
        if(rad->left->prio > rad->prio)
            rad = rotDr(rad);
    }
    else{
        rad->right = inserare(rad->right,key);
        if(rad->right->prio > rad->prio)
            rad = rotSt(rad);
    }
    return rad;
}
Treap* inserare(Treap* rad,int key,int prio){
    if(rad == NULL){
        rad = TreapNou(key,prio);
        return rad;
    }
    if(key <= rad->key){
        rad->left = inserare(rad->left,key,prio);
        if(rad->left->prio > rad->prio)
            rad = rotDr(rad);
    }
    else{
        rad->right = inserare(rad->right,key,prio);
        if(rad->right->prio > rad->prio)
            rad = rotSt(rad);
    }
    return rad;
}
Treap* build(int v[], int n){
    if (n == 0)
        return NULL;
    Treap* rad = NULL;

    for (int i = 0; i < n; i++)
        rad = inserare(rad, v[i],rand()%100000000);

    return rad;
}
Treap* minim(Treap* &rad){
    if(rad->left != NULL)
        return minim(rad->left);
    else
        return rad;
}
Treap* maxim(Treap* &rad){
    if(rad->right != NULL)
        return maxim(rad->right);
    else
        return rad;
}

Treap* stergere(Treap* &rad,int key){
    if(rad == NULL) return NULL;    //arborele e gol

    if(key < rad->key)                 //caut keya
        rad->left = stergere(rad->left , key);
    else if(key > rad->key)
        rad->right = stergere(rad->right , key);

    else if(key == rad->key){            //am gasit keya
        if(rad->left ==NULL){           //n are copil in stanga,il ridic pe ala din dreapta
            Treap* aux = rad->right;
            delete rad;
            rad = aux;
        }
        else if(rad->right == NULL){    //n are copil in dreapta,il ridic pe ala din stanga
            Treap* aux = rad->left;
            delete rad;
            rad = aux;
        }
    else if(rad->left->prio < rad->right->prio){
        rad = rotSt(rad);
        rad->left = stergere(rad->left,key);
        }
    else if(rad->right->prio <= rad->left->prio){
        rad = rotDr(rad);
        rad->right = stergere(rad->right , key);
        }
    }
    return rad;
}
void dezalocare(Treap* &rad){
    if(rad != NULL){
        if(rad->left != NULL)
            dezalocare(rad->left);
        if(rad->right != NULL)
            dezalocare(rad->right);
    delete rad;
    rad = NULL;
    }
}

void afisareSplit(Treap* &rad,int key){
    rad = inserare(rad,key,INFINITY);
    cout<<"LEFT SUBTREAP\n";
    inorder(rad->left);
    cout<<"\nRIGHT SUBTREAP\n";
    inorder(rad->right);
    rad = stergere(rad,key);
}
Treap* copiere(Treap* &rad,Treap* &aux){
    if (rad == NULL)
        return NULL;
    copiere(rad->left,aux);
    aux = inserare(aux,rad->key,rad->prio);
    copiere(rad->right,aux);

    return aux;
}
void split(Treap* &rad,Treap* &st , Treap* &dr,int key){
    Treap *subSt=NULL,*subDr=NULL;
    rad = inserare(rad , key , INFINITY);
    subSt = copiere(rad->left,subSt);
    subDr = copiere(rad->right,subDr);
    rad = stergere(rad , key);
    st = subSt;
    dr = subDr;
}

Treap* join(Treap* &st,Treap* &dr){
    if(maxim(st)->key < minim(dr)->key){
        int key = (maxim(st)->key + minim(dr)->key)/2;
        Treap *aux = new Treap(key,INFINITY,st,dr);
        aux = stergere(aux,key);
        return aux;
    }
    return NULL;
}

Treap* reuniune(Treap* &st , Treap* &dr){
    if (dr != NULL){
        if(dr->left !=NULL)
            st = reuniune(st,dr->left);
        if(dr->right !=NULL)
            st = reuniune(st,dr->right);
        st = inserare(st,dr->key,dr->prio);
    }
    return st;
}

int maximN(Treap* &rad, int key){
    if(rad == NULL) return -1;
    if(rad->key == key) return key;
    else if(rad->key < key){
        int k =maximN(rad->right , key);
        if(k == -1)
            return rad->key;
        else
            return k;
        }
    else if(rad->key > key){
        return maximN(rad->left,key);
    }
    return -1;
}

int minimN(Treap* &rad,int key){
    if(rad == NULL) return -1;
    if(rad->key == key) return key;
    else if(rad->key > key){
        int k = minimN(rad->left , key);
        if( k == -1)
            return rad-> key;
        else
            return k;
        }
    else if(rad->key < key){
        return minimN(rad->right,key);
    }
    return -1;
}

void interval(Treap* &rad,int key1 ,int key2){
    if (rad == NULL)
        return;
    interval(rad->left,key1,key2);
    if(rad->key >= key1 && rad->key <= key2) cout<<rad->key<<' ';
    interval(rad->right,key1,key2);
}