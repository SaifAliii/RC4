#include <iostream>
#include <string>
using namespace std;
int S[256];
int K[256];

void initializeS_Array()
{
	for (int i = 0; i < 255; i++)
	{
		S[i] = i;
	}
}

void initializeK_Array(string key)
{
	int j = 0;
	for (int i = 0; i < 256; i++)
	{
		K[i] = key[j++];
		if (j == key.length())
		{
			j = 0;
		}
	}
}

void keyScheduling()
{
	int j = 0;
	for (int i = 0; i < 256; i++)
	{
		j = (j + S[i] + (K[i] - '0')) % 256;
		swap(S[i], S[j]);
	}

}
string reverseString(string str)
{
	int length = str.length();
	int endingIndex;
	char temp;
	if (length % 2 == 0)
	{
		endingIndex = length - 1;
	}
	else
	{
		endingIndex = length;
	}
	for (int i = 0; i < length / 2; i++, endingIndex--)
	{
		temp = str[i];
		str[i] = str[endingIndex];
		str[endingIndex] = temp;
	}

	return str;
}

string convertIntoBinary(int val)
{
	string binary;
	int remainder;
	if (val == 0)
	{
		return "00";
	}
	while (val != 0)
	{
		remainder = val % 2;
		if (remainder == 0)
		{
			binary += '0';
		}
		else
		{
			binary += '1';
		}
		val = val / 2;
	}
	if (binary.length() < 2)
	{
		binary = '0' + binary;
	}

	binary = reverseString(binary);
	return binary;
}

string encryptionDecryption(string text)
{
	string keyStream;
	int i = 0;
	int j = 0;
	int t;
	string resultingText = "";
	string kStream = "";
	for (int k = 0; k < text.length(); k++)
	{
		i = (i + 1) % 256;
		j = (j + S[i]) % 256;
		swap(S[i], S[j]);
		t = (S[i] + S[j]) % 256;
		keyStream[k] = S[t];
		kStream = convertIntoBinary(keyStream[k]);
		resultingText += (text[k] ^ keyStream) + '0';
	}
	return resultingText;
}

int main()
{
	string key;
	cout << "Enter Key: ";
	cin >> key;
	string plainText, cipherText, decryptedText;
	cout << "Enter the plain text: ";
	cin >> plainText;
	initializeS_Array();
	initializeK_Array(key);
	keyScheduling();
	cipherText = encryptionDecryption(plainText);
	cout << "cipher Text is: " << cipherText << endl;
	decryptedText = encryptionDecryption(cipherText);
	cout << "decrypted text is: " << decryptedText << endl;
	

	return 0;
}