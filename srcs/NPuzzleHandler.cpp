/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NPuzzleHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:16:15 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/17 17:23:34 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "NPuzzleHandler.hpp"

/*
** Constructor - Destructor Methods
*/

NPuzzleHandler::NPuzzleHandler(const int s, const std::string &file_name) : puzzle_file(file_name)
{
	p = new Puzzle(s);
	solution = new Puzzle(s);
}

NPuzzleHandler::~NPuzzleHandler(void)
{
	delete p;
	delete solution;
}

/*
** Private Methods
*/

int	NPuzzleHandler::_parse_file()
{
	std::cout << "Exit Parser - puzzle file open and parsed" << std::endl;
	return (0);
}

int NPuzzleHandler::_generate_puzzle()
{
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine e(seed);
	std::generate(this->p->grid.begin(), this->p->grid.end(), [n = 0] () mutable { return n++; });
	std::shuffle(std::begin(this->p->grid), std::end(this->p->grid), e);
	this->p->_();
	std::cout << "Exit Parser - puzzle genrated" << std::endl;
	return (1);
}

void NPuzzleHandler::_generate_solution()
{
	int nu = 1;
	int sr = 0;
	int sc = 0;
	int r = this->solution->size - 1;
	int c = this->solution->size - 1;

    while(sr <= r && sc <= c)
	{
        for (int i = sc; i <= c; i++)
            this->solution->grid[sr * this->solution->size + i] = nu++;
        sr++;
        for (int i = sr; i <= r; i++)
            this->solution->grid[i * this->solution->size + c] = nu++;
        c--;
        if (sr <= r)
		{
            for (int i = c; i >= sc; i--)
                this->solution->grid[r * this->solution->size + i] = nu++;
            r--;
        }
        if (sc <= c)
		{
            for (int i = r; i >= sr; i--)
                this->solution->grid[i * this->solution->size + sc] = nu++;
            sc++;
        }
    }
	this->solution->_();
	this->solution->grid[this->get_number_index(this->p->grid, this->p->length)] = 0;
	std::cout << "solution" << std::endl;
	this->solution->_();
}

/*
** Public Methods
*/

int NPuzzleHandler::parser()
{
	this->_generate_solution();
	std::cout << "Enter Parser" << std::endl;
	if (!this->puzzle_file.empty())
		return (this->_parse_file());
	else
		return this->_generate_puzzle();
}

int	NPuzzleHandler::solve()
{
	std::cout << "Enter Solve" << std::endl;
	this->a_star(this->p);
	std::cout << "Exit Solve" << std::endl;
	return (0);
}
