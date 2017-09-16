//Árvore binária de busca - Binary Search Tree
//Daniel Welter da Silva

#include <stdio.h>
#include <stdlib.h>

struct  node{
    int key;
    node *left, *right;
};

node *insert(node *r, int key){
    node *no = (node *)malloc(sizeof(node));

    no->key = key;
    no->left = no->right = NULL;

    if(r==NULL){
        return no;
    }

    node *aux = r;

    while(true){
        if(key < aux->key){
            if(aux->left == NULL){
                aux->left = no;
                return r;
            }
            aux = aux->left;
        }
        else{
            if(aux->right == NULL){
                aux->right = no;
                break;
            }
            aux = aux->right;
        }
    }
    return r;
}

node *search (node *r, int key){
    if(!r || r->key == key){
        return r;
    }
    if(key <= r->key){
        return search(r->left, key);
    }
    return search(r->right, key);
}

void inorder(node *r){
    if(r != NULL){
        inorder(r->left);
        printf("%d\n", r->key);
        inorder(r->right);
    }
}

void preorder(node *r){
    if(r != NULL){
        printf("%d\n", r->key);
        preorder(r->left);
        preorder(r->right);
    }
}

void posorder(node *r){
    if(r != NULL){
        posorder(r->left);
        posorder(r->right);
        printf("%d\n", r->key);
    }
}

node *remove(node* r, int key){
    if (r == NULL){
        return NULL;
    }
    else if(key < r->key){
        r->left = remove(r->left, key);
    }
    else if (key > r->key){
        r->right = remove(r->right, key);
    }
    else{
        if (r->left == NULL && r->right == NULL){
            //Quando a raiz nao tem filhos
            free (r);
            r = NULL;
        }
        else if (r->left == NULL){
            //Quando nao tem filhos a esquerda
            node* auxA = r;
            r = r->right;
            free (auxA);
        }
        else if (r->right == NULL){
            //Quando nao tem filhos a direita
            node* auxB = r;
            r = r->left;
            free (auxB);
        }
        else{ //Quando tem subarvore a esquerda e a direita
            node* auxC = r->left;

            while (auxC->right != NULL){
                //Vai buscar o valor mais a direita da subarvore
                auxC = auxC->right;
            }
            r->key = auxC->key;
            auxC->key = key;
            r->left = remove(r->left,key);
        }
    }
    return r;
}

int main(){
    node *root = NULL;
    int key, menu = 1;

    while(menu != 0){
        printf("\n\tArvore binaria de busca\n");
        printf("1- Inserir nodo\n2- Percurso In order\n3- Percurso Pos order\n");
        printf("4- Percurso Pre order\n5- Deletar nodo\n0- Sair\n");
        scanf("%d", &menu);
        system("cls || clear");
        switch(menu){
            case 1:
                printf("Informe o valor a ser inserido: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("In order:\n");
                inorder(root);
                break;
            case 3:
                printf("Pos order:\n");
                posorder(root);
                break;
            case 4:
                printf("Pre order:\n");
                preorder(root);
                break;
            case 5:
                printf("Informe o nodo a ser deletado: ");
                scanf("%d", &key);
                root = remove(root, key);
                break;
            case 0:
                menu = 0;
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }
    return 0;
}
