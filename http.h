#include <iostream>
#include <string>
#include <string.h>
#include <map>
#include <errno.h>
#include <stdlib.h>

#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/event.h>

using namespace std;


class Http
{
private:
	static void event_cb(bufferevent *bev, short events, void *ctx);
	static void read_cb(bufferevent *bev, void *ctx);

private:	
	enum
	{
		REQUEST_LINE = 0,
		HEADER = 1,
		MSG_BODY = 2,
		FINISHED = 3,
		ERROR_STATUS
	};

	string method;
	string path;
	string version;
	map<string, string> header_map;
	string mes_body;

	char status;  

	bufferevent* bev;
		
	bool parse_request_line();
	bool parse_header();
	bool parse_msg_body();

	char* get_word(char*, string&);


	/*explict*/ Http(event_base*, evutil_socket_t);
	~Http();

public:
	static Http* create(event_base*, evutil_socket_t);
	static void release(Http**);

	bool loop();
	void run(void* arg);
};
