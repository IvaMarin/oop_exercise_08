/* 
 *  Мариничев И. А.
 *  М8О-208Б-19
 *  github.com/IvaMarin/oop_exercise_08
 *  Вариант 13:
 *  Фигура:    
 *  - ромб
 *  - пятиугольник 
 *  - шестиугольник
 */

#include <iostream>
#include <queue>
#include <ctime>
#include <sstream>

#include "factory.hpp"
#include "server.hpp"

void Menu() {
	std::cout << "1. Add rhombus" << std::endl;
	std::cout << "2. Add pentagon" << std::endl;
	std::cout << "3. Add hexagon" << std::endl;
	std::cout << "4. Help" << std::endl;
	std::cout << "0. Exit" << std::endl << std::endl;
}

using server_t = server<std::shared_ptr<Figure>>;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "Syntax: ./oop_exercise_08 <buffer_size>" << std::endl;
		return 1;
	}

	if (std::stoi(argv[1]) <= 0) {
		std::cout << "Incorrect buffer size" << std::endl;
		return 2;
	}

	size_t buf_size = std::stoul(argv[1]);

	// adding subscribers (handler functions)
	server_t::Get().RegisterSubscriber([](const std::shared_ptr<Figure> fig) {
		fig->Print();
		});

	server_t::Get().RegisterSubscriber([](const std::shared_ptr<Figure> fig) {
		fig->PrintToFile(server_t::Get().GetFD());
		});

	// starting handler
	std::thread th([buf_size]() {
		server_t::Get().Run(buf_size);
		});

	Menu();

	int cmd;

	std::cout << "Select option: ";
	while (true) {
		std::cin >> cmd;
		if (cmd == 1) {
			std::cout << "Enter coords of the center and lengths of diagonals" << std::endl;
			std::shared_ptr<Figure> fig = factory::Create((FigureType)cmd);
			server_t::Get().Publish(fig);
			std::cout << "Successfully added" << std::endl;
		}
		else if (cmd == 2) {
			std::cout << "Enter coords of the center and length of radius" << std::endl;
			std::shared_ptr<Figure> fig = factory::Create((FigureType)cmd);
			server_t::Get().Publish(fig);
			std::cout << "Successfully added" << std::endl;
		}
		else if (cmd == 3) {
			std::cout << "Enter coords of the center and length of side" << std::endl;
			std::shared_ptr<Figure> fig = factory::Create((FigureType)cmd);
			server_t::Get().Publish(fig);
			std::cout << "Successfully added" << std::endl;
		} else if (cmd == 4) {
            Menu();
		}
		else if (cmd == 0) {
			server_t::Get().Stop();
			break;
		}
		else {
			std::cout << "Incorrect cmd" << std::endl;
		}
		std::cout << std::endl;
    	std::cout << "Select option: "; // Repeat input
	}

	th.join();
	
}