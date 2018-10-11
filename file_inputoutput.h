extern unsigned int nodesExpanded; 
extern unsigned int nodesGenerated;
extern unsigned int solutionLength;
extern double runtime;             

void printInstructions(void) {
    printf(
        "------------------------------------------------------------------------\n"
        "Perintah:\n"
        "    Masukan status awal dan status akhir dari 8-puzzle\n"
        "    Bilangan integer 0-8\n"
        "------------------------------------------------------------------------\n"
    );
}

void inputState(State * const state) {
    state->action = NOT_APPLICABLE;
    char row, col;
    int symbol;

    // tanda validasi masukan / entryan
    char isNumUsed[9] = { 0 };

    for(row = 0; row < 3; ++row) {
        for(col = 0; col < 3; ++col) {
            printf("    POSISI[%i][%i]: ", row, col);

            scanf("%i", &symbol);

            // mengecek jika  yang di input adalah karakter kosong dan angaka dari 0 sampai dengan lebih dari 9
            if(symbol >= 0 && symbol < 9) {
                if(!isNumUsed[symbol]) {
                    state->board[row][col] = symbol + '0';
                    isNumUsed[symbol] = 1;
                }
                else {
                    printf("    ERROR: Number %c is already used. Try again with different input.\n", symbol);
                    --col;
                }
            }
            else {
                printf("    ERROR: Invalid input. Enter a number from 0 to 8.\n");
                --col;
            }
        }
    }
    printf("\n");
}

void printBoard(char const board[][3]) {
    char row, col;

    for(row = 0; row < 3; ++row) {
        printf("+---+---+---+\n");
        for(col = 0; col < 3; ++col) {
            printf("| %c ", board[row][col]);
        }
        printf("|\n");
    }
    printf("+---+---+---+\n");
}


void printSolution(struct SolutionPath *path) {
	//check if solution exists
    if(!path) {
        printf("Tidak ada sulusi.\n");
        return;
    }

	//if the initial state is already the goal state
	if(!path->next) {
		printf("Tidak perlu ada pergeseran. Keadaan awal sudah merupakan tujuan akhir.\n");
		return;
	}

    printf("SOLUSI: (Relative untuk ruang karakter)\n");

    char *move[4] = { "NAIK", "TURUN", "KIRI", "KANAN" };
    int counter = 1;

    for(path = path->next; path; path = path->next, ++counter) {
        printf("%i. Geser %s\n", counter, move[path->action]);
    }

    printf(
        "DETAIL:\n"
        " - Panjang Solusi : %i\n"
        " - Nodes expanded  : %i\n"
        " - Nodes generated : %i\n"
        " - Waktu         : %g milliseconds\n"
        " - Penggunaan Memory    : %i bytes\n", 
        solutionLength, nodesExpanded, nodesGenerated, runtime, nodesGenerated * sizeof(Node));
}
