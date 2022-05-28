#include "myTwitter.h"
#include <fstream>

int main() {
    /* Initialize my Twitter */
    init_user();

    /* Add relationships based on following_relationship.txt */
    char buffer[256];
    ifstream following("following_relationship.txt");
    if (!following.is_open())
        throw invalid_argument( "Cannot find following_relationship.txt, please check your current path!" );
    while (!following.eof()) {
        following.getline(buffer, 100);
        follow(int(buffer[0] - '0'), int(buffer[2] - '0'));
    }

    /* Post tweets based on tweet.txt */
    ifstream tweets("tweet.txt");
    if (!tweets.is_open())
        throw invalid_argument( "Cannot find tweet.txt, please check your current path!" );
    while (!tweets.eof()) {
        tweets.getline(buffer, 100);
        postTweet(int(buffer[0] - '0'));
    }

    /* Check Task 1 and Task 2 */
    cout << "******************************************" << endl;
    cout << "All tweets in current myTwitter: " << endl;
    cout << "******************************************" << endl;
    for (int user_id=0; user_id<MAX_USER; user_id++)
        printTweets(user_id);

    /* Check Task 3 */
    cout << "******************************************" << endl;
    cout << "Recent news feed of user 1: " << endl;
    cout << "******************************************" << endl;
    printNewsFeed(1);

    /* Delete the dynamic objects (Link list) */
    cout << "******************************************" << endl;
    cout << "Delete all dynamic objects." << endl;
    cout << "******************************************" << endl;
    for (int i=0; i<MAX_USER; i++) {
        while(!isEmpty(i))
            delTweet(UsrList[i].p_my_tweets_head->tweet_id, i);
    }
    for (int user_id=0; user_id<MAX_USER; user_id++)
        printTweets(user_id);

    return 0;
}