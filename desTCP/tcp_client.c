// tcp_client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    int numbers[6] = {5, 10, 2, 4, 7, 3};
    int sorted[6];

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation error");
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IP address from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address / Address not supported");
        exit(1);
    }

    // Connect
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(1);
    }

    // Send numbers
    send(sock, numbers, sizeof(numbers), 0);

    // Receive sorted numbers
    read(sock, sorted, sizeof(sorted));

    printf("Sorted numbers (Descending): ");
    for (int i = 0; i < 6; i++) {
        printf("%d ", sorted[i]);
    }
    printf("\n");

    close(sock);
    return 0;
}
