#ifndef MOVIEGRAPH_H
#define MOVIEGRAPH_H

#include <vector>
#include <memory>

class MovieGraph
{
public:
	MovieGraph();
	void add_node();
	void display_graph();
	void set_weights(std::vector<int> users_purchased_movies_ids);
	void update_graph(int new_node, std::vector<int> related_nodes);
	std::vector<int> recommend_movie(std::vector<int> users_movies_ids, int film_id);

private:
	std::vector<std::vector<int> > graph;
	void set_new_graph(std::vector<std::vector<int> > &new_graph);

};

#endif