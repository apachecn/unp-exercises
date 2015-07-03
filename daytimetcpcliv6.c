/*
 * =============================================================================
 *
 *       Filename:  daytimetcpcliv6.c
 *
 *    Description:  time get client based TCP and ipv6. figure 1-6, page 10
 *
 *        Version:  1.0
 *        Created:  03/01/2015 08:56:25 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =============================================================================
 */

#include "unp.h"

int main(int argc, char **argv)
{
	int	sockfd, n;
	char	recvline[MAXLINE + 1];
	struct	sockaddr_in6 servaddr;

	if (argc != 2)
		err_quit("usage: a.out <IPaddress>");

	if ((sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0)
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin6_family = AF_INET;
	servaddr.sin6_port   = htons(13); /* daytime server */
	if (inet_pton(AF_INET6, argv[1], &servaddr.sin6_addr) <= 0)
		err_quit("inet_pton error for %s", argv[1]);

	if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
		err_sys("connect error");

	while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;
		if (fputs(recvline, stdout) == EOF)
			err_sys("fputs error");
	}
	if (n < 0)
		err_sys("read error");
	exit(0);
}
