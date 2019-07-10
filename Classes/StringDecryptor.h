#pragma once

#include <iostream>
#include <cstring>

class StringDecryptor {
public:
	static void decrypt(std::string& data)
	{
		const char* key = "2018212027";
		size_t len = strlen(key);

		for (int i = 0; i < data.length(); i++) {
			data[i] ^= key[i % len];
		}
	}
};
