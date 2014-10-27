#include <cstddef>
#include <vector>

using namespace std;

class TNode {

private:

    string data;
	string nodeType;
	int procIndex;
	int stmtNum;
	vector<TNode> parent;
    vector<TNode> children;
	

public:
	//Constructor
	TNode();
    TNode(string, string,int,int);
	//Accessor for node
	string getData() ;
	int getStmtNum() ;
    int getProcIndex() ;
	string getNodeType() ;
	TNode getChild(int) ;
    TNode getParent() ;
	vector<TNode> getChildren() ;
	int getNumChildren() ;
	//Mutator for node
    void setData(string data);
	void addParent(TNode p);
    void addChild(TNode c);
};