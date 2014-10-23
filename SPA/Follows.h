#include <string>
#include <set>
#include <vector>
using namespace std;

//public functions
class Follows{

private:
int follower, followee;
vector<pair<int,int>> followVec;

public:
//Constructor 
Follows();

//Accessor
set<int> getFollowee(int);
set<int> getFollower(int);
bool ifFollows(int,int);
set<int> getFolloweeStar(int);
set<int> getFollowerStar(int);
bool ifFollowsStar(int,int);

//Mutator
void insertFollows(int,int);

};