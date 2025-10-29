#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <ctime>

using namespace std;

string encipher(string plaintext, int key, vector<char> alphabet);
string decipher(string ciphertext, int key, vector<char> alphabet);
vector<char> generateRandomAlphabet(vector<char>ascii);

int main()
{
    string text;
    int key;
    int alphOption, EDoption, n;

    vector<char>englishAlphabet = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    vector<char>ascii;
    vector<char>randomAlpabeth;

    for(int i=32; i<127; i++)
        ascii.push_back(static_cast<char>(i));

    do
    {
        cout<<"\n\n\t\t----- OPTIONS -----\n1) English alphabet\n2) ASCII\n3) Random alphabet";
        cout<<"\nSelect an option: "; cin>>alphOption;

        if(alphOption<=0 || alphOption>3)
        {
            cout<<"\nInvalid";
            continue;
        }
        else if(alphOption == 3)
        {
            if(randomAlpabeth.size() != 0)
            {
                char change;
                cout<<"Change alphabet? (y/n): "; cin>>change;

                if(change == 'y')
                    randomAlpabeth = generateRandomAlphabet(ascii);
            }
            else
                randomAlpabeth = generateRandomAlphabet(ascii);

            if(randomAlpabeth.size() == 0)
                continue;
        }

        cout<<"\n1) Cipher\n2) Decipher";
        cout<<"\nSelect an option: "; cin>>EDoption;

        cout<<"\nWrite a text: "; 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, text);
        cout<<"Key: "; cin>>key;

        if(EDoption == 1)
        {
            string encipherResult;
            if(alphOption==1)
                encipherResult = encipher(text, key, englishAlphabet);
            else if (alphOption==2)
                encipherResult = encipher(text, key, ascii);
            else
                encipherResult = encipher(text, key, randomAlpabeth);

            cout<<"\nCiphertext: "<<encipherResult; 
        }
        else if(EDoption==2)
        {
            string decipherResult;
            if(alphOption==1)
                decipherResult = decipher(text, key, englishAlphabet);
            else if (alphOption==2)
                decipherResult = decipher(text, key, ascii);
            else
                decipherResult = decipher(text, key, randomAlpabeth);

            cout<<"\nPlaintext: "<<decipherResult;
        }
        else
        {
            cout<<"\nInvalid";
            continue;
        }
    } while(1);
    return 0;
}

string encipher(string plaintext, int key, vector<char> alphabet)
{
    string ciphertext = "";
    int index;

    for(int i=0; i<plaintext.length(); i++)
    {
        auto findchar = find(alphabet.begin(), alphabet.end(), plaintext[i]);
        index = (findchar != alphabet.end()) ? distance(alphabet.begin(), findchar): -1;

        if(index == -1)
            return "HA OCURRIDO UN ERROR";
        
        ciphertext += alphabet[(index+key)%alphabet.size()];
    }
    return ciphertext;
}

string decipher(string ciphertext, int key, vector<char> alphabet)
{
    string plaintext = "";
    int index;

    for(int i=0; i<ciphertext.length(); i++)
    {
        auto findchar = find(alphabet.begin(), alphabet.end(), ciphertext[i]);
        index = (findchar != alphabet.end()) ? distance(alphabet.begin(), findchar): -1;

        if(index == -1)
            return "HA OCURRIDO UN ERROR";

        int indexvalidation = index-key;
        index = (indexvalidation>=0) ? indexvalidation%alphabet.size(): alphabet.size()-((indexvalidation*-1)%alphabet.size());
        plaintext += alphabet[index];
    }
    return plaintext;
}

vector<char> generateRandomAlphabet(vector<char>ascii)
{
    vector<char> randomAlpabeth;
    int n;

    cout<<"\nEnter n (1-95): "; cin>>n;
    if(n>0 && n<=95)
    {
        int i=0;
        while(i<n)
        {
            srand(time(NULL));
            char element = ascii[rand()%95];
            auto findelement = find(randomAlpabeth.begin(), randomAlpabeth.end(), element);
            if(findelement == randomAlpabeth.end())
            {
                randomAlpabeth.push_back(element);
                cout<<i+1<<" - "<<element<<"\t";
                i++;
            }
        }
    }
    else
    {
        cout<<"\nInvalid";
        return randomAlpabeth;
    }
    return randomAlpabeth;
}