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
        if(x == x->pai->esquerda){ //se x for filho a esquerda
            w = x->pai->direita;//w passa a ser o irmão de x
            if(w->cor == 0){ //se a cor do irmão de x for vermelha //caso 1
                w->cor = 1; //troca a cor pra preto
                x->pai->cor = 0; //muda a cor do pai para vermelho
                rotacaoEsquerda(T, x->pai);//vai rotacionar o pai a esquerda
                w = x->pai->direita; //define o novo irmão do x
            }
            if(w->esquerda->cor == 1 && w->direita->cor == 1){//se w e os filhos de w forem pretos //caso 2
                w->cor = 0; //w assume cor vermelha
                x = x->pai; //x sobe um nodo
            }
            else if(w->direita->cor == 1){ //se o filho-direita de w for preto e w tambem //caso 3
                w->esquerda->cor = 1; //o filho a esquerda tambem passa a ser preto
                w->cor = 0; //a cor de w passa a ser vermelho
                rotacaoDireita(T, w); //rotaciona o w a direita
                w = x->pai->direita; //w volta a ser o irmão de x
            }
            else{ //w é preto e o filho a direita é vermelho //caso 4
                w->cor = w->pai->cor; //w assume a cor de seu pai
                x->pai->cor = 1; //pai de x passa a ser preto
                w->direita->cor = 1; //direita de w vermelho
                rotacaoEsquerda(T, x->pai);
                x = T->raiz; //atribui a raiz para x para encerrar o loop
            }
        }
        else{
            w = x->pai->esquerda; //w = irmão de x
            if(w->cor == 0){ //se w for vermelho
                w->cor = 1; //w passa a ser preto
                x->pai->cor = 0; //pai de w e x passa a ser vermelho
                rotacaoDireita(T, x->pai); //rotaciona a direita
                w = x->pai->esquerda; //w recebe o novo irmao de x
            }
            if(w->direita->cor == 1 && w->esquerda->cor == 1){ //filhos de w são pretos
                w->cor = 0; //w passa a ser vermelho
                x = x->pai; //x sobe um nodo
            }
            else if(w->esquerda->cor == 1){ //filho a esquerda de w é preto
                w->direita->cor = 1; //filho a direita passa ser preto tmb
                w->cor = 0; //w passa a ser vermelho
                rotacaoEsquerda(T, w);//rotaciona w para esquerda
                w = x->pai->esquerda; //
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
    x->cor = 1; // a raiz sempre precisa ser preta
}

nodo *deletar(arvore *T, int k){
    nodo *z = buscar(T, T->raiz, k);
    nodo *y, *x;

    if(z == T->nil){
        return z; //Retorna T->nil se não encontrar a chave
    }

    if(z->esquerda == T->nil || z->direita == T->nil){
        y = z;
    }
    else{ //se tiver filhos a esquerda e direita a variavel auxiliar y recebe o sucessor de z
        y = arv_sucessor(T, z);
    }

    if(y->esquerda != T->nil){ //se tiver filho a esquerda
        x = y->esquerda; //x passa a ser filho-esquerdo de y
    }
    else{
        x = y->direita; //x passa a ser filho-direita de y
    }

    x->pai = y->pai;

    if(y->pai == T->nil){ //se y era raiz
        T->raiz = x;  //a raiz da arvore passa a ser x
    }
    else if(y == y->pai->esquerda){ //se o y for filho a esquerda
        y->pai->esquerda = x; //esquerda do pai-y recebe x
    }
    else{
        y->pai->direita = x; //direita do pai-y recebe x
    }

    if(y != z){ //se y for diferente do nodo a ser excluido
        z->chave = y->chave; //z recebe os dados de y
    }

    if(y->cor == 1){ // se y for preto precisa consertar a arvore
        consertar_delecao(T, x);
    }

    return y;
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
