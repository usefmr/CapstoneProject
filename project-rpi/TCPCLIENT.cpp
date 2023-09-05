#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

int main()
{
    // Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        perror("socket");
        return 1;
    }

    // Set server IP address and port
    int port = 54000; 
    string ipAddress = "192.168.1.115";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    // Connect to the server on the socket
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1)
    {
        perror("connect");
        return 1;
    }

    // Receive and display logs in a continuous loop
    char buf[4096];
    string userInput;

    while (true)
    {
        memset(buf, 0, sizeof(buf));
        int bytesReceived = recv(sock, buf, sizeof(buf), 0);
        if (bytesReceived == -1)
        {
            perror("recv");
            break;
        }
        else if (bytesReceived == 0)
        {
            cout << "Server disconnected" << endl;
            break;
        }
        else
        {
            cout << "Received: " << string(buf, bytesReceived) << endl;
        }

        // Request updates from the server every second
        this_thread::sleep_for(chrono::seconds(1));
        send(sock, "Request updates", sizeof("Request updates"), 0);
    }

    // Close the socket
    close(sock);

    return 0;
}
 