#include <string>
#include <set>
using namespace std;

//public functions
class Parent{

private:
int parent, child;
vector<pair<int,int>> parentVec;

public:
//Constructor 
Parent(); 

//Accessor
set<int> getParent(int);
set<int> getChild(int);
bool ifParent(int,int);
set<int> getParentStar(int);
set<int> getChildStar(int);
bool ifParentStar(int,int);

//Mutator
void insertParent(int,int);




};