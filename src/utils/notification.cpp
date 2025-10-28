#include "notification.h"

void logMessage(const string &msg)
{

    notifications.push_back(msg);
    const int MAX_NOTIFICATIONS = 50;
    if (notifications.size() > MAX_NOTIFICATIONS)
    {
        // Xóa bớt phần tử cũ ở đầu (thông báo quá cũ)
        notifications.erase(notifications.begin(), notifications.begin() + (notifications.size() - MAX_NOTIFICATIONS));
    }
}