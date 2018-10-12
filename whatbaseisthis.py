import socket
import struct

HOST = "2018shell3.picoctf.com"
PORT = 15853

#flag: picoCTF{delusions_about_finding_values_3cc386de}

def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((HOST, PORT))

    for x in range(100):
        text = sock.recv(1024)
        print(text)
        if b'Please give me the' in text and b' as a word.' in text:
            begin = text.index(b'me the ') + len('me the ')
            end = text.index(b' as a word.')
            print(text[begin:end])
            if b' ' in text[begin:end]:
                m = text[begin:end].strip()
                l = m.split(b' ')
                word = []
                for x in l:
                    try:
                        word.append(chr(int(x.decode('utf-8'), base=2)))
                    except:
                        word.append(chr(int(x.decode('utf-8'), base=8)))
                word = ''.join(word).encode()
                print(word)
                sock.sendall(word + b'\n')
            else:
                word = bytearray.fromhex(text[begin:end].decode('utf-8')).decode()
                print(word)
                sock.sendall(word.encode() + b'\n')


    sock.close()

main()