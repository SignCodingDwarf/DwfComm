#include "DwfUDPSock.h"
#include <chrono>

int main()
{
	dwf_comm::DwfUDPSock c(1666);
	c.setTimeout(500);

	int i=0;
	std::chrono::time_point<std::chrono::system_clock> t_start = std::chrono::system_clock::now();
	c.recv(i);
	std::chrono::time_point<std::chrono::system_clock> t = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed = t - t_start;
	std::cout << elapsed.count() * 1000.0 <<std::endl; // About 500ms 

	c.setTimeout(10200);
	t_start = std::chrono::system_clock::now();
	c.recv(i);
	t = std::chrono::system_clock::now();
	elapsed = t - t_start;
	std::cout << elapsed.count() * 1000.0 <<std::endl; // About 10200 ms

	c.setTimeout(); 
	c.recv(i); // Blocking (quit with ctrl-c)
	return 0;
}
