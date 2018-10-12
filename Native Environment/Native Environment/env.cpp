#include <cstdio>
#include <string>
#include <iostream>

#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <sstream>

typedef uint8_t byte;

const std::vector<byte> string_to_bytes(const std::string & array_of_bytes)
{
	std::vector<byte> data;
	std::string array_data(array_of_bytes);

	array_data.erase(std::remove(array_data.begin(), array_data.end(), ' '), array_data.end());
	if ((array_data.size() % 2) || !array_data.size())
	{
		return data;
	}

	data.reserve(array_data.size() / 2);

	std::mt19937 mt(static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count()));
	std::uniform_int_distribution<int32_t> dist(0, 15);
	char hexadecimal_character[] = "0123456789ABCDEF";

	for (size_t n = 0; n < array_data.size(); ++n)
	{
		if (!isxdigit(array_data.at(n)))
		{
			array_data.at(n) = hexadecimal_character[dist(mt)];
		}
	}

	for (size_t i = 0; i < array_data.size(); i += 2)
	{
		std::stringstream ss;
		ss << std::hex << array_data.at(i) << array_data.at(i + 1);
		data.push_back(static_cast<uint8_t>(std::stoi(ss.str(), nullptr, 16)));
	}

	return data;
}

__declspec(dllexport, naked) int assembly_2()
{
	__asm
	{
		push   	ebp
		mov    	ebp, esp
		sub    	esp, 0x10
		mov    	eax, DWORD PTR[ebp + 0xc]
		mov 	dword ptr [ebp - 0x4], eax
		mov    	eax, DWORD PTR[ebp + 0x8]
		mov		dword ptr[ebp - 0x8], eax
		jmp    	part_b
		
		part_a :
		add    	DWORD PTR[ebp - 0x4], 0x1
		add	DWORD PTR[ebp + 0x8], 0xa9
		
		part_b :
			cmp    	DWORD PTR[ebp + 0x8], 0x3923
			jle    	part_a
			mov    	eax, DWORD PTR[ebp - 0x4]
			mov	esp, ebp
			pop	ebp
			ret
	}
}




int __cdecl assembly_2_disasm(signed int a1, int a2)
{
	int v3; // [esp+Ch] [ebp-4h]

	v3 = a2;
	while (a1 <= 14627)
	{
		++v3;
		a1 += 169;
	}
	return v3;
}

__declspec(dllexport, naked) int assembly_3()
{
	__asm
	{
		push   	ebp
		mov    	ebp, esp
		mov	eax, 0x27
		xor al, al
		mov	ah, BYTE PTR[ebp + 0xb]
		sal	ax, 0x10
		sub	al, BYTE PTR[ebp + 0xc]
		add	ah, BYTE PTR[ebp + 0xf]
		xor ax, WORD PTR[ebp + 0x12]
		mov	esp, ebp
		pop	ebp
		ret
	}
}

int assembly_3_disasm()
{
	//asm3(0xfac0f685,0xe0911505,0xaee1f319)
	unsigned long eax_val = 0;
	__asm
	{
		push 0xaee1f319
		push 0xe0911505
		push 0xfac0f685
		call assembly_3
		mov eax_val, eax
	}

	return eax_val;
}


int quackme_buffer[] = {
0x29,
0x6,
0x16,
0x4F,
0x2B,
0x35,
0x30,
0x1E,
0x51,
0x1B,
0x5B,
0x14,
0x4B,
0x8,
0x5D,
0x2B,
0x5C,
0x10,
0x6,
0x6,
0x18,
0x45,
0x51,
0x0,
0x5D,
0x0
};

std::string greetingMessage = "You have now entered the Duck Web, and you're in for a honkin' good time.\nCan you figure out my trick?";
std::string do_magic(char *s, std::string &mask)
{
	signed int input_size; // [esp+18h] [ebp-10h]
	void *v5; // [esp+1Ch] [ebp-Ch]

	input_size = strlen(s);
	v5 = malloc(input_size + 1);
	if (!v5)
	{
		puts("malloc() returned NULL. Out of Memory\n");
		exit(-1);
	}
	memset(v5, 0, input_size + 1);
	int v1 = 0;
	
	for (int i = 0; ; ++i)
	{
		if (i >= input_size)
			break;
		if (greetingMessage.at(i) == (quackme_buffer[i] ^ (unsigned __int8)s[i]))
		{
			++v1;
			mask.at(i) = s[i];
		}
	
		if (v1 == 25)
			puts("You are winner!");
	}
	return mask;
}

void quackme()
{
	std::string mask = "@@@@@@@@@@@@@@@@@@@@@@@@@";
	for (char a = 'a'; a <= 'z'; ++a)
	{
		std::string text = "";
		for (size_t n = 0; n < 25; ++n)
		{
			text.push_back(a);
		}

		std::cout << a << ": " << do_magic((char*)text.c_str(), mask) << std::endl;
	}

	for (char a = 'A'; a <= 'Z'; ++a)
	{
		std::string text = "";
		for (size_t n = 0; n < 25; ++n)
		{
			text.push_back(a);
		}

		std::cout << a << ": " << do_magic((char*)text.c_str(), mask) << std::endl;
	}

	for (char a = '0'; a <= '9'; ++a)
	{
		std::string text = "";
		for (size_t n = 0; n < 25; ++n)
		{
			text.push_back(a);
		}

		std::cout << a << ": " << do_magic((char*)text.c_str(), mask) << std::endl;
	}

	std::cout << mask << std::endl;
}

int __cdecl rol4(char a1)
{
	return (unsigned __int8)_rotl(a1, 4);
}

int __cdecl ror8(char a1)
{
	return (unsigned __int8)_rotr(a1, 8);
}

//std::string encrypted = "11 80 20 E0 22 53 72 A1 01 41 55 20 A0 C0 25 E3 35 40 55 30 85 55 70 20 C1";
//auto encrypted_buffer = string_to_bytes(encrypted);
std::vector<byte> encrypted_buffer = { 0x11, 0x80, 0x20, 0xE0, 0x22, 0x53, 0x72, 0xA1, 0x01, 0x41, 0x55, 0x20, 0xA0, 0xC0, 0x25, 0xE3, 0x35, 0x40, 0x55, 0x30, 0x85, 0x55, 0x70, 0x20, 0xC1 };

char __cdecl encrypt(char s)
{
	char v1 = rol4(s);
	s = ror8((char)(v1 ^ 0x16));
	return s;
}

void quackmeup()
{
	std::string mask = "@@@@@@@@@@@@@@@@@@@@@@@@@";
	for (int n = 0; n < 25; ++n)
	{
		for (char a = '0'; a <= '9'; ++a)
		{
			if (encrypted_buffer.at(n) == encrypt(a))
			{
				mask.at(n) = a;
			}
			printf("%d %d - ", encrypted_buffer.at(n), encrypt(a));
		}
	}

	std::cout << mask << std::endl;

	
}



int main()
{
	//printf("%d", assembly_2_disasm(0x8, 0x21));
	//printf("%d", assembly_3_disasm());
	quackmeup();
	return 0;
}