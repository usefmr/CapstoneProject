#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
//#include "simple_logger.h"

using namespace std;
string logg;
#define MAX_TEXT 512
struct my_msg {
    long int msg_type;
    char some_text[MAX_TEXT];
};

void send(string buffer){
int msgid;
struct my_msg some_data;
msgid = msgget((key_t)12345, 0666 | IPC_CREAT);

if (msgid == -1) {
    cerr << "Error in creating queue" << std::endl;
    exit(0);
}
//char buffer[50];
//strncpy(buffer, data, 50);
some_data.msg_type = 1;
const char* data = buffer.c_str();

strcpy(some_data.some_text, data);
if (msgsnd(msgid, (void *)&some_data, MAX_TEXT, 0) == -1) {
    cerr << "Msg not sent" << endl;
    }
}


int add(int x, int y) {
    return x + y;
}

int subtract(int x, int y) {
    return x - y; 
}

int multiply(int x, int y) {
    return x * y;
}

double divide(int x, int y) {
    if (y == 0) {
        cerr << "Cannot divide by zero" << endl;
        //strncpy(buffer, "error", 50);

        //log = "error";
        //LOG_ERROR << "ERROR-used divided by zero";
        logg="error-user divided by zero";
        send(logg);
        return 0;
    }
    else{
    return static_cast<double>(x) / y;
    }
}

double power(int x, int y) {
    return pow(static_cast<double>(x), static_cast<double>(y));
}

void displayHelp() {
    logg = "trace-displaying help";
    send(logg);
    cout << "Usage: calculator <operand1> <operator> <operand2>" << endl;
    cout << "Available operators: + - * / ^" << endl;
}

int main(int argc, char *argv[]) {
        //LOG_TRACE << "this is a trace message";
   // strncpy(buffer, "trace", 50);
   //send("main");
    logg = "trace-user entered main";
    send(logg);
    if (argc == 2 && (string(argv[1]) == "--help")) {
        // User misused the app or requested help
        displayHelp();
        return 0;
    }

    char op;
    int operand1, operand2;
   

    while (true) {
        cout << "Enter an expression (e.g., 5 + 3 or 'exit' to quit or '--help' to get help): ";
        string input;
        getline(cin, input);

        if (input == "exit") {
            logg = "exit";
            send(logg);
            break;
        }
        /*else if (input == "--help") {
            displayHelp();

        }*/
        int pos = input.find_first_of("+-*/^");
        
        if (pos != string::npos && pos > 0 && pos < input.length() - 1) {
            operand1 = stoi(input.substr(0, pos));
            operand2 = stoi(input.substr(pos + 1));
            op = input[pos];

            switch (op) {
                case '+':
                    logg = "trace-user chose '+' operation";
                    send(logg);
                    cout << add(operand1, operand2) << endl;
                    break;
                case '-':
                 logg = "trace-user chose '-' operation";
                    send(logg);
                    cout << subtract(operand1, operand2) << endl;
                    break;
                case '*':
                 logg = "trace-user chose '*' operation";
                    send(logg);
                    cout << multiply(operand1, operand2) << endl;
                    break;
                case '/':
                 logg = "trace-user chose '/' operation";
                    send(logg);
                    cout << divide(operand1, operand2) << endl;
                    break;
                case '^':
                 logg = "trace-user chose '^' operation";
                    send(logg);
                    cout << power(operand1, operand2) << endl;
                    break;
                default:
                    break;
                    //cerr << "Invalid operator: " << op << endl;
                    //displayHelp();
            }
        } else {
            if (input != "--help") {
            logg = "error-user misused app..displaying help";
            send(logg);
            cerr << "Invalid input." << endl;}
            displayHelp();
        }
    }

    return 0;
}
