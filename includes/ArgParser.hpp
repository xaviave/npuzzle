/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ArgParser.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xamartin <xamartin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 14:55:37 by xamartin          #+#    #+#             */
/*   Updated: 2021/03/16 15:03:38 by xamartin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGPARSER_HPP
# define ARGPARSER_HPP

# include <string>
# include <iostream>

class ArgParser
{
	public:
		std::string	prog_name;
		
		ArgParser();
		ArgParser(std::string name);
		virtual ~ArgParser();

		void	print_usage() const;
		int		check_file(std::string file_name);
		int		parse_command_line(int ac, char **av);
};

#endif