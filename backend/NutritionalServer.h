#pragma once
#include <stdlib.h>
#include <iostream>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/http_listener.h> 
#include <cpprest/json.h>  
#include <cpprest/uri.h>
#include <cpprest/asyncrt_utils.h>


using namespace std;
using namespace utility;
using namespace web;
using namespace pplx;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;
using namespace http::experimental::listener;


class NutritionalServer {
public:
	NutritionalServer() {}
	NutritionalServer(string_t url);

	task<void> open() { return listener.open(); }
	task<void> close() { return listener.close(); }
private:
	void handle_get(http_request message);
	void handle_put(http_request message);
	void handle_post(http_request message);
	void handle_delete(http_request message);

	http_listener listener;
};
