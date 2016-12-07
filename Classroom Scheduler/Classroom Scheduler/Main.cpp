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

//This is better than brute force, in that:
//We won't try configurations for which a subset is known to be infeasible
//We only have to check a single node for conflicts for each trial configuration.
//Configurations that are equivalent by permutations of {R}, {K}, {N} are not attempted

//Using the same code with R = N removes the room number constraint.
//Using the same code with K = N removes the time slot constraint.
//Whatever the program acheives on its first run through would then be reported

#include <vector>
#include <set>
#include <algorithm> //std::count, max_element

using namespace std;

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

bool ColourIsAvailable(
	const Node & i_oNode,
	const int i_nTargetColour,
	const vector<int> & i_vectColours)
{
	for(const int nAdjacentNode 
		: i_oNode.m_setAdjacentNodeIDs)
	{
		if(i_vectColours[nAdjacentNode] == i_nTargetColour)
			return false;
	}

	return true;
}

int GetNextAvailableColour(
	const Graph & i_oGraph,
	const int i_nNodeIndex, 
	const vector<int> & i_vectColours,
	const int i_nMaxNodesPerColour) 
{
	assert(i_nNodeIndex >= 0
		&& i_nNodeIndex < i_oGraph.m_vectNodes.size());

	int nTryColour = i_vectColours[nNodeIndex] + 1; //since we want the next one
	for(; nTryColour < i_oGraph.m_vectNodes.size(); //just in case
	++nTryColour)
	{
		//Available implies no adjacent nodes with that colour, and node count constraint not violated.
		if(ColourIsAvailable(i_oGraph.m_vectNodes[i_nNodeIndex], nTryColour, i_vectColours)
			&& count(i_vectColours.begin, i_vectColours.end, nTryColour) < i_nMaxNodesPerColour)
		{
			return nTryColour;
		}
	}

	assert(false);
	return nTryColour;
}

//Returns true on success, false otherwise.
//Output vector not accessed on failure.
bool DoColouring(
	const Graph & i_oGraph, 
	int i_nMaxColours, 
	int i_nMaxNodesPerColour,
	vector<int> & o_vectNodeColours)
{
	//Some error checking

	//Set initial colours at -1
	vector<int> vectColours(-1, i_oGraph.m_vectNodes.size());

	//Find colour for nodes until success/failure
	int nWorkNode = 0;
	while(nWorkNode >= 0
		&& nWorkNode < i_oGraph.m_vectNodes.size())
	{
		//Get next available colour > current colour.
		int nNextAvailableColour = GetNextAvailableColour(oGraph, nNodeIndex, vectColours);

		//If this colour is K, backtrack on colouring sequence, otherwise proceed to next
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
	}

	//If backtracking on the first node, report failure.
	assert(nWorkNode == -1 
		|| nWorkNode == i_oGraph.m_vectNodes.size());
	if(nWorkNode == -1) 
	{
		return false;
	}

	//If proceeding on final node, report success
	o_vectNodeColours.swap(vectColours);
	return true;
}

void PrintCourseSchedulingSolution(
	const vector<int> & i_vectNodeColours)
{
	//We need room numbers. Count the occurrences of each colour.
	int nColourCount = *max_element(i_vectNodeColours.begin(), i_vectNodeColours.end());
	vector<int> vectColourOccurrences(0, nColourCount);

	for(int nNode = 0; 
		nNode < i_vectNodeColours.size(); 
		++nNode)
	{
		printf("Course: %d\tRoom: %d\tTime Slot:%d\n",
			nNode,
			i_vectNodeColours[nNode],
			vectColourOccurrences[i_vectNodeColours[nNode]]++);
	}
}

bool CheckSolution(
	const Graph & i_oGraph,
	const vector<int> & i_vectNodeColours,
	int i_nMaxColours, 
	int i_nMaxNodesPerColour)
{
	//Number of time slots (colours)
	int nMaxColour = *max_element(i_vectNodeColours.begin(), i_vectNodeColours.end());
	if(nMaxColour < 0
		|| nMaxColour >= i_nMaxColours)
		return false;

	//Number of rooms (number of nodes of each colour)
	for(int nColour = 0; 
		nColour < nMaxColour;
		++nColour)
	{
		int nOccurrenceCount = count(i_vectColours.begin, i_vectColours.end, nColour);
		if(nOccurrenceCount >= i_nMaxNodesPerColour)
			return false;
	}

	//Student conflicts (colouring constraint)
	for(int nNode = 0; 
		nNode < i_oGraph.m_vectNodes.size();
		++nNode)
	{
		if(!ColourIsAvailable(
			i_oGraph.m_vectNodes[nNode],
			i_vectColours[i_oGraph.m_vectNodes[nNode]],
			i_vectColours))
			return false;
	}

	return true;
}

bool SolveScheduling(
		const int i_nTimeSlotCount, 
		const int i_nRoomCount,
		const int i_nCourseCount,
		)
{
	//Construct graph from input
	Graph oGraph = MakeConstraintGraph(
		i_nCourseCount,
		i_oConstraints);

	//Colour the graph
	vector<int> vectNodeColours;
	bool bReturnValue = DoColouring(
		oGraph, 
		i_nTimeSlotCount, // i_nMaxColours
		i_nRoomCount, //i_nMaxNodesPerColour
		vectNodeColours);

	//Print the output
	if(bReturnValue)
		PrintCourseSchedulingSolution(vectNodeColours);
	
	return bReturnValue;
}

int main()
{
	//Probably easier to just export an API.
	return 0;
}