#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_WORDS = 4096; // Max number of words in the wordlist and messages
                            // You may change this value if you have a larger wordlist

/*
 * **********  Task 0: **********
 *
 * This function reads words from wordlist.txt and store them in wordlist.
 * It returns 'true' if successfully loaded, 'false' otherwise.
 *
 * This function is provided for you for reference. You should not modify it.
 */
int wordCount = 0;          // Actual number of words in the wordlist
string wordlist[MAX_WORDS]; // Store all the words in wordlist
bool read_word_list()
{
    // Use ifstream to open the file and check if the file is correctly open.
    // If not, return false.
    ifstream fin;
    fin.open("wordlist.txt");
    if (!fin.is_open())
    {
        return false;
    }

    // Read wordCount and wordlist from the file.
    // Remember to close the input stream after reading all words.
    fin >> wordCount;
    for (int i = 0; i < wordCount; ++i)
    {
        fin >> wordlist[i];
    }
    fin.close();

    return true;
}

/*
 * **********  Task 1: **********
 *
 * This function checks if the word is in the wordlist.
 * Return 'true' if the word is in the wordlist, 'false' otherwise.
 */
bool is_in_list(string word)
{
    // TODO: implement this function according to comments above.
    // CODE STARTS HERE
    for (int i = 0; i < wordCount; i++)
    {
        if (word == wordlist[i])
        {
            return true;
        }
    }
    return false;
    // CODE ENDS HERE
}

/*
 * **********  Task 2: **********
 *
 * This function checks if ALL the words in the array are in the wordlist.
 * Return 'true' if ALL words are in the wordlist, 'false' otherwise.
 *
 * Hint: You should use 'is_in_list(string word)' in this function.
 */
bool is_all_in_list(string word[], int length)
{
    // TODO: implement this function according to comments above.
    // CODE STARTS HERE
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        if (is_in_list(word[i]))
        {
            count++;
        }
    }
    if (count >= 2)
    {
        return true;
    }
    else
    {
        return false;
    }

    // CODE ENDS HERE
}

/*
 * **********  Task 3: **********
 *
 * Read encrypted messages from encrypted.txt and store it in the string array
 * encrypted[], and also store its length in message_len. It returns 'true'
 * if successfully loaded, and 'false' otherwise.
 *
 * This task should be similar to the Task 0 given, but remember to skip extra
 * spaces, as we described in lab webpage.
 */
bool read_encrypted_messages(string encrypted[], int &message_len)
{
    // TODO: read and store message from encrypted.txt.
    // Remember to close the input stream after reading all messages.
    // CODE STARTS HERE

    ifstream fin;
    fin.open("encrypted.txt");
    if (!fin.is_open())
    {
        return false;
    }

    std::string line;
    for (message_len = 0; std::getline(fin, line); ++message_len)
        ;

    fin.clear();
    fin.seekg(0);

    for (int i = 0; i < message_len; ++i)
    {
        fin >> encrypted[i];
    }
    fin.close();

    return true;
    // CODES ENDS HERE
}

/*
 * **********  Task 4: **********
 *
 * This function tries all possible shifts from 0 to 25,
 * and check if any shift makes the message valid (i.e.,
 * all words in the decrypted message are in the wordlist).
 *
 * If any shift makes the message valid, it returns true,
 * and the decrypted message is stored in the string array decrypted[],
 * otherwise it returns false and the array decrypted[] is meaningless.
 * (i.e., we don't care about the value in the array)
 *
 */
bool find_valid_shift(string encrypted[], int message_len, string decrypted[])
{
    // TODO: implement this function according to comments above.
    // CODE STARTS HERE
    string encryptedTemp[MAX_WORDS];
    string decryptedTemp[MAX_WORDS];
    for (int j = 0; j <= 25; j++)
    {
        for (int i = 0; i < MAX_WORDS; i++)
        {
            encryptedTemp[i] = encrypted[i];
            decryptedTemp[i] = decrypted[i];
        }

        for (int i = 0; i < message_len; i++)
        {
            for (int k = 0; k < encryptedTemp[i].length(); k++)
            {
                decryptedTemp[i] += encryptedTemp[i][k] + j;
                if (encryptedTemp[i][k] + j > 122)
                {
                    decryptedTemp[i][k] -= 26;
                }
            }
        }
        if (is_all_in_list(decryptedTemp, message_len))
        {
            for (int i = 0; i < MAX_WORDS; i++)
            {
                decrypted[i] = decryptedTemp[i];
            }
            return true;
            break;
        }
    }

    return false;
    // CODE ENDS HERE
}

/*
 * **********  Task 5: **********
 *
 * This function stores decrypted message(given in the string array decrypted[])
 * into file "decrypted.txt". Each word in the message should be followed by a space.
 * If the file cannot be opened, it returns 'false', otherwise, returns 'true'.
 *
 * Remember to close output stream after writing all messages.
 */
bool store_decrypted_messages(string decrypted[], int message_len)
{
    // TODO: create an output stream and write message into file "decrypted.txt"
    // CODE STARTS HERE

    ofstream MyFile("decrypted.txt");

    if (!MyFile)
    {
        return false;
    }

    for (int i = 0; i < message_len; i++)
    {
        MyFile << decrypted[i] << ' ';
    }
    MyFile.close();

    return true;

    // CODE ENDS HERE
}

int main()
{

    // Read wordlist
    if (!read_word_list())
    {
        // We recommend using cerr to print error messages.
        cerr << "Error: cannot open wordlist.txt" << endl;
        return -1;
    }

    // Read encrypted messages
    string encrypted[MAX_WORDS];
    int message_len = 0;
    if (!read_encrypted_messages(encrypted, message_len))
    {
        cerr << "Error: cannot open encrypted.txt" << endl;
        return -1;
    }

    // Try all possible shifts
    string decrypted[MAX_WORDS];
    if (!find_valid_shift(encrypted, message_len, decrypted))
    {
        cerr << "Error: No valid shift has been found" << endl;
        return -1;
    }

    // write decrypted messages into file "decrypted.txt"
    if (!store_decrypted_messages(decrypted, message_len))
    {
        cerr << "Error: cannot open decrypted.txt" << endl;
        return -1;
    }

    cout << "Successfully decrypted the message!" << endl;
    return 0;
}
