#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "file_state.h"
#include "file_list.h"
#include "file_node.h"
#include "file_inputoutput.h"

unsigned int nodesExpanded;  
unsigned int nodesGenerated; 
unsigned int solutionLength; 
double runtime;              

SolutionPath* AStar_search(State *, State *);

int main(void) {
    
    printInstructions();     

    State initial;          
    State goalState;         
    
    SolutionPath *aStar;
    
    printf("KONDISI AWAL:\n");
    inputState(&initial);

    printf("\nKONDISI AKHIR / GOAL:\n");
    inputState(&goalState);

    printf("KONDISI AWAL:\n");
    printBoard(initial.board);

    printf("GOAL / KONDISI AKHIR:\n");
    printBoard(goalState.board);

    aStar = AStar_search(&initial, &goalState);
    printf("\n-------------------------- A* ALGORITMA --------------------------\n");
    printSolution(aStar);

    nodesExpanded = 0;
    nodesGenerated = 0;
    solutionLength = 0;
    runtime = 0;
    
    return 0;
}

SolutionPath* AStar_search(State *initial, State *goal) {
    NodeList *queue = NULL;
    NodeList *children = NULL;
    Node *node = NULL;

    clock_t start = clock();

    pushNode(createNode(0, manhattanDist(initial, goal), initial, NULL), &queue);
    Node *root = queue->head->currNode;

    while(queue->nodeCount > 0) {
        node = popNode(&queue);

        if(statesMatch(node->state, goal))
            break;

        children = getChildren(node, goal);
        ++nodesExpanded;

        pushListInOrder(&children, queue);
    }

    runtime = (double)(clock() - start) / CLOCKS_PER_SEC;

    SolutionPath *pathHead = NULL;
    SolutionPath *newPathNode = NULL;

    while(node) {
        newPathNode = malloc(sizeof(SolutionPath));
        newPathNode->action = node->state->action;
        newPathNode->next = pathHead;
        pathHead = newPathNode;

        ++solutionLength;
        node = node->parent;
    }

    --solutionLength; 

    destroyTree(root);

    return pathHead;
}
