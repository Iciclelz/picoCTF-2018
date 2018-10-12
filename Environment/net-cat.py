import socket

HOST = "2018shell3.picoctf.com"
PORT = 49387

#flag: picoCTF{NEtcat_iS_a_NEcESSiTy_8b6a1fbc}

def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((HOST, PORT))
    print(sock.recv(1024))
    print(sock.recv(1024))
    sock.close()

main()