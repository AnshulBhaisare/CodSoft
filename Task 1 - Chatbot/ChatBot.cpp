#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string toLowerCase(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}


string chatbotResponse(const string& userInput) {
    string input = toLowerCase(userInput);


    if (input.find("hello") != string::npos || input.find("hi") != string::npos || input.find("hey") != string::npos) {
        return "Hello! How can I help you today?";
    } else if (input.find("how are you") != string::npos) {
        return "I'm just a bot, but I'm doing well! How can I assist you?";
    }


    else if (input.find("bye") != string::npos || input.find("goodbye") != string::npos) {
        return "Goodbye! Have a great day!";
    }


    else if (input.find("services") != string::npos || input.find("help") != string::npos) {
        return "I can help you with various tasks such as providing information, answering queries, or just having a chat!";
    }


    else if (input.find("weather") != string::npos) {
        return "I'm not connected to a live weather service, but it's always good to check the forecast online!";
    } else if (input.find("time") != string::npos) {
        return "You can check the current time on your device or ask a voice assistant!";
    }


    else {
        return "I'm not sure how to respond to that. Could you ask something else?";
    }
}

int main() {
    cout << "Chatbot: Hello! I'm a simple chatbot. Type 'bye' to exit." << endl;

    string userInput;
    while (true) {
        cout << "You: ";
        getline(cin, userInput);

        if (toLowerCase(userInput) == "bye") {
            cout << "Chatbot: Goodbye! Have a great day!" << endl;
            break;
        }

        string response = chatbotResponse(userInput);
        cout << "Chatbot: " << response << endl;
    }

    return 0;
}
