#include "notification.h"

void logMessage(const string &msg)
{
    cout << msg << endl;
    notifications.push_back(msg);
}