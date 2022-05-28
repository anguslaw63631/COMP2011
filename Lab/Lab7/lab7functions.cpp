#include <iostream>
#include <cstring>
#include "lab7.h"
using namespace std;

//names listed in no particular order :)
char names[MAX_SIZE][MAX_STRING_LENGTH] = {"JoeBiden", "QueenElizabethII", "Putin", "Trudeau", "XiJinping", "Macron", "KimJongun", "CarrieLam", "Zelenskyy", "Trump"};

/* Task 1: 
 * Setup the election
 * - initialize all the member variables of the Election object
 * Parameters:
 *    - election: a Election struct object
 * Note:
 *    - id for voter/candidate are assigned as 1, 2, 3, ...in sequence
 *    - name for voter/candidate are copied from names[][] in sequence
 *    - role: CANDIDATE or VOTER (note candidate can also vote)
 *    - hasvoted = false, voteCount = 0
 */
void setup(Election &election, int numCandidates, int numVoters)
{
   election.numCandidates = numCandidates;
   election.numVoters = numVoters;

   for (int i = 0; i < (numCandidates + numVoters); i++)
   {
      strcpy(election.participants[i].name, names[i]);
      election.participants[i].id = i;
      election.participants[i].hasVoted = false;
      election.participants[i].voteCount = 0;
      election.participants[i].role = (i < numCandidates) ? CANDIDATE : VOTER;
   }
}

/* Print participants
 * Parameter:
 *    - election: the Election struct object
 */
void printParticipants(const Election &election)
{

   for (int i = 0; i < election.numCandidates + election.numVoters; i++)
   {
      cout << "ID: " << election.participants[i].id << "\tName:" << election.participants[i].name << "\t";
      if (election.participants[i].role == CANDIDATE)
         cout << "Role: Candidate" << endl;
      else
         cout << "Role: Voter" << endl;
   }
}

/* Task 2:
 * Casting votes to some candidates by a specific voter given the voter id
 * Parameters:
 *    - election: the Election struct object
 *    - voterId: the voter's id
 * Note:
 *    validates the following 
 *    - voter id has to be valid, note candidate can also vote
 *    - candidate id has to be valid
 *    - voter can only vote once
 */
void voting(Election &election, int voterID)
{
   if ((voterID < 0) || (voterID >= election.numCandidates + election.numVoters))
   {
      cout << "Invalid voter ID!" << endl;
      return;
   }
   if (election.participants[voterID].hasVoted)
   {
      cout << "The voter has already voted!" << endl;
      return;
   }

   int candID;

   cout << "Enter the candidate id you want to vote for: ";
   cin >> candID;

   if ((candID < 0) || (candID >= election.numCandidates))
   {
      cout << "Invalid candidate ID!" << endl;
      cout << "No vote is casted." << endl;
      return;
   }
   else
   {
      election.participants[candID].voteCount++;
      cout << "You vote for " << election.participants[candID].id << " " << election.participants[candID].name << endl;
   }

   election.participants[voterID].hasVoted = true;
}

/* Task 3:
 * Output the number of votes for each candidate
 * and announce the winner by finding who has the maximum number of votes
 * Parameters:
 *    - election: the Election struct object
 * Note: if there is more than 1 candidate has the same number of maximum votes,
 * announce it as a tie election.
 */
void resultTallying(const Election &election)
{
   int winner, totalVotes = 0, maxVotes = 0;
   int tie = 0;

   cout << "Vote counting: " << endl;
   for (int i = 0; i < election.numCandidates; i++)
   {
      cout << "ID: " << election.participants[i].id << "\tName: " << election.participants[i].name << "\tVotes: " << election.participants[i].voteCount << endl;
      if (election.participants[i].voteCount > maxVotes)
      {
         winner = election.participants[i].id;
         maxVotes = election.participants[i].voteCount;
      }
      totalVotes += election.participants[i].voteCount;
   }
   cout << "Total votes received in election : " << totalVotes << endl;
   if (totalVotes != 0) // a valid election
   {
      for (int i = 0; i < election.numCandidates; i++)
         if (election.participants[i].voteCount == maxVotes)
            tie++;
      if (tie == 1)
         cout << "The winner is: " << election.participants[winner].name << endl;
      else
         cout << "Tied election. More than 1 candidates have the same number of votes." << endl;
   }
}