/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:16:15 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/29 14:23:59 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUZZLE_HPP
# define PUZZLE_HPP

# include <chrono>
# include <random>
# include <vector>
# include <algorithm>

# include "ArgParser.hpp"

#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3

class Puzzle
{
	public:
		typedef void (Puzzle::*mptr)(const int z);
	
		// variables
		int		size;
		int		length;
		int		f;
		int		g;
		std::vector<int> grid;
		void	*p_ptr; // parent ptr | 0x0 if normal puzzle
		// 	Puzzle a = ((Puzzle *)this->p_ptr);

		// constructors - destructor
		Puzzle(const int s);
		Puzzle(Puzzle *obj);
		Puzzle(const int s, const int f_, const int g_, std::vector<int> grid_, void *p);
		virtual ~Puzzle(void);

		// operators
		bool operator()(const Puzzle& p) const;

		// Methods
		void	_(const std::string &name) const;
		mptr 	f_move[4] = {&Puzzle::_move_left, &Puzzle::_move_up, &Puzzle::_move_right, &Puzzle::_move_down};
		void	move(int i, const int z);

	private:
		void	_move_left(const int z);
		void	_move_up(const int z);
		void	_move_right(const int z);
		void	_move_down(const int z);


};

#endif