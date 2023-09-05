#include <iostream>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <sys/stat.h> 

using namespace std;

// Function to read new log entries from the file
string readNewLogEntries(const string& lastReadContent, const string& filePath) {
    ifstream file(filePath);
    string newContent;

    if (file) {
        ostringstream contentStream;
        contentStream << file.rdbuf();
        newContent = contentStream.str();
    }

    // Find the position where the previous content ends
    size_t startPos = newContent.find(lastReadContent);

    if (startPos != string::npos) {
        // Extract the new log entries
        newContent = newContent.substr(startPos + lastReadContent.size());
    }

    return newContent;
}

int main() {
    const char* logFilePath = "/home/youssef/project/run_logs.log";
    if (access(logFilePath, R_OK) == -1) {
        cerr << "Error: Log file is not readable. Please check file permissions." << endl;
        return -1;
    }

    // Create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1) {
        cerr << "Can't create a socket! Quitting" << endl;
        return -2;
    }

    // Bind the IP address and port to a socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);

    if (bind(listening, (sockaddr*)&hint, sizeof(hint)) == -1) {
        cerr << "Can't bind to IP/Port. Quitting" << endl;
        return -3;
    }

    // Tell the socket it's for listening
    listen(listening, SOMAXCONN);

    vector<int> clientSockets;

    string lastReadContent; // Store the last read content of the log file

    while (true) {
        // Check for new log entries
        string newContent = readNewLogEntries(lastReadContent, logFilePath);

        // If there are new log entries, send them to connected clients
        if (!newContent.empty()) {
            for (int clientSocket : clientSockets) {
                send(clientSocket, newContent.c_str(), newContent.size(), 0);
            }

            // Update the last read content
            lastReadContent += newContent;
        }

        // Accept client connections and create client sockets (ignore client input)
        sockaddr_in client;
        socklen_t clientSize = sizeof(client);

        int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);

        clientSockets.push_back(clientSocket);
    }

    // Close the listening socket and clean up
    close(listening);
    for (int clientSocket : clientSockets) {
        close(clientSocket);
    }

    return 0;
}

