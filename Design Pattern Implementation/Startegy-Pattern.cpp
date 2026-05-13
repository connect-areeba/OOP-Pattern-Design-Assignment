#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 1. The Strategy Interface
// This acts as the "Abstract Base Class" required by the assignment.
class RoutingStrategy {
public:
    virtual string selectNode(const vector<string>& nodes) const = 0;
    virtual ~RoutingStrategy() {} 
};

// 2. Concrete Strategy A: Geographic (Nearest Node)
// This is a specific "Physical" implementation of the behavior.
class GeoLocationStrategy : public RoutingStrategy {
public:
    string selectNode(const vector<string>& nodes) const override {
        // Real-world logic: Uses GPS coordinates to find the index
        return nodes[0]; // Simplification for the demo: returns the first local node
    }
};

// 3. Concrete Strategy B: Load Balancing (Traffic Management)
// This is used when the local node is too busy.
class LoadBalancedStrategy : public RoutingStrategy {
public:
    string selectNode(const vector<string>& nodes) const override {
        // Real-world logic: Checks the 'health' attribute of each server
        return nodes[nodes.size() - 1]; // Returns the least busy node at the end of the list
    }
};

// 4. The Context: RequestRouter (The Brain)
class RequestRouter {
private:
    // Attributes of the physical network
    vector<string> networkMap = {"Karachi_Edge_Node", "London_Edge_Node", "NewYork_Edge_Node"};

public:
    // This method demonstrates Polymorphism through References
    void findBestServer(const RoutingStrategy& strategy) {
        string selected = strategy.selectNode(networkMap);
        cout << "[CDN Router] Applying strategy... Selected Server: " << selected << endl;
    }
};

// 5. Main: Executing the "Object Conversation"
int main() {
    // Creating the physical management object
    RequestRouter myRouter;
    
    // Creating strategy objects on the stack (No 'new' keyword, no pointers)
    GeoLocationStrategy geoLogic;
    LoadBalancedStrategy loadLogic;

    cout << "--- Situation: Standard User Request (Low Latency Priority) ---" << endl;
    myRouter.findBestServer(geoLogic); 

    cout << "\n--- Situation: Network Congestion Detected (Load Priority) ---" << endl;
    myRouter.findBestServer(loadLogic);

    return 0;
}