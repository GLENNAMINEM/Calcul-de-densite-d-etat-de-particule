#include <stdio.h>
#include <stdlib.h>
#include "list.h"


//Fonction d'initialisation de ListCmd

ListNode *initialisation()
{
    ListNode *list_node = malloc(sizeof(*list_node));
    node *new_node = malloc(sizeof(*new_node));

    if (list_node == NULL)
    {
        exit(EXIT_FAILURE);
    }

    new_node->nextNode = NULL;

    list_node->first_node = new_node;

    return list_node;
}
// Fonction d'Insertion au debut d'un Node

void insertion(ListNode *list_node, int m, int s, int c)

{

    /* Création du nouvel élément */

    node *new_node = malloc(sizeof(*new_node));

    FILE* data;

    //data = fopen("IsingOUTPUTZ.dat","a+");

    if (list_node == NULL)
    {
        exit(EXIT_FAILURE);
    }

    new_node->m = m;
    new_node->s = s;
    new_node->c = c;
    new_node->cmpt=1;

    /* Insertion de l'élément au début de la ListCmd */

    new_node->nextNode = list_node->first_node;

    list_node->first_node = new_node;

    //fprintf(data,"%i\t%i\t%i\t%i\n",new_node->m,new_node->s,new_node->c,new_node->cmpt);

    //fclose(data);

}

void searchListCmdElment(ListNode *list_node,int m, int s, int c){

	int vrai =0,vrai1=0,vrai2=0;
    
    node *actuel_node = malloc(sizeof(*actuel_node));


     actuel_node = list_node->first_node;

    //vrai1 = actuel_node->cmpt;

    //vrai2 = actuel_node->cmpt;

    while(actuel_node != NULL){

        if (actuel_node->m != m && actuel_node->s != s && actuel_node->c != c)
        {
            vrai++;
           
        }

        else {

            //printf("Element Existe !!!\n");
            actuel_node->cmpt++;
            vrai2++;

        }

        actuel_node = actuel_node->nextNode;
    }


  if(vrai && vrai1 >= vrai2)
	insertion(list_node,m,s,c);


}


void afficherListCmd(ListNode *list_node)

{
    if (list_node == NULL)
    {

        exit(EXIT_FAILURE);

    }

    node *actuel = list_node->first_node;


    while (actuel != NULL)
    {
        printf("%d %d %d %d \n ", actuel->m,actuel->s,actuel->c,actuel->cmpt);

        
        actuel = actuel->nextNode;
    }

}

