/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:16:15 by xamartin          #+#    #+#             */
/*   Updated: 2021/04/06 10:21:52 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

# include <chrono>
# include <random>
# include <vector>
# include <unordered_set>
# include <algorithm>

# include "ArgParser.hpp"

#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3

class Node
{
	public:
		typedef void (Node::*mptr)(const int z);
	
		// variables
		int		size;
		int		length;
		int		f;
		int		g;
		std::vector<int> grid;
		void	*p_ptr; // parent ptr | 0x0 if normal Node
		// 	Node a = ((Node *)this->p_ptr);

		// constructors - destructor
		Node(const int s);
		Node(Node *obj);
		Node(const int s, const int f_, const int g_, std::vector<int> grid_, void *p);
		virtual ~Node(void);

		// operators
		bool operator()(const Node& p) const;

		// Methods
		void	_(const std::string &name) const;
		mptr 	f_move[4] = {&Node::_move_left, &Node::_move_up, &Node::_move_right, &Node::_move_down};
		void	move(int i, const int z);

	private:
		void	_move_left(const int z);
		void	_move_up(const int z);
		void	_move_right(const int z);
		void	_move_down(const int z);


};

#endif