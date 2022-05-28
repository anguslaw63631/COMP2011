
const int MAX_SIZE = 10;
const int MAX_STRING_LENGTH = 20;
enum Role
{
   CANDIDATE,
   VOTER
};

// struct definition of Participant
struct Participant
{
   int id;
   char name[MAX_STRING_LENGTH];
   Role role;     // CANDIDATE or VOTER
   bool hasVoted; // true if voter has voted, false otherwise
   int voteCount; // number of votes received if the participant is a candidate of election, initilized as 0
};

// struct definition of Election
struct Election
{
   Participant participants[MAX_SIZE];
   int numCandidates; //note candidates can also vote
   int numVoters;
   // the candidates will occupy the first numCandidates elements in the participants array,
   // while the other voters will occupy the next numVoters elements in the participants array
};


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
void setup(Election &election, int numCandidates, int numVoters);

/* Print participants
 * Parameter:
 *    - election: the Election struct object
 */
void printParticipants(const Election &election);

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
void voting(Election &election, int voterID);

/* Task 3:
 * Output the number of votes for each candidate
 * and announce the winner by finding who has the maximum number of votes
 * Parameters:
 *    - election: the Election struct object
 * Note: if there is more than 1 candidate has the same number of maximum votes,
 * announce it as a tie election.
 */
void resultTallying(const Election &election);
