#include "election.h"

// Global variables
CurrentValidID currentValidID;
Candidate candidateArray[MAX_CANDIDATES];
int numberOfCandidates = 0;
char studentVotes[MAX_VOTERS];

void addCandidate(Candidate candidates[], int *candidateCount) {
    if (*candidateCount >= MAX_CANDIDATES) {
        printf("Cannot add more candidates. Maximum limit reached.\n");
        return;
    }
    printf("Enter candidate name: ");
    scanf(" %[^\n]", candidates[*candidateCount].cname);
    candidates[*candidateCount].cid = *candidateCount + 1;
    candidates[*candidateCount].votes = 0;
    (*candidateCount)++;
    printf("Candidate added successfully!\n");
}

void castVote(Candidate candidates[], int candidateCount) {
    char name[20];
    printf("Enter candidate name to vote: ");
    scanf(" %[^\n]", name);
    for (int i = 0; i < candidateCount; i++) {
        if (strcmp(candidates[i].cname, name) == 0) {
            candidates[i].votes++;
            printf("Vote casted successfully for %s!\n", name);
            return;
        }
    }
    printf("Candidate not found.\n");
}

void displayVotes(Candidate candidates[], int candidateCount) {
    printf("Current vote counts:\n");
    for (int i = 0; i < candidateCount; i++) {
        printf("Candidate: %s, Votes: %d\n", candidates[i].cname, candidates[i].votes);
    }
}

void declareWinner(Candidate candidates[], int candidateCount) {
    if (candidateCount == 0) {
        printf("No candidates available.\n");
        return;
    }
    Candidate *winner = &candidates[0];
    for (int i = 1; i < candidateCount; i++) {
        if (candidates[i].votes > winner->votes) {
            winner = &candidates[i];
        }
    }
    printf("The winner is %s with %d votes!\n", winner->cname, winner->votes);
}

int extractYear(char userID[15]) {
    int year = 0;
    for (int i = 0; i < 4; i++) {
        year = (year * 10) + (userID[i] - '0');
    }
    return year;
}

int extractRollNo(char userID[15]) {
    int rollno = 0;
    for (int i = 9; i < 14; i++) {
        rollno = (rollno * 10) + (userID[i] - '0');
    }
    return rollno;
}

int checkBranchCode(char userID[15]) {
    char branchCode[6];
    for (int i = 4; i < 9; i++) {
        branchCode[i - 4] = userID[i];
    }
    branchCode[5] = '\0';
    return strcmp(branchCode, currentValidID.branch) == 0;
}

int isValid(char userID[15]) {
    if (extractYear(userID) == currentValidID.year && checkBranchCode(userID) && extractRollNo(userID) <= currentValidID.totalVoters) {
        return 1;
    }
    return 0;
}

int isBanned(char userID[15]) {
    int location = extractRollNo(userID);
    return studentVotes[location - 1] == '!' ? 1 : 0;
}

int isVoted(char userID[15]) {
    int location = extractRollNo(userID);
    return studentVotes[location - 1] == '$' ? 1 : 0;
}

void saveVote(char userID[15], char voteInput) {
    int location = extractRollNo(userID);
    studentVotes[location - 1] = voteInput;
    candidateArray[voteInput - '1'].votes++;
}

void studentPanel() {
    char userID[15];
    char voteInput;
    while (1) {
        printf("\n\n  To exit press 0");
        printf("\n  Enter user ID: ");
        scanf("%s", userID);
        if (strcmp(userID, "0") == 0)
            return;
        if (isValid(userID) != 1) {
            printf("\n  Invalid User ID(Press Enter)");
            getch();
            continue;
        }
        if (isBanned(userID) != 0) {
            printf("\nThis User ID is currently banned...\nContact Admin for the reason...(Press Enter to continue)");
            getch();
            continue;
        }
        if (isVoted(userID) != 0) {
            printf("\n  Your PRN entered is already voted\n  Contact Admin for further query");
            getch();
            continue;
        }
        printf("\n\n  Candidates for election:");
        for (int i = 0; i < numberOfCandidates; i++) {
            printf("\n  %d. %s", i + 1, candidateArray[i].cname);
        }
        printf("\n\n  Your Vote(Enter Number): ");
        voteInput = getch();
        printf("*");
        if (voteInput - '0' < 1 || voteInput - '0' > numberOfCandidates) {
            printf("\nInvalid Vote\nTry Again...");
            getch();
            continue;
        }
        saveVote(userID, voteInput);
        printf("\n\nThanks for your precious vote(Press Enter)");
        getch();
    }
}

void adminPanel() {
    int choice;
    while (1) {
        printf("\n\nAdmin Panel");
        printf("\n1. Add Candidate");
        printf("\n2. Display Votes");
        printf("\n3. Declare Winner");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCandidate(candidateArray, &numberOfCandidates);
                break;
            case 2:
                displayVotes(candidateArray, numberOfCandidates);
                break;
            case 3:
                declareWinner(candidateArray, numberOfCandidates);
                break;
            case 4:
                return;
            default:
                printf("\nInvalid choice. Please try again.");
        }
    }
}
