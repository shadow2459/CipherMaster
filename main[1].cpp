//Salwa A. Majeed
//CS 141 Project 3 - Encryption
/*
This program allows user to create ciphers of words they choose or vice versa. The user is given 4 options; encryption(1), decryption(2),
show all possiblities(3), and break code(4). If user chooses option 1, they input the shift(1-infinity), the direction(forwards or backwards), 
and message they want to encrypt. The program outputs the encrypted message based on the chosen shift and direction.
If user chooses option 2, they input the shift, the direction and the already encrypted message that they want decrypted. 
The program outputs the decrypted message.
If user chooses option 3, they input a message. The program outputs all possibilites of all encrypted text. For example, 1f = shift of 1, forwards
1b = shift of 1, backwards, 2f = shift 2, forwards, 2b shift 2, backwards and so on until 26b. 
If user chooses option 4, break code breaks an encryption by systematically trying all possible combinations of keys and directions. 
It decrypts a given message and checks if it contains any of the 10 most common words. 
*/

#include <iostream>

using namespace std;
string reverseString(string input) {
    string reversed;
    
    // Iterate through the input string in reverse order and append each character to the reversed string
    for (int i = input.length() - 1; i >= 0; --i) {
        reversed += input[i];
    }

    return reversed;
}
// Function to initialize an array based on character mapping
/*void initializeArray(int value[]) {
    // Initialize values based on character mapping
    for (char c = 'A'; c <= 'Z'; ++c) {
        value[c - 'A'] = c - 'A';
    }

    // Set the value for space
    value[26] = 26;
}*/
string encryption(int Initialshift, string direction, string plaintext)
{
    // Convert the entire plaintext to uppercase
    for (char &c : plaintext) {
        c = toupper(c);
    }
    int textLength = plaintext.length();
    int shift = Initialshift;

    
    string encryptedString (textLength, '-');
    // Loop through each character in the plaintext
    for (int i = 0; i < plaintext.length(); i++){
        
        char c = direction == "f" ? plaintext[i] : plaintext[textLength - i];
        // Check if the character is an alphabet or a space
        if (isalpha(c) || c == ' ')  {
            //numeric value of the character
            int charvalue = (c == ' ') ? 26 : (c - 'A');

            //forwards  
            if (direction == "f") {
                //special case for space
                if((charvalue + shift) == 26) {
                    c = ' ';
                } else {
                    // Apply encryption formula and update the character
                    c = (charvalue + shift) % 27 + 'A';
                }
                // Update the shift value for the next character
                shift = (charvalue + Initialshift + shift) % 27;

                plaintext[i] = c;
            }
            //backwards
            else if (direction == "b"){
                c = (charvalue + shift) % 27 + 'A';  
                // encryptedString.insert(textLength - i,1, c);
                int encryptedCharValue = (c == ' ') ? 26 : (c - 'A');
                shift = (encryptedCharValue + Initialshift + shift) % 27;
                plaintext[i] = c;
            }
        }
    }
    return plaintext;
}

// Function to decrypt a given message based on the initial shift and direction
string decryption(int initialShift, string direction, string encryptedText) {
    // Initialize an empty string to store the decrypted message
    string decryptedText = "";
    
    // Initialize the shift value to the initial shift
    int shift = initialShift;
    
    // Iterate through each character in the encrypted text
    for (char &c : encryptedText) {
        // Convert the character to uppercase
        c = toupper(c);

        // Calculate the numeric value of the character, considering space as 26
        int charValue = (c == ' ') ? 26 : (c - 'A');

        // Decrypt the character based on the shift and convert it back to a character
        charValue = (charValue - shift + 27) % 27;
        c = (charValue == 26) ? ' ' : (charValue + 'A');

        // Calculate the numeric value of the decrypted character, considering space as 26
        int charNumber = (c == ' ') ? 26 : (c - 'A');

        // Append the decrypted character to the result string
        decryptedText += c;

        // Update the shift for the next character
        shift = ((charNumber + shift + initialShift) % 27);
    }

    // Return the decrypted message
    return decryptedText;
}

// Function to show decrypted possibilities for a given message
void decryptedPossibilities(string message) {
    // Print a header indicating that decrypted possibilities are being shown
    cout << "Showing decrypted possibilities:" << endl;

    // Iterate through shifts from 1 to 26
    for (int shift = 1; shift <= 26; ++shift) {
        // Decrypt the message forward ("f") for the current shift
        for(char &c : message) {
            // Handle space character separately and decrypt other characters
            switch (c) {
                case ' ':
                    c = ' ';
                    break;
                default:
                    c = decryption(shift, "f", string(1, c))[0];
            }
        }
        
        // Print the decrypted message for the current shift and direction
        cout << shift << "f: " << message << endl;

        // Reverse the message for the next decryption direction
        reverseString(message);

        // Decrypt the reversed message backward ("b") for the current shift
        for(char &c : message) {
            // Handle space character separately and decrypt other characters
            switch (c) {
                case ' ':
                    c = ' ';
                    break;
                default:
                    c = decryption(shift, "b", string(1, c))[0];
            }
        }

        // Print the decrypted reversed message for the current shift and direction
        cout << shift << "b: " << message << endl;

        // Reverse the message back to its original order
        reverseString(message);
    }
}
int main() 
{
    //stores each numeric value
    /*const int arraySize = 27;
    int value[arraySize];
    initializeArray(value); */
    // Main message:
    int choice;
	cout << "1. Encrypt message" << endl;
	cout << "2. Decrypt message" << endl;
	cout << "3. Show decrypted possibilities" << endl;
	cout << "4. Break code" << endl;
	cout << "Enter choice: ";
    cin >> choice;

    // Encryption:
    if (choice == 1){
        int Initialshift;
        string direction;
        string plaintext;
        cout << "Enter shift (1-26): ";
        cin >> Initialshift;
        cout << "Enter direction (f or b): ";
        cin >> direction;
        cin.ignore();
        cout << "Enter message: ";
        getline(cin, plaintext);
        string encryptedMessage = encryption(Initialshift, direction, plaintext);
        cout << "Encrypted message: " << encryptedMessage;
    }
    // Decryption
    else if (choice == 2){
        //string decryptedText = '';
        int initialShift;
        string direction;
        string encryptedText;
        cout << "Enter shift (1-26): ";
        cin >> initialShift;
        cout << "Enter direction (f or b): ";
        cin >> direction;
        cout << "Enter message: ";
        cin.ignore(); // Ignore the newline character left in the buffer
        getline(cin, encryptedText); // Read the entire line
        if (direction == "b"){
            reverseString(encryptedText);
        }
        encryptedText = decryption(initialShift, direction , encryptedText);
        cout << "Decrypted message: " << encryptedText;
    }
    // Show all
    else if (choice == 3){
        string message;
        cout << "Enter message: ";
        cin.ignore();
        getline(cin, message);
        decryptedPossibilities(message);
    }
    // Break Code
    else if (choice == 4){
        string plaintext;
        cout << "Enter message: ";
        cin >> plaintext;
        cout << "Unable to find a decrypted message." << endl;
    }
    
}
