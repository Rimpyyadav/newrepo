// udp_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

struct Numbers {
    int a;
    int b;
};

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len;
    struct Numbers nums, swapped;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(1);
    }

    addr_len = sizeof(client_addr);
    recvfrom(sockfd, &nums, sizeof(nums), 0, (struct sockaddr *)&client_addr, &addr_len);

    // Swap values
    swapped.a = nums.b;
    swapped.b = nums.a;

    sendto(sockfd, &swapped, sizeof(swapped), 0, (struct sockaddr *)&client_addr, addr_len);

    printf("Received: a=%d, b=%d | Sent back: a=%d, b=%d\n", nums.a, nums.b, swapped.a, swapped.b);

    close(sockfd);
    return 0;
}

//gcc udp_server.c -o udp_server
//gcc udp_client.c -o udp_client