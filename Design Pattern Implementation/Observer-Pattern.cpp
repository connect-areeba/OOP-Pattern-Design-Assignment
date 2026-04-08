#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Observer{
	
	public:
		
		virtual void fileUpdate(string filename) = 0;
		virtual ~Observer(){}
		
};

class Edge : public Observer{
	
	private:
		
		string name;
		vector<string> cachedFiles;
	
	public:
		
		//constructor
		Edge(string edgeName){
		    name = edgeName;
		}
		
		string getName(){
			return name;
		}
		
        void fileUpdate(string filename) override {
        	for(int i=0; i<cachedFiles.size(); i++){
        		if(cachedFiles[i] == filename){
        			cachedFiles.erase(cachedFiles.begin() + i);
        			cout<<"File "<<filename<<" deleted"<<endl;
        			break;
				}
			}
			AddtoCache(filename);
			cout<<endl;
	}
		
		void AddtoCache(string filename){
			cachedFiles.push_back(filename);
			
			cout<<"Edge "<<name<<" update file: "<<filename<<endl;
		}
	
};

class Origin : public Observer{
	
	private:
		vector<Edge*> edges;
		
	public:
		
		void getEdge(){
			for(int i=0; i<edges.size(); i++){
				cout<<edges[i]->getName()<<endl;
			}
		}
		
		void addEdgeServer(Edge* edge){
			edges.push_back(edge);
		}
		void fileUpdate(string filename) override {
			for(int i=0; i<edges.size(); i++){
				edges[i]->fileUpdate(filename);
			}
		}
};



int main() {
    
    Origin origin;
    
    Edge edge1("Edge-1");
    Edge edge2("Edge-2");
    Edge edge3("Edge-3");
    
    cout<<endl;
    
    origin.addEdgeServer(&edge1);
    origin.addEdgeServer(&edge2);
    origin.addEdgeServer(&edge3);
    
    cout<<"\nCurrent Edge Servers: "<<endl;
    origin.getEdge();
    cout<<endl;
    
    edge1.AddtoCache("file1.txt");
	edge2.AddtoCache("file1.txt");
	edge3.AddtoCache("file1.txt");
    cout<<endl;

	cout << "Updating file: file1.txt" << endl;
    origin.fileUpdate("file1.txt");

    
    return 0;
}






















