#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Iterator{
    public:
       virtual bool hasNext() = 0;
       virtual string next() = 0;
       virtual ~Iterator() {}
};
class CacheIterator : public Iterator{
    private:
        vector<string> cache;
        int index;
    public:
        CacheIterator(vector<string> files){
            cache = files;
            index = 0;
        }
        bool hasNext() override{
            return index < cache.size();
        }
        string next() override{
            return cache[index++];
        }
};
class EdgeServer{
    private:
        vector<string> cache;
        string name;
    public:
        EdgeServer(string n){
            name = n;
        }
        void addFile(string filename){
            cache.push_back(filename);
            cout << name << " added files: " << filename << endl;
        }
        Iterator* creatIterator(){
            return new CacheIterator(cache);
        }
        string getname(){
            return name;
        }
};
int main(){
    EdgeServer edge("Edge-Server-1");
    edge.addFile("video.mp4");
    edge.addFile("image.jpg");
    edge.addFile("style.css");
    edge.addFile("script.js");
    cout << "\nIterating through cached files: \n";
    Iterator* it = edge.creatIterator();
    while(it->hasNext()){
        cout << "File: " << it->next() << endl;
    }
    delete it;
    return 0;
}
