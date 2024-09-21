import socket
import json

server_address = "127.0.0.1"  # Change this to the server's IP address
server_port = 8080  # Change this to the server's port

MESSAGE_TYPE_LOGIN = 0
MESSAGE_TYPE_SIGNUP = 1

def send_hello(server_address, server_port):
    # Check if the port is within the allowed range
    if not (1024 <= server_port and server_port <= 65535):
        print("Error: Server port must be within the range of 1024 to 65535")
        return

    try:
        # Create a socket object
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        # Connect to the server
        client_socket.connect((server_address, server_port))

        from_server = client_socket.recv(4096)
        from_server = from_server.decode()
        if (from_server == "Hello"):
            # Send the string "Hello"
            client_socket.sendall(b"Hello")
            print("Message 'Hello' sent successfully to the server.")

        print (from_server)

        message = format_message_login("user1", "1234")

        client_socket.sendall(message.encode())

        # Receive response from the server
        response = client_socket.recv(4096)
        print("Received response from server:", response.decode())

        message = format_message_signup("user1", "1234", "user1@gmail.com")

        client_socket.sendall(message.encode())

        # Receive response from the server
        response = client_socket.recv(4096)
        print("Received response from server:", response.decode())

    except Exception as e:
        print(f"Error: {e}")
    finally:
        # Close the socket
        client_socket.close()

# Define the server's IP address and port

# Call the function to send "Hello" to the server
send_hello(server_address, server_port)


def format_message_login(username, password):
    # Define the message structure
    message = {"username": username, "password": password}

    # Convert message to JSON format
    message_json = json.dumps(message)

    message_json_len = len(message_json.encode())

    return str(MESSAGE_TYPE_LOGIN) + str(message_json_len).zfill(4) + message_json


def format_message_signup(username, password, mail):
    # Define the message structure
    message = {"username": username, "password": password, "mail": mail}

    # Convert message to JSON format
    message_json = json.dumps(message)

    message_json_len = len(message_json.encode())

    return str(MESSAGE_TYPE_SIGNUP) + str(message_json_len).zfill(4) + message_json


# Define the server's IP address and port
server_address = "127.0.0.1"  # Change this to the server's IP address
server_port = 8080  # Change this to the server's port

# Call the function to message to the server
send_hello(server_address, server_port)
