import socket
import struct

HOST = "2018shell3.picoctf.com"
PORT = 6903

directory = [
b'blackmail',
b'executables',
b'passwords',
b'photos',
b'secret'
]


def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((HOST, PORT))
    for x in range(20):
        print(sock.recv(1024).decode('utf-8'))

    sock.sendall(b"cd secret\n")
    sock.sendall(b"ls\n")
    #sock.sendall(b"cd intel_1\n")
    #sock.sendall(b"ls\n")
    sock.sendall(b"rm intel_1\n")
    sock.sendall(b"rm intel_2\n")
    sock.sendall(b"rm intel_3\n")
    sock.sendall(b"rm intel_4\n")
    sock.sendall(b"rm intel_5\n")

    sock.sendall(b"echo 'Drop it in!' \n")
    sock.sendall(b'cd ..\n')
    sock.sendall(b'cd executables\n')
    sock.sendall(b'ls\n')

    sock.sendall(b'cat dontLookHere\n')
    sock.sendall(b'./dontLookHere\n')

    for x in range(100):
        print(sock.recv(1024).decode('utf-8'))

    sock.close()

main()