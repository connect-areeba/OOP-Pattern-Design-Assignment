#include <iostream>
#include <string>
#include <vector>

using namespace std;

class requestRouter {
private:
    static requestRouter* instance;
    vector<string> activeServers;

    requestRouter() {}

public:
    static requestRouter* getInstance() {
        if (!instance) {
            instance = new requestRouter();
        }
        return instance;
    }

    void addServer(const string& server) {
        activeServers.push_back(server);
        cout << "System: Added " << server << " to the cluster." << endl;
    }

    void serverDown(const string& server) {
        bool found = false;
        for (int i = 0; i < activeServers.size(); i++) {
            if (activeServers[i] == server) {
                activeServers.erase(activeServers.begin() + i);
                cout << "ALERT: " << server << " is down. Removing from active servers." << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Notice: " << server << " not found in active list." << endl;
        }
    }

    void printTable() {
        if (activeServers.empty()) {
            cout << "[No active servers]" << endl;
        } else {
            for (int i = 0; i < activeServers.size(); i++) {
                cout << i + 1 << ". " << activeServers[i] << endl;
            }
        }
    }
};

requestRouter* requestRouter::instance = nullptr;

int main() {
    requestRouter* router = requestRouter::getInstance();

    router->addServer("server 1");
    router->addServer("server 2");
    router->addServer("server 3");

    router->printTable();

    router->serverDown("server 2");
    
    router->printTable();

    return 0;
}