/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArgParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:55:37 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/17 16:46:33 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGPARSER_HPP
# define ARGPARSER_HPP

# include <string>
# include <iostream>

class ArgParser
{
	public:
		int			s_option;
		std::string	file_option;
		std::string	prog_name;

		ArgParser(const std::string &name);
		virtual ~ArgParser();

		void	print_usage() const;
		int		parse_command_line(int ac, char **av);
	private:
		bool	_is_number(const std::string &s) const;
		int		_check_file(std::string file_name) const;
};

#endif