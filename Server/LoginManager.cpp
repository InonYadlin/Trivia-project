#include "LoginManager.h"

std::vector<LoggedUser> LoginManager::m_loggedUsers = {};

LoginManager::LoginManager(IDatabase* db)
{
	this->m_database = db;
}

LoginManager::LoginManager(LoginManager& loginManager)
{
	this->m_database = loginManager.getDatabase();
}


LoginManager::~LoginManager()
{
	this->m_database = nullptr;
}


void LoginManager::login(const std::string username, const std::string password, const SOCKET socket)
{
	// Check if user already logged in
	this->users_mtx.lock(); 

	// Make sure we read all the users properly
	for (auto& user : this->m_loggedUsers)
	{
		if (username == user.getUsername())
		{
			this->users_mtx.unlock();
			throw std::exception("[ERROR] User is already logged in");
		}
	}
	this->users_mtx.unlock();

	// Checks users password (if matches according his record in the db)
	if (this->m_database->doesPasswordMatch(username, password))
		this->m_loggedUsers.push_back(LoggedUser(username, socket));
	else
		throw std::exception("[ERROR] Invalid password or username");
}


void LoginManager::signup(const std::string username, const std::string password, const std::string email,
	const std::string address, const std::string phoneNumber, const std::string birthDate)
{
	// All the checks to do on the infromation
	std::vector<std::pair<std::string, std::pair<std::regex, std::string>>> all_checks;

	all_checks.push_back({ password, {(std::regex)(REGEX_PASSWORD), "[ERROR] Password should be 8+ length, contain uppercase, lowercase and special characters, digits"} }); // check for password
	all_checks.push_back({ email, {(std::regex)(REGEX_EMAIL), "[ERROR] email should be separated via @ and should contain . (dot) between the email and the domain" } }); // check for email
	all_checks.push_back({ address, {(std::regex)(REGEX_ADDRESS), "[ERROR] Address should be (Street [upper/lower case characters], Apt [digits], City [upper/lower case characters])" } }); // check for address
	all_checks.push_back({ phoneNumber, {(std::regex)(REGEX_PHONE_NUMBER), "[ERROR] Number should begin with 0 and continue with 1-2 numbers (0X/05X)" } }); // check for phoneNumber
	all_checks.push_back({ birthDate, { (std::regex)(REGEX_BIRTH_DATE), "[ERROR] Birth date should be DD.MM.YYYY or DD/MM/YYYY" } }); // check for birthDate

	// Loop through all the checks
	for (auto i : all_checks) 
	{
		// Check if current info is valid
		if (!regex_search(i.first, i.second.first)) 
		{
			throw std::exception(i.second.second.c_str());
		}
	}

	// Check if user already exists in the data base
	if (this->m_database->doesUserExist(username)) 
	{
		throw std::exception("[ERROR] User with this name already exists");
	}

	// Everything is valid -> add the user
	else 
	{
		this->users_mtx.lock();
		this->m_database->addNewUser(username, password, email, address, phoneNumber, birthDate);
		this->users_mtx.unlock();
	}
}


void LoginManager::logout(const std::string username)
{
	bool loggedIn = false;
	auto it = this->m_loggedUsers.begin();

	this->users_mtx.lock();

	// Search the user in the vector of users
	while (it != this->m_loggedUsers.end() && !loggedIn) 
	{
		if (it->getUsername() == username)
			loggedIn = true;
		else
			it++;
	}

	if (loggedIn)
	{
		// Remove the user from the vector of users
		this->m_loggedUsers.erase(it); 
		this->users_mtx.unlock();
	}

	else
	{
		this->users_mtx.unlock();
		throw std::exception("[ERROR] This username isn't logged in");
	}
}

IDatabase* LoginManager::getDatabase()
{
	return this->m_database;
}
