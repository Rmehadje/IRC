/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:20:28 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/06/14 12:20:42 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Lib.hpp"

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << RED << "Please enter all needed Arguments!" << DEFAULT << std::endl;
		std::cerr << "How to use : ./IRC <port> <password>" << std::endl;
		return 1;
	}
	if (PortChecker(argv[1]) == 1)
		return 1;
	Server server(atoi(argv[1]), argv[2]);
	while (server.getStatus() == true)
	{
		server.init();
	}
	return 0;
}