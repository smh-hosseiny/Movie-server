#include "MovieGraph.h"
#include <iostream>
#include <algorithm>
#include <map>


using namespace std;

MovieGraph::MovieGraph()
{}


void MovieGraph::add_node()
{
	int new_size = graph.size() +1;
	vector<vector<int> > new_graph(new_size, vector<int>(new_size, 0));
	set_new_graph(new_graph);
	graph = new_graph;
}


void MovieGraph::remove_node(int film_id)
{
	graph.erase(graph.begin() + film_id);
	for(auto &elem : graph)
	{
		elem.erase(elem.begin()+film_id);
	}
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

void MovieGraph::update_weights(int new_node, int related_node)
{
	if(related_node != new_node)
	{
		graph[new_node-1][related_node-1]++;
		graph[related_node-1][new_node-1]++;
	}
}

void MovieGraph::update_graph(int new_node, vector<int> related_nodes)
{
	for(auto &elem :related_nodes)
	{
		update_weights(new_node, elem);
	}
}


void MovieGraph::delete_not_purchased_movies(map<int,int> &movies_weights, vector<int> users_movies_ids)
{
	if(!users_movies_ids.empty())
	{
		for(auto &elem : users_movies_ids)
			movies_weights.erase(movies_weights.find(elem));
	}
}


void MovieGraph::delete_wanted_movie(map<int,int> &movies_weights, int film_id)
{
	if(movies_weights.count(film_id) > 0)
		movies_weights.erase(movies_weights.find(film_id));
}

map<int,int> MovieGraph::form_Id_weight_map(vector<int> linked_ids)
{
	map<int,int> movies_weights;
	for(int i=0; i<linked_ids.size(); i++)
	{
		movies_weights[i+1] = linked_ids[i];
	}
	return movies_weights;
}

map<int,int> MovieGraph::get_not_purchased_movies(vector<int> users_movies_ids, int film_id)
{
	vector<int> linked_ids = graph[film_id-1];
	map<int,int> movies_weights = form_Id_weight_map(linked_ids);	
	delete_not_purchased_movies(movies_weights, users_movies_ids);
	delete_wanted_movie(movies_weights, film_id);
	return movies_weights;
}

vector<int> MovieGraph::form_recommended_movies_index_list(vector<pair<int,int>> Id_and_weight)
{
	vector<int> recommended_movies_index;
	for(auto &elem : Id_and_weight)
	{
		recommended_movies_index.push_back(elem.first -1);
	}
	return recommended_movies_index;
}


vector<int> MovieGraph::set_recommended_movies_index(vector<pair<int,int>> Id_and_weight)
{
	vector<int> recommended_movies_index = form_recommended_movies_index_list(Id_and_weight);
	if(recommended_movies_index.size() > 4)
		recommended_movies_index.resize(4);
	return recommended_movies_index;
}

vector<int> MovieGraph::find_recommendation(map<int,int> movies_weights)
{
	vector<pair<int,int>> Id_and_weight = sort_by_weight(movies_weights);	
	vector<int> recommended_movies;
	recommended_movies = set_recommended_movies_index(Id_and_weight);
	return recommended_movies;
}


vector<int> MovieGraph::recommend_movie(vector<int> users_movies_ids, int film_id)
{
	map<int,int> linked_ids = get_not_purchased_movies(users_movies_ids, film_id);
	vector<int> recommended_movies = find_recommendation(linked_ids);
	return recommended_movies;
}


vector<pair<int,int>> MovieGraph::sort_by_weight(map<int,int> map)
{
	std::vector<pair<int,int>> sorted;

	copy(map.begin(), map.end(), back_inserter<vector<pair<int,int>>>(sorted));

	sort(sorted.begin(), sorted.end(), [](const pair<int,int>& l, const pair<int,int>& r)
    {
		if (l.second != r.second)
			return l.second > r.second;

		return l.first < r.first;
	});
	return sorted;
}