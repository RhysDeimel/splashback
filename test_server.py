import argparse
import socket

MAX_BYTES = 655355


def server(port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind(('', port))
    print('Listening at {}'.format(sock.getsockname()))
    while True:
        data, address = sock.recvfrom(MAX_BYTES)
        text = data.decode('ascii')
        print('The client at {} says {!r}'.format(address, text))


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Send and receive UDP locally'
    )
    parser.add_argument('-p', metavar='PORT', type=int, default=8125,
                        help='UDP port (default 8125)')
    args = parser.parse_args()

    server(args.p)
