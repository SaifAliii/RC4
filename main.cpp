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
		j = (j + S[i] + K[i]) % 256;
		swap(S[i], S[j]);
	}

}

string encryptionDecryption(string text,string key)
{
	initializeS_Array();
	initializeK_Array(key);
	keyScheduling();
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
		keyStream += S[t];
		resultingText += text[k] ^ S[t];
	}
	return resultingText;
}

int main()
{
	string key;
	cout << "Enter Key: ";
	cin >> key;
	cin.ignore();
	string plainText, cipherText, decryptedText;
	cout << "Enter the plain text: ";
	getline(cin, plainText);
	cipherText = encryptionDecryption(plainText,key);
	cout << "cipher Text is: " << cipherText << endl;
	decryptedText = encryptionDecryption(cipherText,key);
	cout << "decrypted text is: " << decryptedText << endl;
	return 0;
}