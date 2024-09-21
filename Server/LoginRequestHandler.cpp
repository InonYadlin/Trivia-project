#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handlerFactory) : m_loginManager(loginManager), m_handlerFactory(handlerFactory) {}


bool LoginRequestHandler::isRequestRelevant(const RequestInfo request) 
{
	// Check if request is relevant
	return (request.id == LOGIN_REQUEST) || (request.id == SIGNUP_REQUEST);
}


RequestResult LoginRequestHandler::handleRequest(const RequestInfo request, const SOCKET socket) 
{
	try
	{
		// Login
		if (request.id == LOGIN_REQUEST) 
		{
			return this->login(request, socket);
		}

		// Signup
		else if (request.id == SIGNUP_REQUEST) 
		{
			return this->signup(request);
		}
	}

	// JSON error
	catch (nlohmann::json::exception& e) 
	{
		ErrorResponse res = { "[ERROR] Request contains invalid json" };
		return { JsonResponsePacketSerializer::serializeResponse(res), nullptr };
	}

	// Different error
	catch (std::exception& e) 
	{
		ErrorResponse res = { e.what() };
		return { JsonResponsePacketSerializer::serializeResponse(res), nullptr };
	}
}


RequestResult LoginRequestHandler::login(const RequestInfo request, const SOCKET socket) const
{
	LoginRequest req = JsonRequestPacketDeserializer::deserializeLoginRequest(request.buffer);
	// Trying to login 
	this->m_loginManager.login(req.username, req.password, socket); 
	LoginResponse res = { LOGIN_RESPONSE };
	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createMenuRequestHandler(req.username, socket) };
}


RequestResult LoginRequestHandler::signup(const RequestInfo request) const
{
	SignupRequest req = JsonRequestPacketDeserializer::deserializeSignupRequest(request.buffer);
	// Trying to signup
	this->m_loginManager.signup(req.username, req.password, req.email, req.address, req.phoneNumber, req.birthDate); 
	SignupResponse res = { SIGNUP_RESPONSE };
	return { JsonResponsePacketSerializer::serializeResponse(res), (IRequestHandler*)this->m_handlerFactory.createLoginRequestHandler() };
}