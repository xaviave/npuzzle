/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Puzzle.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:16:15 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/22 13:49:17 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUZZLE_HPP
# define PUZZLE_HPP

# include <chrono>
# include <random>
# include <algorithm>

# include "ArgParser.hpp"

#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3

class Puzzle
{
	public:
		typedef std::vector<int>	(Puzzle::*mptr)(const int z, std::vector<int> grid);
	
		// variables
		int					size;
		int					length;
		int					f;
		int					g;
		std::vector<int>	grid;
		void				*p_ptr; // parent ptr | 0x0 if normal puzzle
		// 	Puzzle a = ((Puzzle *)this->p_ptr);

		// constructor - destructor
		Puzzle(const int s);
		Puzzle(Puzzle *obj);
		Puzzle(const int s, const int f_, const int g_, const std::vector<int> grid_, void *p);
		virtual ~Puzzle(void);

		// Override methods

		// Methods
		void						_(const std::string &name) const;
		mptr 						f_move[4] = {&Puzzle::_move_left, &Puzzle::_move_up, &Puzzle::_move_right, &Puzzle::_move_down};
		std::vector<int>			move(int i, const int z);
	private:
		std::vector<int>			_move_left(const int z, std::vector<int> grid);
		std::vector<int>			_move_up(const int z, std::vector<int> grid);
		std::vector<int>			_move_right(const int z, std::vector<int> grid);
		std::vector<int>			_move_down(const int z, std::vector<int> grid);		
};

#endif