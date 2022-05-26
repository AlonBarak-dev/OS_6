// Client side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 3490


int main(int argc, char const* argv[])
{
	int sock = 0, valread = 0;
	struct sockaddr_in serv_addr;
	char buffer[1024] = { 0 };
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text to binary
	// form
	const char * ip_address = argv[1];
	if (inet_pton(AF_INET, ip_address, &serv_addr.sin_addr)
		<= 0) {
		printf(
			"\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr*)&serv_addr,
				sizeof(serv_addr))
		< 0) {
		printf("\nConnection Failed \n");
		return -1;
	}
    char command[1024] = {0};
	sleep(3);
    while (1)
    {
        printf("Please enter a command:\n");
        fgets(command,1024 ,stdin);
        send(sock, command, strlen(command), 0);
        if (strncmp(command, "TOP",3) == 0)
        {
			bzero(command, 1024);
            recv(sock, command, 1024,0);
			if (strcmp(command, "-") == 0)
			{
				printf("OUTPUT:\n");
			}
			else{
				printf("OUTPUT:%s\n", command);
			}
        }
		else if(strncmp(command, "EXIT", 4) == 0){
			break;
		}
        bzero(command, 1024);
		sleep(1);
    }
    
	return 0;
}
