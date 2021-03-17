/**
 * Creates a socket for the server and makes it passive such that
 * we can wait for connections on it later.
 */
int server_listen(server_t* server);


/**
 * Accepts new connections and then prints `Hello World` to
 * them.
 */
int server_accept(server_t* server);


/**
 * Main server routine.
 *
 *      -       instantiates a new server structure that holds the
 *              properties of our server;
 *      -       creates a socket and makes it passive with
 *              `server_listen`;
 *      -       accepts new connections on the server socket.
 *
 */
int
main()
{
	int err = 0;
	server_t server = { 0 };

	err = server_listen(&server);
	if (err) {
		printf("Failed to listen on address 0.0.0.0:%d\n", 
                        PORT);
		return err;
	}

	for (;;) {
		err = server_accept(&server);
		if (err) {
			printf("Failed accepting connection\n");
			return err;
		}
	}

	return 0;
}
// The `socket(2)` syscall creates an endpoint for communication
	// and returns a file descriptor that refers to that endpoint.
	//
	// It takes three arguments (the last being just to provide greater
	// specificity):
	// -    domain (communication domain)
	//      AF_INET              IPv4 Internet protocols
	//
	// -    type (communication semantics)
	//      SOCK_STREAM          Provides sequenced, reliable,
	//                           two-way, connection-based byte
	//                           streams.
	err = (server->listen_fd = socket(AF_INET, SOCK_STREAM, 0));
	if (err == -1) {
		perror("socket");
		printf("Failed to create socket endpoint\n");
		return err;
	}
	OCKET(2)      Linux Programmer's Manual          SOCKET(2)

NAME
       socket - create an endpoint for communication

SYNOPSIS
       int socket(int domain, int type, int protocol);

DESCRIPTION
       socket()  creates  an  endpoint for communication and 
       returns a file descriptor that refers to that endpoint.

       The file descriptor returned by a successful call will be 
       the lowest-numbered file descriptor  not  currently open 
       for the process.
// The `socket(2)` syscall creates an endpoint for communication
	// and returns a file descriptor that refers to that endpoint.
	//
	// It takes three arguments (the last being just to provide greater
	// specificity):
	// -    domain (communication domain)
	//      AF_INET              IPv4 Internet protocols
	//
	// -    type (communication semantics)
	//      SOCK_STREAM          Provides sequenced, reliable,
	//                           two-way, connection-based byte
	//                           streams.
	err = (server->listen_fd = socket(AF_INET, SOCK_STREAM, 0));
	if (err == -1) {
		perror("socket");
		printf("Failed to create socket endpoint\n");
		return err;
	}
# Capture the PID of the server process that only
# calls `socket(2)` and the `pause(2)` to wait for
# a signal indefinitely.
SERVER_PROC=$(pgrep server.out)


# List the open files of this process but filter
# out those that do not contain `sock` in the 
# line.
lsof | ag $SERVER_PROC | ag sock
COMMAND    PID    TYPE    NODE  NAME
server.out 8824   sock   34368  protocol: TCP


# Check out what file descriptors are assigned
# to our process by inspecting the `proc` virtual
# filesystem.
ls -lah /proc/$SERVER_PROC/fd
 .
 ..
 0 -> /dev/pts/0
 1 -> /dev/pts/0
 2 -> /dev/pts/0
 3 -> socket:[34368]
err = (server->listen_fd = socket(AF_INET, SOCK_STREAM, 0));
        // ...

        err = write(server->listen_fd, "hey", 3);
        if (err == -1) {
                perror("write");
                printf("failed to write\n");
                return err;
        }
strace ./server.out
socket(AF_INET, SOCK_STREAM, IPPROTO_IP) = 3
write(3, "hey", 3)                      = -1 EPIPE (Broken pipe)
--- SIGPIPE {si_signo=SIGPIPE, si_code=SI_USER, si_pid=11008, si_uid=1001} ---
+++ k# Check that `lsof` identifies our socket listening on
# port 8080
lsof -i:8080
COMMAND    TYPE DEVICE NAME
server.out IPv4 38593  TCP *:http-alt (LISTEN)

# Check that `ss` properly recognizes our socket as `listen`
ss \
        --listening \
        --numeric \
        --tcp  | ag 8080
LISTEN     0      128          *:8080                     *:*  illed by SIGPIPE +++
 # In one terminal, start the server.
# ps.: I modified the code to have the
# backlog set to 4.
./server.out

# In another terminal, start a handful of 
# connections using telnet.

for i in $(seq 1 10); \
        do sleep 1; \
        telnet localhost 8080 & \
done

[1] 11696                       # <<<<< worked
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.

telnet localhost 8080
[2] 11698                       # <<<<< worked
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.

telnet localhost 8080
[3] 11700                       # <<<<< worked
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.

telnet localhost 8080
[4] 11702                       # <<<<< worked
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.

telnet localhost 8080
[5] 11704                       # <<<<< worked
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.


# From now on, the backlog got to its maximum, 
# so it won't accept more connections.

telnet localhost 8080
[6] 11707
Trying 127.0.0.1...
[7] 11709
Trying 127.0.0.1...
[8] 11711
Trying 127.0.0.1...
[9] 11713
Trying 127.0.0.1...
[10] 11715
Trying 127.0.0.1...
int
server_accept(server_t* server)
{
	int err = 0;
	int conn_fd;
	socklen_t client_len;
	struct sockaddr_in client_addr;

	client_len = sizeof(client_addr);

	err =
	  (conn_fd = accept(
	     server->listen_fd, (struct sockaddr*)&client_addr, &client_len));
	if (err == -1) {
		perror("accept");
		printf("failed accepting connection\n");
		return err;
	}

	printf("Client connected!\n");

	err = close(conn_fd);
	if (err == -1) {
		perror("close");
		printf("failed to close connection\n");
		return err;
	}

	return err;
}
