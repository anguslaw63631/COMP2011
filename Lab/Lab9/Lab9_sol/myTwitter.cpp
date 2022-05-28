#include "myTwitter.h"

/*
    In this Lab, we will design a simple Twitter.
    1. Maintain several users.
    2. Each user has ID and a Tweet list, which is defined in myTwitter.h.
    3. Each user can follow other users.

    Main functions in myTwitter:
    1. Post a tweet (Insert a node in link list) - Task 2
    2. Delete a tweet (Delete a node in link list) - Task 3
    3. Get the latest news from followings - Task 4
*/

/* ----------------------------------------- */
/* ----------------Functions---------------- */
/* ----------------------------------------- */

/* Global varaibles */
int current_time = 1;
int max_recent_num = 5;
User UsrList[MAX_USER];

/* Initialize each User */
void init_user() {
    for (int i=0; i<MAX_USER; i++) {
        UsrList[i].self_id = i;
        UsrList[i].p_my_tweets_head = NULL;
        UsrList[i].followings_size = 0;
        for (int j=0; j<MAX_FOLLOWEE; j++)
            UsrList[i].followings[j] = NULL;
    }
}

/* 
    Task 1: Determines if the specified user has sent a tweet
    Link List: isEmpty
    Input:
        user_id: int, must smaller than MAX_USER. Used to get the User in UsrList
    Return:
        True: empty
        False: not empty
*/
bool isEmpty(int user_id) {
    if (user_id > MAX_USER)
        throw invalid_argument( "User ID is out of scope!" );
    /*******************************************
                 Your code begin at here
    *******************************************/
    if (UsrList[user_id].p_my_tweets_head == NULL)
        return true;
    else 
        return false;
    /*******************************************
                 Your code end at here
    *******************************************/
}

/* 
    Task 2: Post a tweet given a user 
    Link List : Insert 
    Input:
        user_id: int, must smaller than MAX_USER. Used to get the User in UsrList
    Return:
        None
*/
void postTweet(int user_id) {
    if (user_id > MAX_USER)
        throw invalid_argument( "User ID is out of scope!" );
    /* Initialize new Tweet */
    Tweet *p_NewTweet = new Tweet();
    p_NewTweet->timestamp = current_time;
    p_NewTweet->tweet_id = MAX_TWEETS*user_id + current_time;
    p_NewTweet->p_next_tweet = NULL;

    /*******************************************
                 Your code begin at here
    *******************************************/
    if (isEmpty(user_id)) {
        UsrList[user_id].p_my_tweets_head = p_NewTweet;     // if empty, initialize head node
    }
    else {
        p_NewTweet->p_next_tweet = UsrList[user_id].p_my_tweets_head;   // insert
        UsrList[user_id].p_my_tweets_head = p_NewTweet;
    }
    /*******************************************
                 Your code end at here
    *******************************************/
    current_time++;     // Time incremented by 1 for each tweet added
}

/* 
    Task 3: 
    Retrieve the 5 most recent tweets in the user's news feed. 
    Each item in the news feed must be posted by users who the user followed or by the user herself. 
    Tweets must be ordered from most recent to least recent.

    Link List : Search & Compare
    Input:
        user_id: int, must smaller than MAX_USER. Used to get the User in UsrList
    Return:
        None
*/
void printNewsFeed(int user_id) {
    if (user_id > MAX_USER)
        throw invalid_argument( "User ID is out of scope!" );
    cout << "Current time is: " << current_time << endl;
    cout << "You should display recent " << max_recent_num << " tweets" << endl;

    /*******************************************
                 Your code begin at here
    *******************************************/
    User self = UsrList[user_id];
    int following_size = self.followings_size;
    Tweet *p_heads[MAX_FOLLOWEE+1];           // array of head pointers 
    p_heads[0] = self.p_my_tweets_head;         // add self head node

    /* Init p_heads */
    for (int i=1; i<following_size+1; i++) 
        p_heads[i] = self.followings[i-1]->p_my_tweets_head;

    /* Start seaching most recent news */
    int news_feed_num = 0;
    while (news_feed_num < max_recent_num) {
        /* Init most_recent_idx */
        int most_recent_idx = 0;
        /* Search most recent news */
        for (int i=1; i<following_size+1; i++) {
            if (p_heads[i] == NULL)             
                continue;
            if (p_heads[most_recent_idx] == NULL) {
                most_recent_idx = i;
                continue;
            }
            if (p_heads[i]->timestamp > p_heads[most_recent_idx]->timestamp)
                most_recent_idx = i;
        }
        if (p_heads[most_recent_idx] == NULL)
            break;
        cout << p_heads[most_recent_idx]->tweet_id << endl;
        p_heads[most_recent_idx] = p_heads[most_recent_idx]->p_next_tweet;
        news_feed_num++;
    }

    /*******************************************
                 Your code end at here
    *******************************************/

}

void follow(int user_id_A, int user_id_B) {
    int current_size = UsrList[user_id_A].followings_size;
    UsrList[user_id_A].followings[current_size] = &UsrList[user_id_B];
    UsrList[user_id_A].followings_size++;
}

void printTweets(int user_id) {
    Tweet *p = UsrList[user_id].p_my_tweets_head;
    if (isEmpty(user_id)) {
        cout << "Tweet of user " << user_id << " is empty. " << endl;
        return;
    }
    cout << "Tweets of user " << user_id << ": ";
    if (user_id == 0)
        while (p != NULL) {
            cout << p->tweet_id << " ";
            p = p->p_next_tweet;
        }
    else
        while (p != NULL) {
            cout << p->tweet_id << " ";
            p = p->p_next_tweet;
        }
    cout << endl;
}


/* 
    Original Task 3: Delete a tweet given a tweet id 
    Link List : Delete
    Input:
        tweet_id: first several number is user id and second several number is timestamp
        user_id: int, must smaller than MAX_USER. Used to get the User in UsrList
    Return:
        True: delete successfully
        False: No tweet found for the input tweet id
*/
bool delTweet(int tweet_id, int user_id) {      
    /*******************************************
                 Your code begin at here
    *******************************************/
    Tweet *p = UsrList[user_id].p_my_tweets_head;
    Tweet *p_front = NULL;
    while (p != NULL) {
        if (tweet_id == p->tweet_id) {
            if (p_front == NULL) {      // handle the head node
                UsrList[user_id].p_my_tweets_head = p->p_next_tweet;
                delete p;
                return true;
            }
            else {          // handle the normal node
                p_front ->p_next_tweet = p->p_next_tweet;
                delete p;
                return true;
            }
        }
        p_front = p;
        p = p->p_next_tweet;
    }
    return false;       // No tweet found
    /*******************************************
                 Your code end at here
    *******************************************/
}
