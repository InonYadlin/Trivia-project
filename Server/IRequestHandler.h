#pragma once

#include "Requests.h"
#include <WinSock2.h>

typedef struct RequestInfo;
typedef struct RequestResult;

class IRequestHandler
{
public:
	/** Function checks if the given request is relevant to the current handler */
	virtual bool isRequestRelevant(const RequestInfo request) = 0;

	/** Function handles the given request */
	virtual RequestResult handleRequest(const RequestInfo request, const SOCKET socket) = 0;
};