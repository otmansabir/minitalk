# minitalk

Inter-process communication using UNIX signals (42 Project)

This repository contains a minimal messaging system between two processes: a server and a client. The client encodes a string into bits and sends it to the server using POSIX signals (`SIGUSR1` and `SIGUSR2`). The server decodes the stream of signals back into characters and prints the resulting message.

Repository: https://github.com/otmansabir/minitalk  
Language: C

## Features

- Server process that receives messages via signals and prints them to stdout
- Client process that sends a message to the server PID using only `SIGUSR1`/`SIGUSR2`
- Robust signal handling via `sigaction` with `SA_SIGINFO`
- Graceful handling of transmission pacing to avoid signal loss
- Clear usage and error messages

Bonus ideas (if implemented in this repository):
- Acknowledgment from server to client after each character or full message
- Support for extended characters/Unicode
- Additional utilities and improved UX

## Requirements

- POSIX-compliant system (Linux or macOS)
- `make` and a C compiler (e.g., `cc` or `gcc`)
- Standard C library and POSIX signal APIs

## Build

```sh
make
# or, if available:
make bonus
```

This typically builds two executables:
- `server`
- `client`

Clean targets:
```sh
make clean      # remove object files
make fclean     # remove objects and binaries
make re         # rebuild from scratch
```

## Usage

1) Start the server (in terminal 1):
```sh
./server
```
The server will print its PID, for example:
```
Server PID: 12345
```

2) Send a message from the client (in terminal 2):
```sh
./client 12345 "Hello, 42!"
```

3) The server prints the received message:
```
Hello, 42!
```

Common errors:
- Invalid or missing PID
- Empty message argument
- Server not running

The client displays a helpful usage message if arguments are incorrect:
```
Usage: ./client <server_pid> "<message>"
```

## How it works (high level)

- The client converts each character of the message to bits.
- It sends one signal per bit: e.g., `SIGUSR1` for 0 and `SIGUSR2` for 1 (or vice versa).
- The server handles signals via `sigaction` and reconstructs bytes from the incoming bit stream.
- When a full byte is assembled, the server writes the character to stdout.

Key system calls and functions you may find:
- `sigaction`, `sigemptyset`, `kill`, `getpid`, `pause`, `usleep`, `write`
- Optional: `printf`/`ft_printf` and small utility functions

## Project structure (typical)

Your layout may differ, but a common structure is:
```
.
├── Makefile
├── include/           # headers (e.g., minitalk.h)
├── src/
│   ├── server.c
│   ├── client.c
│   └── utils.c        # optional helpers
└── README.md
```

## Testing

- Send short and long messages
- Try edge cases: empty string, very long strings, mixed punctuation and spaces
- Validate behavior when PID is wrong or server isn’t running
- If bonus acknowledgments exist, confirm client waits and reacts correctly

## Notes

- Signal delivery is asynchronous; pacing (`usleep`) helps avoid missed signals.
- Always use `sigaction` (not `signal`) for reliable handling.
- Be careful with global state in signal handlers; keep handlers minimal.
- Printing inside a signal handler should use async-signal-safe functions (e.g., `write`).

## License

If applicable, add your preferred license here.

## Author

- otmansabir — https://github.com/otmansabir
