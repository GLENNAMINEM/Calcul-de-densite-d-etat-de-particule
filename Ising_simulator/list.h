
typedef struct node node;
struct node 
{
    int m;
    int s;
    int c;
    int cmpt;
    node *nextNode;

};

//La structure de contrôle

typedef struct ListNode ListNode;

struct ListNode

{
    node *first_node;
};


ListNode *initialisation();
void insertion(ListNode *list_node, int m, int s, int c);
void searchListCmdElment(ListNode *list_node,int m, int s, int c);
void afficherListCmd(ListNode *list_node);
