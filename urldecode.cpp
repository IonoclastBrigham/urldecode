// URL Decoder
//
// Copyright © 2020 Brigham Toskin <https://github.com/IonoclastBrigham>
//
// License: GPLv3.0 <https://www.gnu.org/licenses/gpl-3.0.txt>
//
// Dependencies: libcurl <https://curl.haxx.se>
//
////////////////////////////////////////////////////////////////////////////////


#import <iostream>
using namespace std;

#include <curl/curl.h>


class CurlWrapper
{
private:
	CURL* ptr;
public:
	CurlWrapper() : ptr(curl_easy_init()) {}
	virtual ~CurlWrapper()
	{
		curl_free(ptr);
	}

	string Decode(const string& tEncoded)
	{
		return string(curl_easy_unescape(ptr, tEncoded.c_str(), tEncoded.size(), nullptr));
	}
};


int main(int argc, char** argv)
{
	auto curl = CurlWrapper();

	// bail if bad input
	if(argc > 2)
	{
		cerr << "Usage: " << argv[0] << " ENCODED\n"
		     << "   or: COMMAND | " << argv[0] << endl;
		return argc - 2;
	}

	// decode from expected input
	if(argc == 2)
	{
		cout << curl.Decode(argv[1]) << endl;
	}
	else
	{
		string encoded;
		getline(cin, encoded);
		cout << curl.Decode(encoded) << endl;
	}

	return 0;
}
