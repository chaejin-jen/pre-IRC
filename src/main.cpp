#include <iostream>
#include <string>
#include "Socket.hpp"

#include <set>

void puterr_exit(std::string err_str);
size_t valid_port(std::string port_str);

int main(int argc, char *argv[]){
	if (argc != 2)
		puterr_exit("Error: arguments\n[hint] ./ft_irc <port(1025 ~ 65535)>");
	ft::Socket sckt(valid_port(argv[1]));
	sckt.run();
	return 0;
}

void puterr_exit(std::string err_str){
	std::cerr << err_str << std::endl;
	exit(1);
}

size_t valid_port(std::string port_str){
	double d;
	char *back;

	if (port_str.find('.') != std::string::npos)
		puterr_exit("Error: arguments\n[hint] ./ft_irc <port(1025 ~ 65535)>");

	d = std::strtod(port_str.c_str(), &back);
	// port 데이터의 목적지가 어떤 프로그램인지 구분
	// [0 ~ 1023] well-known port
	// [1024] reserved but not using
	// [1025 ~ 65535] 랜덤포트라고 해서 클라이언트 측의 송신 포트로 사용됨
	if (*back || d < 1025 | d > 65535){
		puterr_exit("Error: arguments\n[hint] ./ft_irc <port(1025 ~ 65535)>");
	}
	return d;
}
