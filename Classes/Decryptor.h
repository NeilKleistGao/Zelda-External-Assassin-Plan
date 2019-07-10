#pragma once

#include "base/CCData.h"
#include "xxtea/xxtea.h"

class Decryptor {
public:
	static void decrypt(cocos2d::Data *data)
	{
		const char* key = "2018212027";
		const char* sign = "XXTEA";
		unsigned char* dataBytes = data->getBytes();
		ssize_t dataLen = data->getSize();
		ssize_t signLen = strlen(sign);
		ssize_t keyLen = strlen(key);

		if (strncmp(sign, (const char*)dataBytes, signLen) != 0)
		{
			return;
		}
		xxtea_long retLen = 0;
		unsigned char* retData = xxtea_decrypt(dataBytes + signLen, dataLen - signLen, (unsigned char*)key, keyLen, &retLen);
		data->fastSet(retData, retLen);
	}
};


