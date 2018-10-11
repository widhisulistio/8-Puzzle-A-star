typedef struct Node Node;
typedef struct NodeList NodeList;

typedef struct ListNode {
    Node *currNode;
    struct ListNode *prevNode; 
    struct ListNode *nextNode; 
} ListNode;


struct NodeList {
    unsigned int nodeCount;    
    ListNode *head;            
    ListNode *tail;           
};

typedef struct SolutionPath {
    Move action;
    struct SolutionPath *next;
} SolutionPath;

void destroySolution(SolutionPath **list) {
    SolutionPath *next;
    while(*list) {
        next = (*list)->next;
        free(*list);
        *list = next;
    }
    *list = NULL;
}


char pushNode(Node *node, NodeList** const list) {
    if(!node)
        return 0;

    ListNode *doublyNode = malloc(sizeof(ListNode));
    if(!doublyNode)
        return 0;

    doublyNode->currNode = node;

    if(*list && !(*list)->nodeCount) {
        (*list)->head = doublyNode;
        (*list)->tail = doublyNode;
        doublyNode->nextNode = NULL;
        doublyNode->prevNode = NULL;
        ++(*list)->nodeCount;
        return 1;
    }

    if(*list == NULL) {
        *list = malloc(sizeof(NodeList));
        if(*list == NULL)
            return 0;

        (*list)->nodeCount = 0;
        (*list)->head = NULL;
        (*list)->tail = doublyNode;
    }
    else {
        (*list)->head->prevNode = doublyNode;
    }

    doublyNode->nextNode = (*list)->head;
    doublyNode->prevNode = NULL;
    (*list)->head = doublyNode;

    ++(*list)->nodeCount;

    return 1;
}


Node* popNode(NodeList** const list) {
    if(!*list || (*list)->nodeCount == 0)
        return NULL;

    Node *popped = (*list)->tail->currNode;
    ListNode *prevNode = (*list)->tail->prevNode;

    
    free((*list)->tail);

    if((*list)->nodeCount == 1) {
        (*list)->head = NULL;
    }
	else {
		prevNode->nextNode = NULL;
	}

    (*list)->tail = prevNode;
    --(*list)->nodeCount;
    return popped;
}

void pushList(NodeList **toAppend, NodeList *list) {
    
    if(!*toAppend || !list || !(*toAppend)->head || (*toAppend)->head == list->head) {
        return;
    }

    if(!list->nodeCount) {
        list->head = (*toAppend)->head;
        list->tail = (*toAppend)->tail;
    }
    else {
        (*toAppend)->tail->nextNode = list->head;
        list->head->prevNode = (*toAppend)->tail;
		list->head = (*toAppend)->head;
    }

    list->nodeCount += (*toAppend)->nodeCount;

    free(*toAppend);
    *toAppend = NULL;
}

int totalCost(Node *); 

void pushListInOrder(NodeList **toAppend, NodeList *list) {
   
    if(!*toAppend || !list || !(*toAppend)->head || (*toAppend)->head == list->head) {
        return;
    }

    if(!list->nodeCount) {
        pushNode(popNode(toAppend), &list);
    }

    ListNode *toAppendNode; 
    ListNode *listNode;     
    Node *node;

     while((toAppendNode = (*toAppend)->head)) {
        listNode = list->head;

        while(listNode && totalCost(toAppendNode->currNode) < totalCost(listNode->currNode)) {
            listNode = listNode->nextNode;
        }

        ListNode *temp = toAppendNode->nextNode;

        if(!listNode) {
            list->tail->nextNode = toAppendNode;
            toAppendNode->prevNode = list->tail;
            toAppendNode->nextNode = NULL;
            list->tail = toAppendNode;
        }
        else {
            
            if(listNode->prevNode) {
                toAppendNode->prevNode = listNode->prevNode;
                toAppendNode->nextNode = listNode;
                listNode->prevNode->nextNode = toAppendNode;
                listNode->prevNode = toAppendNode;
            }
            else {
                toAppendNode->nextNode = list->head;
                toAppendNode->prevNode = NULL;
                list->head->prevNode = toAppendNode;
                list->head = toAppendNode;
            }
        }

        (*toAppend)->head = temp;
        --(*toAppend)->nodeCount;
        ++list->nodeCount;
    }

    free(*toAppend);
    *toAppend = NULL;
}
