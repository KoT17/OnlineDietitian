#include <stdlib.h>
#include <iostream>
#include <mysql.h>
#include <mysqlx/xdevapi.h>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/http_listener.h> 
#include <cpprest/json.h>  
#include <cpprest/uri.h>
#include <cpprest/asyncrt_utils.h>
#include "NutritionalServer.h"


using namespace std;
using namespace mysqlx;
using namespace utility;
using namespace web;
using namespace pplx;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;
using namespace http::experimental::listener;

std::unique_ptr<NutritionalServer> g_http;

void on_initialize(const string_t& address)
{
	// Build our listener's URI from the configured address and the hard-coded path "MyServer/Action"

	uri_builder uri(address);
	uri.append_path(U("NutritionalLookup"));

	auto addr = uri.to_uri().to_string();
	g_http = std::unique_ptr<NutritionalServer>(new NutritionalServer(addr));
	g_http->open().wait();

	ucout << utility::string_t(U("Listening for requests at: ")) << addr << std::endl;

	return;
}

void on_shutdown()
{
	g_http->close().wait();
	return;
}

int wmain(int argc, wchar_t* argv[])
{
	utility::string_t port = U("4200");
	if (argc == 2)
	{
		port = argv[1];
	}

	utility::string_t address = U("http://localhost:");
	address.append(port);

	on_initialize(address);
	std::cout << "Press ENTER to exit." << std::endl;

	std::string line;
	std::getline(std::cin, line);

	on_shutdown();
	return 0;
}