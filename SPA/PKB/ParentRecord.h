#include <iostream>
#include<string>

using namespace std;

class ParentRecord{

	private :
	
	int stmt1;
	int stmt2;
	
	public :
	
	ParentRecord(int,int);
	int getChild();
	int getParent();
};
	