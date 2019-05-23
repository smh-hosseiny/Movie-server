#include "MovieGraph.h"
#include <iostream>
#include <algorithm>

using namespace std;

MovieGraph::MovieGraph()
{}


void MovieGraph::add_node()
{
	int new_size = graph.size() +1;
	vector<vector<int> > new_graph(new_size, vector<int>(new_size, 0));
	set_new_graph(new_graph);
	graph = new_graph;
	//cout << new_graph.size() << " " << endl;
}


void MovieGraph::set_new_graph(vector<vector<int> > &new_graph)
{
	for(int i=0; i<graph.size(); i++)
	{
		for(int j=0; j<graph[i].size(); j++)
			new_graph[i][j] = graph[i][j];
	}
}


void MovieGraph::display_graph()
{
	cout << "the Graph : " << endl;
	for(auto &link : graph)
	{
		for(auto &elem :link)
			cout << elem << " ";
		cout << endl;
	}
	cout << endl;
}

void MovieGraph::set_weights(vector<int> users_purchased_movies_ids)
{
	int new_node = users_purchased_movies_ids.back();
	users_purchased_movies_ids.pop_back();
	vector<int> related_nodes = users_purchased_movies_ids;
	update_graph(new_node, related_nodes);
}

void MovieGraph::update_graph(int new_node, vector<int> related_nodes)
{
	for(auto &elem :related_nodes)
	{
		if(elem != new_node)
		{
			graph[new_node-1][elem-1]++;
			graph[elem-1][new_node-1]++;
		}
	}
}



vector<int> MovieGraph::recommend_movie(vector<int> users_movies_ids, int film_id)
{
	vector<int> linked_ids = graph[film_id-1];
	for(auto &elem : users_movies_ids)
	{
		linked_ids[elem-1] = 0;
	}
	linked_ids.erase(remove(linked_ids.begin(), linked_ids.end(), 0), linked_ids.end());
	sort(linked_ids.begin(), linked_ids.end());
	return linked_ids;
}
