//Very quick and dirty. Avert your eyes.

//R classrooms
//K time slots
//N courses
//M students, each taking courses
//Students as a list of lists of course numbers

//We require an answer: for each course, {room, time slot} = {r,k} 

//A constraint graph representing the courses is created,
//For each student's course list, the pairs of courses are enumerated.
//For each pair, an edge between two courses is added to the constraint graph 
//We attempt to K-colour the graph, such that there are no more than R nodes of each colour
//If successful, the r^th node of colour k is scheduled at {r,k}

//K-colouring:
//Set initial colours at -1
//begin processing on node *, seeded to start of work list
//Set colour at next available colour > current colour.
//	available implies no adjacent nodes with that colour, and node count constraint not violated.
//If this colour is K, backtrack on colouring sequence 
//	(effectively trying last node at next available colour)
//If backtracking on the first node, report failure.
//If proceeding on final node, report success

//This is better than brute force, in that:
//We won't try configurations for which a subset is known to be infeasible
//Configurations that are equivalent by permutations of {R}, {K}, {N} are not attempted

//Using the same code with R = N removes the room number constraint.
//Using the same code with K = N removes the time slot constraint.
//Whatever the program acheives on its first run through would then be reported

#include <vector>
#include <set>
using namespace std;

//Better if nodes are vector<Node *> adjacency with no ID and scratch is mapped onto it.
//We're just doing it this way because its easier.
struct Node
{
	set<int> m_setAdjacentNodeIDs;
};

struct Graph
{
	void AddEdge(
		int i_nNode1, 
		int i_nNode2)
	{
		//node ID's should be valid.
		if(i_nNode1 >= 0 && i_nNode1 < m_vectNodes.size()
			i_nNode2 >= 0 && i_nNode2 < m_vectNodes.size())
		{
			//Add adjacency to both nodes
			m_vectNodes[i_nNode1].m_setAdjacentNodeIDs += i_nNode2;
			m_vectNodes[i_nNode2].m_setAdjacentNodeIDs += i_nNode1;
		}
	}

	vector<Node> m_vectNodes;
};

void DoColouring(
	const Graph & i_oGraph, 
	int i_nMaxColours, 
	int i_nMaxNodesPerColour)
{
	//some error checking

	//Set initial colours at -1
	vector<int> vectColours(-1, i_oGraph.m_vectNodes.size());

	//begin processing on node *, seeded to start of work list
	int nWorkNode = 0;

	while(true)
	{
		//Get next available colour > current colour.
		//	available implies no adjacent nodes with that colour, and node count constraint not violated.
		int nNextAvailableColour = GetNextAvailableColour(oGraph, nNodeIndex, nCurrentColour);

		//If this colour is K, backtrack on colouring sequence 
		//	(effectively trying last node at next available colour)
		assert(nNextAvailableColour >= 0
			&& nNextAvailableColour <= i_nMaxColours);
		if(nNextAvailableColour < i_nMaxColours)
		{
			vectColours[nWorkNode] = nNextAvailableColour;
			++nWorkNode;
		}
		else
		{
			vectColours[nWorkNode] = -1;
			--nWorkNode;
		}

		//Loop condition / success failure
		if(nWorkNode == -1) 
		{//If backtracking on the first node, report failure.
			return false;
		}
		else if(nWorkNode == i_oGraph.m_vectNodes.size()) 
		{//If proceeding on final node, report success
			return true;
		}
	}

	//Prepare solution from colour vector. 
	//We also need room numbers. Count the occurrences of each colour.

}

int main()
{
	//Probably easier to just export an API.
	return 0;
}