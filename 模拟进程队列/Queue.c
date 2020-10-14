#include <stdio.h>
#include <stdlib.h>
#define maxsize 31
#define newnode (node *)malloc(sizeof(node))


typedef struct linknode{
    char data;
    struct linknode *pre;
    struct linknode *post;
} node;


void init_node(node **new_node);
void insert_node(node *head, node *new_node);
void free_node(node **useless_node);
void free_all(node **head);
int get_queue_size(node *head);
void in_queue(node **l);
void out_queue(node **l);
void delete_queue(node *head, char ch);
void print_queue(node *head);
void init_array(char a[]);
int get_length(char a[]);
void clear_space(char a[]);
void clear_repat(char a[]);


int main(){
    node *l;
    while(1){
        char choice;
        printf("Please input your choice:\n\
            1. Input in_queue.\n\
            2. Input out_queue.\n\
            3. Print queue.\n\
            4. Exit program.\n>>>");
        fflush(stdin);
        choice = getchar();
        switch (choice){
        case '1':
            in_queue(&l);
            break;
        case '2':
            out_queue(&l);
            break;
        case '3':
            print_queue(l);
            break;
        case '4':
            free_all(&l);
            return 0;
            break;
        default:
            printf("Input ERROR!\n");
            break;
        }
    }
}


void in_queue(node **l){
    char ch[maxsize];
    init_array(ch);
    printf("Please input in_queue, you can insert %d chars.\n>>>",  maxsize - get_length(ch) -1);
    fflush(stdin);
    gets(ch);
    clear_space(ch);
    clear_repat(ch);
    int num = get_length(ch);
    init_node(l);
    for(int i=0; i<num; i++){
        node *news;
        init_node(&news);
        news->data = ch[i];
        insert_node(*l,news);
        printf("The %c in queue success !\n", ch[i]);
    }
}


void out_queue(node **l){
    char ch[maxsize];
    init_array(ch);
    int queue_size = get_queue_size(*l);
    printf("Please input out_queue, you can delete %d chars.\n>>>", queue_size);
    fflush(stdin);
    gets(ch);
    clear_space(ch);
    clear_repat(ch);
    int num = get_length(ch);
    for(int i=0; i<num; i++)
        delete_queue(*l, ch[i]);
}


void print_queue(node *head){
    int flag = 1;
    node *p = head->post;
    printf("\n");
    while(p!=NULL){
        printf("%c", p->data);
        p = p->post;
        flag = 0;
    }
    if(flag)
        printf("None");
    printf("\n\n");
}


void init_array(char a[]){
    for(int i=0; i<maxsize; i++)
        a[i] = '\0';
}


int get_length(char a[]){
    int length;
    for(length=0; a[length]!='\0'; length++);
    return length;
}


void clear_space(char a[]){
    int i, j;
    for(i=0, j=0; a[i]!='\0'; i++, j++){
        if(a[j]==32)
            j++;
        a[i] = a[j];
    }
    a[i] = '\0';
}


void clear_repat(char a[]){
    int i, j, k;
    for(i=0, k=0; a[i]!='\0'; i++, k++){
        for(j=0; j<i; j++){
            if(a[i] == a[j]){
                i++;
            }
        }
        a[k] = a[i];
    }
    a[k] = '\0';
}


void init_node(node **new_node){
    (*new_node) = newnode;
    (*new_node)->data = '\0';
    (*new_node)->pre = NULL;
    (*new_node)->post = NULL;
}


void free_node(node **useless_node){
    (*useless_node)->data='\0';
    (*useless_node)->pre = NULL;
    (*useless_node)->post = NULL;
    free(*useless_node);
}


void insert_node(node *head, node *new_node){
    while(head->post!=NULL)
        head = head->post;
    head->post = new_node;
    new_node->pre = head;
}


void delete_queue(node *head, char ch){
    node *slow = head;
    node *fast = head->post;
    while(fast!=NULL && fast->data!=ch){
        slow = slow->post;
        fast = fast->post;
    }
    if(fast == NULL)
        printf("The %c is not exist.\n", ch);
    else{
        node *temp = fast;
        slow->post = fast->post;
        fast->pre = slow;
        fast = fast->post;
        free_node(&temp);
        printf("The %c has been deleted.\n", ch);
    }
}


int get_queue_size(node *head){
    int size = 0;
    node *p = head->post;
    while(p!=NULL){
        p = p->post;
        size++;
    }
    return size;
}


void free_all(node **head){
    node *temp;
    node *p = *head;
    while(p!=NULL){
        temp = p;
        p = p->post;
        free_node(&temp);
    }
}


