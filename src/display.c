#include "data.h"

// Global variables for UI components
Widget inputField, submitButton, resetButton;
Widget wordGrid[MAX_ATTEMPTS][MAX_WORD_LENGTH];
Mot motMystere;
int essais;
char etat[MAX_WORD_LENGTH + 1];
bool conditionAffichage;

void InitDisplay(int argc, char **argv);
void CreateDisplay();
void SubmitCallback(Widget w, void *data);
void ResetCallback(Widget w, void *data);

int main(int argc, char **argv) {
    if (OpenDisplay(argc, argv) == 0) {
        fprintf(stderr, "Can't open display\n");
        return EXIT_FAILURE;
    }

    InitDisplay(argc, argv);
    MainLoop();

    return EXIT_SUCCESS;
}

void InitDisplay(int argc, char **argv) {
    motMystere = initMot();
    essais = 0;
    etat[motMystere.size] = '\0';
    conditionAffichage = false;

    printf("Mot à deviner : %s\n", motMystere.mot); // For debugging purposes

    CreateDisplay();
}

void CreateDisplay() {
    SetBgColor(GetWidgetRoot(), WHITE);
    
    // Create input field
    inputField = MakeStringEntry(NULL, MAX_WORD_LENGTH, NULL, NULL);

    // Create buttons
    submitButton = MakeButton("Submit", SubmitCallback, NULL);
    resetButton = MakeButton("Reset", ResetCallback, NULL);

    // Create grid for displaying the words
    for (int i = 0; i < MAX_ATTEMPTS; i++) {
        for (int j = 0; j < MAX_WORD_LENGTH; j++) {
            wordGrid[i][j] = MakeLabel("");
            SetBgColor(wordGrid[i][j], BLUE);
        }
    }

    // Layout the components
    for (int i = 0; i < MAX_ATTEMPTS; i++) {
        for (int j = 0; j < motMystere.size; j++) {
            AttachWidget(wordGrid[i][j], i, j);
        }
    }
    AttachWidget(inputField, MAX_ATTEMPTS, 0);
    AttachWidget(submitButton, MAX_ATTEMPTS + 1, 0);
    AttachWidget(resetButton, MAX_ATTEMPTS + 1, 1);
}

void SubmitCallback(Widget w, void *data) {
    char motPropose[MAX_WORD_LENGTH + 1];
    GetStringEntry(inputField, motPropose);

    if (motExistant(motPropose) && longueurMot(motPropose, motMystere.mot)) {
        int gagne = verifMot(motPropose, motMystere.mot, etat);
        for (int i = 0; i < motMystere.size; i++) {
            SetLabel(wordGrid[essais][i], &motPropose[i]);
            if (etat[i] == 'x') {
                SetBgColor(wordGrid[essais][i], GREEN);
            } else if (etat[i] == 'o') {
                SetBgColor(wordGrid[essais][i], YELLOW);
            } else {
                SetBgColor(wordGrid[essais][i], RED);
            }
        }
        essais++;
        if (gagne || essais >= MAX_ATTEMPTS) {
            SetLabel(submitButton, "Game Over");
            DisableWidget(submitButton);
        }
    } else {
        printf("Invalid word\n");
    }
}

void ResetCallback(Widget w, void *data) {
    essais = 0;
    motMystere = initMot();
    printf("New word: %s\n", motMystere.mot); // For debugging purposes
    for (int i = 0; i < MAX_ATTEMPTS; i++) {
        for (int j = 0; j < motMystere.size; j++) {
            SetLabel(wordGrid[i][j], "");
            SetBgColor(wordGrid[i][j], BLUE);
        }
    }
    SetLabel(submitButton, "Submit");
    EnableWidget(submitButton);
}
