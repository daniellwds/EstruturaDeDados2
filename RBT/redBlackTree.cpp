//Arvore Rubro-Negra
//Daniel Welter da Silva

#include <stdio.h>
#include <stdlib.h>

struct nodo{
    int chave;
    int cor; //0 = Vermelho, 1 = Preto
    nodo *esquerda, *direita, *pai;
};

struct arvore{
    nodo *raiz, *nil;
};

arvore *iniciarArvore(){
    arvore *n = (arvore *)malloc(sizeof(arvore));
    n->nil = (nodo *)malloc(sizeof(nodo));

    n->nil->cor = 1;
    n->nil->pai = NULL;
    n->nil->esquerda = NULL;
    n->nil->direita = NULL;
    n->raiz = n->nil;

    return n;
}

void rotacaoEsquerda(arvore *T, nodo *z){
    nodo *y = z->direita;

    z->direita = y->esquerda;

    if(y->esquerda != T->nil){
        y->esquerda->pai = z;
    }
    y->pai = z->pai;

    if(z->pai == T->nil){
        T->raiz = y;
    }
    else if(z == z->pai->esquerda){
        z->pai->esquerda = y;
    }
    else {
        z->pai->direita = y;
    }

    y->esquerda = z;
    z->pai = y;
}

void rotacaoDireita(arvore *T, nodo *z){
    nodo *y = z->esquerda;

    z->esquerda = y->direita;

    if(y->direita != T->nil){
        y->direita->pai = z;
    }
    y->pai = z->pai;

    if(z->pai == T->nil){
        T->raiz = y;
    }
    else if(z == z->pai->esquerda){
        z->pai->esquerda = y;
    }else{
        z->pai->direita = y;
    }
    y->direita = z;
    z->pai = y;
}

void consertar_insercao(arvore *T, nodo *z){
    nodo *y;

    while(z->pai->cor == 0){
        if(z->pai == z->pai->pai->esquerda){
            y = z->pai->pai->direita;
            if(y->cor == 0){
                z->pai->cor = 1;
                y->cor = 1;
                z->pai->pai->cor = 0;
                z = z->pai->pai;
            }
            else{
                if(z == z->pai->direita){
                    z = z->pai;
                    rotacaoEsquerda(T, z);
                    z->pai->cor = 1;
                    z->pai->pai->cor = 0;
                    rotacaoDireita(T, z->pai->pai);
                }
                else{
                    z = z->pai;
                    rotacaoDireita(T, z);
                }
            }
        }
        else{
            y = z->pai->pai->esquerda;
            if(y->cor == 0){
                z->pai->cor = 1;
                y->cor = 1;
                z->pai->pai->cor = 0;
                z = z->pai->pai;
            }
            else{
                if(z == z->pai->esquerda){
                    z = z->pai;
                    rotacaoDireita(T, z);
                    z->pai->cor = 1;
                    z->pai->pai->cor = 0;
                    rotacaoEsquerda(T, z->pai->pai);
                }
                else{
                    z = z->pai;
                    rotacaoEsquerda(T, z);
                }
            }
        }
    }
    T->raiz->cor = 1;
}

void inserir(arvore *T, int k){
    nodo *aux = (nodo *)malloc(sizeof(nodo));
    aux->pai = aux->esquerda = aux->direita = T->nil;
    aux->chave = k;
    aux->cor = 0;

    nodo *y, *x;

    y = T->nil;
    x = T->raiz;

    while(x != T->nil){
        y = x;
        if(k < x->chave){
            x = x->esquerda;
        }
        else{
            x = x->direita;
        }
    }

    aux->pai = y;

    if(y == T->nil){
        T->raiz = aux;
    }
    else if(k < y->chave){
        y->esquerda = aux;
    }
    else{
        y->direita = aux;
    }

    consertar_insercao(T, aux);

}

nodo *buscar(arvore *T, nodo *r, int k){
    if(r == T->nil || r->chave == k){
        return r;
    }
    if(k <= r->chave){
        return buscar(T, r->esquerda, k);
    }

    return buscar(T, r->direita, k);
}

nodo *menorNodo(arvore *T, nodo *no){
    nodo *aux = no;
    while(aux->esquerda != T->nil){
        aux = aux->esquerda;
    }
    return aux;
}

nodo *arv_sucessor(arvore *T, nodo *no){
    if(no->direita != T->nil){
        return menorNodo(T, no->direita);
    }
    nodo *pai = no->pai;
    while(pai != T->nil && no == pai->direita){
        no = pai;
        pai = pai->pai;
    }
    return pai;
}

