// udp_client.c
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
    struct sockaddr_in server_addr;
    socklen_t addr_len;
    struct Numbers nums, result;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    nums.a = 15;
    nums.b = 20;

    addr_len = sizeof(server_addr);

    sendto(sockfd, &nums, sizeof(nums), 0, (struct sockaddr *)&server_addr, addr_len);

    recvfrom(sockfd, &result, sizeof(result), 0, (struct sockaddr *)&server_addr, &addr_len);

    printf("Original: a=%d, b=%d\n", nums.a, nums.b);
    printf("After swap: a=%d, b=%d\n", result.a, result.b);

    close(sockfd);
    return 0;
}
