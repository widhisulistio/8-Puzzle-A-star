extern unsigned int nodesGenerated; 

/**
 * DESKRIPSI: Mendefinisikan struktur simpul yang digunakan untuk membuat pohon pencarian
**/
typedef struct Node Node;
struct Node {
    unsigned int depth; //kedalaman node dari root. Untuk pencarian A *
    unsigned int hCost; //biaya heuristik dari node
    State *state;       
    Node *parent;      
    NodeList *children; 
};

/**
 * Deskripsi:
 *    Fungsi ini menciptakan node
 * PARAMETERS:
 *    d - kedalaman node
 *    h - nilai heuristic pada node
 *    s - keadaan yang ditetapkan ke node
 *    p - parent node
**/
Node* createNode(unsigned int d, unsigned int h, State *s, Node *p) {
    Node *newNode = malloc(sizeof(Node));
    if(newNode) {
        newNode->depth = d;
        newNode->hCost = h;
        newNode->state = s;
        newNode->parent = p;
        newNode->children = NULL;
        ++nodesGenerated; 
    }
    return newNode;
}

/**
 * Deskripsi:
 * Fungsi ini digunakan untuk membatalkan semua node dalam sebuah pohon, termasuk node root.
 * PARAMETER:
 *   node - simpul akar dari pohon untuk deallocate
**/
void destroyTree(Node *node) {
    if(node->children == NULL) {
        free(node->state);
        free(node);
        return;
    }

    ListNode *listNode = node->children->head;
    ListNode *nextNode;

    while(listNode) {
        nextNode = listNode->nextNode;
        destroyTree(listNode->currNode);
        listNode = nextNode;
    }

    free(node->children);
    free(node);
}


NodeList* getChildren(Node *parent, State *goalState) {
    NodeList *childrenPtr = NULL;
    State *testState = NULL;
    Node *child = NULL;

    if(parent->state->action != TURUN && (testState = createState(parent->state, NAIK))) {
        child = createNode(parent->depth + 1, manhattanDist(testState, goalState), testState, parent);
        pushNode(child, &parent->children);
        pushNode(child, &childrenPtr);
    }
    if(parent->state->action != NAIK && (testState = createState(parent->state, TURUN))) {
        child = createNode(parent->depth + 1, manhattanDist(testState, goalState), testState, parent);
        pushNode(child, &parent->children);
        pushNode(child, &childrenPtr);
    }
    if(parent->state->action != KANAN && (testState = createState(parent->state, KIRI))) {
        child = createNode(parent->depth + 1, manhattanDist(testState, goalState), testState, parent);
        pushNode(child, &parent->children);
        pushNode(child, &childrenPtr);
    }
    if(parent->state->action != KIRI && (testState = createState(parent->state, KANAN))) {
        child = createNode(parent->depth + 1, manhattanDist(testState, goalState), testState, parent);
        pushNode(child, &parent->children);
        pushNode(child, &childrenPtr);
    }

    return childrenPtr;
}


int totalCost(Node * const node) {
    return node->depth + node->hCost;
}
