#define BLANK_CHARACTER '0'

//menyediakan tempat untuk karakter yang kosong
typedef enum Move {
    NAIK,TURUN, KIRI, KANAN, 
    NOT_APPLICABLE         
} Move;

typedef struct State {
    Move action;           
    char board[3][3];      //menyiapkan papan berbentuk array 3 x 3 
} State;


State* createState(State *state, Move move) {
    State *newState = malloc(sizeof(State));
    char i, j;  //akan di masukan dalam array 3 x 3      
    char row, col;    

    for(i = 0; i < 3; ++i) {
        for(j = 0; j < 3; ++j) {
            if(state->board[i][j] == BLANK_CHARACTER) {
                row = i;
                col = j;
            }

            newState->board[i][j] = state->board[i][j];
        }
    }

    if(move == NAIK && row - 1 >= 0) {
        char temp = newState->board[row - 1][col];
        newState->board[row - 1][col] = BLANK_CHARACTER;
        newState->board[row][col] = temp;
        newState->action = NAIK;
        return newState;
    }
    else if(move == TURUN  && row + 1 < 3) {
        char temp = newState->board[row + 1][col];
        newState->board[row + 1][col] = BLANK_CHARACTER;
        newState->board[row][col] = temp;
        newState->action = TURUN;
        return newState;
    }
    else if(move == KIRI  && col - 1 >= 0) {
        char temp = newState->board[row][col - 1];
        newState->board[row][col - 1] = BLANK_CHARACTER;
        newState->board[row][col] = temp;
        newState->action = KIRI;
        return newState;
    }
    else if(move == KANAN && col + 1 < 3) {
        char temp = newState->board[row][col + 1];
        newState->board[row][col + 1] = BLANK_CHARACTER;
        newState->board[row][col] = temp;
        newState->action = KANAN;
        return newState;
    }

    free(newState);
    return NULL;
}

void destroyState(State **state) {
    free(*state);
    state = NULL;
}

int manhattanDist(State * const curr, State * const goal) {
    int x0, y0; 
    int x1, y1; 
    int dx, dy; 
    int sum = 0;

    for(y0 = 0; y0 < 3; ++y0) {
        for(x0 = 0; x0 < 3; ++x0) {
            for(y1 = 0; y1 < 3; ++y1) {
                for(x1 = 0; x1 < 3; ++x1) {
                    if(curr->board[y0][x0] == goal->board[y1][x1]) {
                        dx = (x0 - x1 < 0)? x1 - x0 : x0 - x1;
                        dy = (y0 - y1 < 0)? y1 - y0 : y0 - y1;
                        sum += dx + dy;
                    }
                }
            }
        }
    }

    return sum;
}

char statesMatch(State const *testState, State const *goalState) {
    char row = 3, col;

    while(row--) {
        col = 3;
        while(col--) {
            if(testState->board[row][col] != goalState->board[row][col])
                return 0;
        }
    }

    return 1;
}