void inorder(nodo *r, nodo *nil){
    if(r != nil){
        inorder(r->esquerda, nil);
        printf("%d", r->chave);
        if(r->cor == 0){
            printf(" Vermelho\n");
        }else{
            printf(" Preto\n");
        }
        inorder(r->direita, nil);
    }
}

void preorder(nodo *r, nodo *nil){
    if(r != nil){
        printf("%d", r->chave);
        if(r->cor == 0){
            printf(" Vermelho\n");
        }else{
            printf(" Preto\n");
        }
        preorder(r->esquerda, nil);
        preorder(r->direita, nil);
    }
}

void posorder(nodo *r, nodo *nil){
    if(r != nil){
        posorder(r->esquerda, nil);
        posorder(r->direita, nil);
        printf("%d", r->chave);
        if(r->cor == 0){
            printf(" Vermelho\n");
        }else{
            printf(" Preto\n");
        }
    }
}

void consertar_delecao(arvore *T, nodo *x){
    nodo *w;

    while(x != T->raiz && x->cor == 1){
        if(x == x->pai->esquerda){
            w = x->pai->direita;
            if(w->cor == 0){
                w->cor = 1;
                x->pai->cor = 0;
                rotacaoEsquerda(T, x->pai);
                w = x->pai->direita;
            }
            if(w->esquerda->cor == 1 && w->direita->cor == 1){
                w->cor = 0;
                x = x->pai;
            }
            else if(w->direita->cor == 1){
                w->esquerda->cor = 1;
                w->cor = 0;
                rotacaoDireita(T, w);
                w = x->pai->direita;
            }
            else{
                w->cor = w->pai->cor;
                x->pai->cor = 1;
                w->direita->cor = 1;
                rotacaoEsquerda(T, x->pai);
                x = T->raiz;
            }
        }
        else{
            w = x->pai->esquerda;
            if(w->cor == 0){
                w->cor = 1;
                x->pai->cor = 0;
                rotacaoDireita(T, x->pai);
                w = x->pai->esquerda;
            }
            if(w->direita->cor == 1 && w->esquerda->cor == 1){
                w->cor = 0;
                x = x->pai;
            }
            else if(w->esquerda->cor == 1){
                w->direita->cor = 1;
                w->cor = 0;
                rotacaoEsquerda(T, w);
                w = x->pai->esquerda;
            }
            else{
                w->cor = w->pai->cor;
                x->pai->cor = 1;
                w->esquerda->cor = 1;
                rotacaoDireita(T, x->pai);
                x = T->raiz;
            }
        }
    }
    x->cor = 1;
}

nodo *deletar(arvore *T, int k){
    nodo *z = buscar(T, T->raiz, k);
    nodo *y, *x;

    if(z == T->nil){
        return z;
    }

    if(z->esquerda == T->nil || z->direita == T->nil){
        y = z;
    }
    else{
        y = arv_sucessor(T, z);
    }

    if(y->esquerda != T->nil){
        x = y->esquerda;
    }
    else{
        x = y->direita;
    }

    x->pai = y->pai;

    if(y->pai == T->nil){
        T->raiz = x;
    }
    else if(y == y->pai->esquerda){
        y->pai->esquerda = x;
    }
    else{
        y->pai->direita = x;
    }

    if(y != z){
        z->chave = y->chave;
    }

    if(y->cor == 1){
        consertar_delecao(T, x);
    }

    return z;
}

int main(){

    arvore *T = iniciarArvore();
    int menu = 1, entrada;

    while(menu != 0){
        printf("\n\tArvore Rubro-Negra\n");
        printf("1- Inserir chave\n2- Deletar chave\n3- Percurso In order\n");
        printf("4- Percurso Pre order\n5- Percurso Pos order\n0- Sair\n");
        scanf("%d", &menu);
        system("clear || cls");


        switch(menu){
            case 1:
                printf("Informe o valor a ser inserido: ");
                scanf("%d", &entrada);
                inserir(T, entrada);
                break;
            case 2:
                printf("Informe o valor a ser deletado: ");
                scanf("%d", &entrada);
                deletar(T, entrada);
                break;
            case 3:
                printf("\n\tIn Order\n");
                inorder(T->raiz, T->nil);
                printf("\n");
                break;
            case 4:
                printf("\n\tPre Order\n");
                preorder(T->raiz, T->nil);
                printf("\n");
                break;
            case 5:
                printf("\n\tPos Order\n");
                posorder(T->raiz, T->nil);
                printf("\n");
                break;
            case 0:
                break;
            default:
                printf("\nINFORME UMA OPCAO VALIDA!\n");
                break;
        }
    }
}
