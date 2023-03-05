#include "Socket.hpp"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h> // inet_ntoa
#include <netdb.h> // getprotobyname
#include <fcntl.h>
#include <unistd.h> // close
#include <stdlib.h> // exit

ft::Socket::Socket(){}
ft::Socket::Socket(int port)
	: __port_(port), __server_fd_(0), __kq_fd_(0){
		__srv_create();
		__eventPtr_[0] = &Socket::__send;
	}
ft::Socket::Socket(const Socket&){}

ft::Socket::~Socket(){
	for (iterator it = __client_fd_.begin(); it != __client_fd_.end() ; ++it) {
		__erase_client(*it);
	if (__server_fd_)
		close(__server_fd_);
	if (__kq_fd_)
		close(__server_fd_);
	}
}

ft::Socket& ft::Socket::operator=(const Socket&){
	return *this;
}

void ft::Socket::run(){
	//struct timespec timeout;
	const int max_event = 20; // CHECK
	struct kevent ev[max_event]; // CHECK

	while (true){
		int n = kevent(__kq_fd_, NULL, 0, ev, max_event, NULL);
		//std::cout << "epoll_wait return " << n << std::endl;
		for (int i = 0; i < n; i++){
			int event_fd = (int)(intptr_t)ev[i].udata; // CHECK : ident
			int evfilt = ev[i].filter;
			// CHECK : ev[i].flags & EV_EOF
			if (evfilt == EVFILT_READ){
				if (event_fd == __server_fd_)
					__handleAccept(event_fd);
				else
					__handleRead(event_fd);
			}
			// CHECK : else if (event_fd == EVFILT_WRITE)
			else{
				std::cout << "client #" << event_fd << " gone away (unknown event occured)" << std::endl;
				__erase_client(event_fd);
			}
		}
	}
}

void ft::Socket::__srv_create(){
	struct sockaddr_in sin;
	struct protoent *pe;

	pe = getprotobyname("tcp");
	if (pe == NULL)
		exit(1); // CHECK
	__server_fd_ = ::socket(PF_INET, SOCK_STREAM, pe->p_proto);
	if (__server_fd_ < 0)
		exit(1); // CHECK
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(__port_);
	if (bind(__server_fd_, (struct sockaddr*)&sin, sizeof(sin)) < 0)
		exit(1); // CHECK
	if (listen(__server_fd_, 42) < 0)
		exit(1); // CHECK
	__setNonBlock(__server_fd_);
	__kq_fd_ = kqueue();
	if (__kq_fd_ ==  -1)
		exit(1); // CHECK
	__updateEvent(__server_fd_);
}

void ft::Socket::__setNonBlock(int fd){
	if (fcntl(fd, F_SETFL, O_NONBLOCK) < 0)
		exit(1); // CHECK
}

void ft::Socket::__updateEvent(int fd){
	struct kevent ev;

	EV_SET(&ev, fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, (void *)(intptr_t)fd);
	if (kevent(__kq_fd_, &ev, 1, NULL, 0, NULL) < 0)
		exit(1); // CHECK
}

void ft::Socket::__handleAccept(int client_fd){
	struct sockaddr_in csin;
	socklen_t csin_len = sizeof(csin);
	int cfd = accept(client_fd, (struct sockaddr *)&csin, &csin_len);
	std::cout << "New client # " << cfd
	<< " from " << inet_ntoa(csin.sin_addr)
	<< ':' << ntohs(csin.sin_port) << std::endl;
	__insert_client(cfd);
	__setNonBlock(cfd);
	__updateEvent(cfd);
}

void ft::Socket::__handleRead(int client_fd){
	char buf[4096];
	int n = 0;
	n = recv(client_fd, buf, sizeof buf, 0);
	//buf[n] = 0;
	//if (errno == EAGAIN || errno == EWOULDBLOCK)
	//	return;
	if (n <= 0){
		__erase_client(client_fd);
		std::cout << "client #" << client_fd << " gone away" << std::endl;
	}
	else{
		std::cout << "read " << n << " bytes" << std::endl;
		// TODO : parsing
		//std::string cmd[3] = {
		//	"JOIN",
		//	"NICK",
		//	"CHANNEL"
		//};
		//for (int i = 0 ; i < 3 ; i++){
		//	if (cmd[i].find(buf) == 0){
		//		(this->*__eventPtr_[i])(buf);
		//		break ;
		//	}
		//}
		//(this->*__eventPtr_[0])(buf);
		for (iterator it = __client_fd_.begin(); it != __client_fd_.end() ; ++it) {
			send(*it, buf, n, 0);
		}
	}
}

void ft::Socket::__insert_client(int fd){
	if (fd < 0)
		exit(1); // CHECK
	std::pair<iterator, bool> r(__client_fd_.insert(fd));
	if (r.second == false) // CHECK
		std::cerr << "already inserted" << std::endl;
}

void ft::Socket::__erase_client(int fd){
	if (__client_fd_.erase(fd))
		close(fd);
	else // CHECK
		std::cerr << "already erased" << std::endl;
}

void ft::Socket::__send(const std::string &buf){
	for (iterator it = __client_fd_.begin(); it != __client_fd_.end() ; ++it) {
		send(*it, buf.c_str(), buf.length(), 0);
	}
}
