/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Solver.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 10:10:21 by xamartin          #+#    #+#             */
/*   Updated: 2021/04/08 16:53:36 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "Node.hpp"
#include "Solver.hpp"

/*
** Constructor - Destructor Methods
*/

Solver::Solver()
{
	return ;
}

Solver::~Solver()
{
	return ;
}

/*
** Private Methods
*/

int		Solver::_generate_path_solution(std::shared_ptr<Node> resolve, std::map<size_t, std::shared_ptr<Node> > hash_dict)
{
	std::cout << "\n\n\n\n\nSolution founded" << std::endl;
	resolve->_("rg");
	std::exit(1);
	return (resolve->size + hash_dict.size());
}

int		Solver::_linear_conflict(const Node& s, const std::vector<int>& grid) const
{
	/*
		linear conflit - if 2 elements are not in the good order on the same line,
		it will need 2 moves to swap thoses elements
		x_g for element
		y_g for element neighbour
		x_s for element solution coord
		x_s for element neigbour solution coord
	*/
	int	x_g;
	int	y_g;
	int	x_s;
	int	y_s;
	int	lc = 0;

	for (int r = 0; r < s.size; r++)
	{
		for (int c = 0; c < s.size; c++)
		{
			// line
			if (c + 1 < s.size)
			{
				x_g = r * s.size + c;
				y_g = r * s.size + c + 1;
				x_s = this->get_number_index(s.length, s.grid, grid[x_g]);
				y_s = this->get_number_index(s.length, s.grid, grid[y_g]);
				if (grid[x_g] && grid[y_g] &&
					(int)(x_g % s.size) < (int)(y_g % s.size) &&
					(int)(x_s % s.size) > (int)(y_s % s.size) &&
					(x_g / s.size) == (y_g / s.size) &&
					(x_s / s.size) == (y_s / s.size))
					lc++;
			}

			// column
			if (r + 1 < s.size)
			{
				x_g = r * s.size + c;
				y_g = (r + 1) * s.size + c;
				x_s = this->get_number_index(s.length, s.grid, grid[x_g]);
				y_s = this->get_number_index(s.length, s.grid, grid[y_g]);
				// std::cout << "x_g | " << (x_g / s.size) << " - " << (x_g % s.size) << std::endl;
				// std::cout << "y_g | " << (y_g / s.size) << " - " << (y_g % s.size) << std::endl;
				// std::cout << "x_s | " << (x_s / s.size) << " - " << (x_s % s.size) << std::endl;
				// std::cout << "y_s | " << (y_s / s.size) << " - " << (y_s % s.size) << std::endl;
				if (grid[x_g] && grid[y_g] &&
					(int)(x_g / s.size) < (int)(y_g / s.size) &&
					(int)(x_s / s.size) > (int)(y_s / s.size) &&
					(x_g % s.size) == (y_g % s.size) &&
					(x_s % s.size) == (y_s % s.size))
					lc++;
			}
		}
	}
	return (lc * 2);
}

int 	Solver::_get_heuristic(const int a_pos, const int t_pos, const int size) const
{
	/*
	** Calculate the g between
	** actual number pos (a_pos) and target number pos (t_pos)
	** using predefined heurist function
	**
	** a_pos and t_pos coord are transformed from 1D coord to 2D
	*/
	return (this->heuristic((int)(a_pos / size), a_pos % size, (int)(t_pos / size), t_pos % size));
}

int		Solver::_calculate_f(const Node& s, const std::vector<int>& p_grid) const
{
	int	h = 0;

	for (int i = 1; i < s.length; i++)
		h += this->_get_heuristic(
			this->get_number_index(s.length, p_grid, i),
			this->get_number_index(s.length, s.grid, i),
			s.size);
	if (this->h == 5)
		h += this->_linear_conflict(s, p_grid);
	return (h);
}

/*
** Public Methods
*/

int		Solver::get_number_index(const int length, const std::vector<int>& g, const int nu) const
{
	for (int _ = 0; _ < length; _++)
		if (g[_] == nu)
			return (_);
	return length;
}

int 	Solver::a_star(Node& base, Node& s)
{
	std::hash<std::shared_ptr<Node> > node_hash;
	std::shared_ptr<Node> b = std::make_shared<Node>(base);
	std::map<size_t, std::shared_ptr<Node> > hash_dict; // save all nodes
	std::unordered_set<std::vector<int>, VectorHasher > closeset; // hash table of grid
	std::priority_queue< std::shared_ptr<Node>, std::vector<std::shared_ptr<Node> >, LowestF> openset; // priority queue
	
	openset.push(b);
	hash_dict[node_hash(b)] = b;
	while (openset.size())
	{
		std::shared_ptr<Node> p = openset.top();
		openset.pop();
		if (p->grid == s.grid)
			return (this->_generate_path_solution(p, hash_dict));
		if (closeset.find(p->grid) == closeset.end())
			closeset.insert(p->grid);
		hash_dict[node_hash(p)] = p;
		int	z = this->get_number_index(p->length, p->grid, 0);
		for (int i = 0; i < 4; i++)
		{
			std::shared_ptr<Node> p_ = std::make_shared<Node>(Node(p));
			p_->move(i, z);
			if (!p_->grid.empty() && closeset.find(p_->grid) == closeset.end())
			{
				p_->g = p->g + 1;
				p_->f = this->_calculate_f(s, p_->grid) + p_->g;
				p_->p_ptr = p;
				if (!hash_dict.count(node_hash(p_)))
					openset.push(p_);
				else
				{
					std::shared_ptr<Node> cpy = hash_dict[node_hash(p_)];
					if (p->g < cpy->g)
					{
						cpy->g = p->g;
						cpy->f = p->f;
						cpy->p_ptr = p->p_ptr;
					}
				}
			}
		}
	}
	return (1);
}
