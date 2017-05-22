#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    struct addrinfo* result;
    struct addrinfo* res;
    char ipstr[INET_ADDRSTRLEN];
    int error;

    error = getaddrinfo("www.facebook.com", NULL, NULL, &result);
    if (error != 0) {
        if (error == EAI_SYSTEM) {
            perror("getaddrinfo");
        } else {
            fprintf(stderr, "error in getaddrinfo: %s\n", gai_strerror(error));
        }
        exit(EXIT_FAILURE);
    }

    for (res = result; res != NULL; res = res->ai_next) {
        struct in_addr  *addr;
        if (res->ai_family == AF_INET) {
            struct sockaddr_in *ipv = (struct sockaddr_in *)res->ai_addr;
            addr = &(ipv->sin_addr);
        }
        else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)res->ai_addr;
            addr = (struct in_addr *) &(ipv6->sin6_addr);
        }
        inet_ntop(res->ai_family, addr, ipstr, sizeof ipstr);
    }
    printf("Address: %s\n", ipstr);

    freeaddrinfo(result);
    return 0;
}
