#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Server{
	public:
		virtual string requestContent(string fileName) = 0;
		virtual ~Server(){}
};

class OriginServer : public Server{
	public:
		string requestContent(string filename) override {
			return "Data of (Origin Server)" + filename;
		}
};

class EdgeServer : public Server{
	private:
		OriginServer* origin;
		vector<string> cache;
		
		bool findInCache(string filename){
			for(int i=0; i<cache.size(); i++){
				if(cache[i] == filename){
					return true;
				}
			}
			return false;
		}
	public:
		EdgeServer(OriginServer* o){
		     origin = o;
		}
		
		string requestContent(string filename){
			if(findInCache(filename)){
				return "Data from Edge Cache: " + filename;
			}
			else {
				cache.push_back(filename);
				return origin->requestContent(filename);
			}
		}
		
		void addFile(string filename){
			cache.push_back(filename);
		}
};

int main() {

    OriginServer origin;
    EdgeServer edge(&origin);
    
    edge.addFile("file1.txt");
    edge.addFile("file2.txt");

    cout << edge.requestContent("file1.txt") << endl;
    cout << edge.requestContent("file3.txt") << endl;
    cout << edge.requestContent("file2.txt") << endl;
    cout << edge.requestContent("file3.txt") << endl;

    return 0;
}







