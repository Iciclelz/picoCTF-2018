import socket
import struct

HOST = "2018shell3.picoctf.com"
PORT = 37542

#flag: picoCTF{almost_like_mario_a6975cdb}

def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((HOST, PORT))

    for x in range(100):
        print(sock.recv(2048).decode('utf-8'))

    sock.close()

main()