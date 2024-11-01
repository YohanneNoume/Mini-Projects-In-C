#ifndef ELECTION_H
#define ELECTION_H

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CANDIDATES 20
#define MAX_VOTERS 200

typedef struct {
    int year;
    char branch[6];
    int totalVoters;
} CurrentValidID;

typedef struct {
    int cid;
    char cname[20];
    int votes;
} Candidate;

// Global variables
extern CurrentValidID currentValidID;
extern Candidate candidateArray[MAX_CANDIDATES];
extern int numberOfCandidates;
extern char studentVotes[MAX_VOTERS];

// Function declarations
void addCandidate(Candidate candidates[], int *candidateCount);
void castVote(Candidate candidates[], int candidateCount);
void displayVotes(Candidate candidates[], int candidateCount);
void declareWinner(Candidate candidates[], int candidateCount);

void studentPanel();
void adminPanel();
int extractYear(char userID[15]);
int extractRollNo(char userID[15]);
int checkBranchCode(char userID[15]);
int isValid(char userID[15]);
int isBanned(char userID[15]);
int isVoted(char userID[15]);
void saveVote(char userID[15], char voteInput);

#endif // ELECTION_H
