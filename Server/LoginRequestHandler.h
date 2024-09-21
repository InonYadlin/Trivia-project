#pragma once

#include "IRequestHandler.h"
#include "jsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "Requests.h"
#include "RequestHandlerFactory.h"
#include "sqliteDB.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	/* Constructor */
	LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handlerFactory);

	/* Function checks if the request is a login or signup one */
	virtual bool isRequestRelevant(const RequestInfo request) override;

	/*s Function gets a request and returns a "RequestResult" object(holds the response) */
	virtual RequestResult handleRequest(const RequestInfo request, const SOCKET socket) override;

private:

	/* Function tries to login with the request's info */
	RequestResult login(const RequestInfo request, const SOCKET socket) const;

	/* Function tries to signup with the request's info */
	RequestResult signup(const RequestInfo request) const;

	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handlerFactory;
};