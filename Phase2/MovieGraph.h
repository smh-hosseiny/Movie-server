#ifndef MOVIEGRAPH_H
#define MOVIEGRAPH_H

#include <vector>
#include <memory>
#include <map>

class MovieGraph
{
public:
	MovieGraph();
	void add_node();
	void display_graph();
	void set_weights(std::vector<int> users_purchased_movies_ids);
	void update_weights(int new_node, int related_node);
	void update_graph(int new_node, std::vector<int> related_nodes);
	std::map<int,int> get_not_purchased_movies(std::vector<int> users_movies_ids, int film_id);
	std::map<int,int> form_Id_weight_map(std::vector<int> linked_ids);
	void delete_wanted_movie(std::map<int,int> &movies_weights, int film_id);
	void delete_not_purchased_movies(std::map<int,int> &movies_weights,
		std::vector<int> users_movies_ids);
	std::vector<int> find_recommendation(std::map<int,int>);
	std::vector<int> recommend_movie(std::vector<int> users_movies_ids, int film_id);

	std::vector<std::pair<int,int>> sort_by_weight(std::map<int,int> map);
	std::vector<int> set_recommended_movies_ids(std::vector<std::pair<int,int>> Id_and_weight);
	std::vector<int> form_recommended_movies_ids_list(std::vector<std::pair<int,int>> Id_and_weight);

private:
	std::vector<std::vector<int> > graph;
	void set_new_graph(std::vector<std::vector<int> > &new_graph);

};

#endif