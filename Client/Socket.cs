using System;
using System.Configuration;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Windows;
using WpfApp1;

namespace WpfApp1
{
    public static class Socket
    {
        private static readonly TcpClient clientSocket = new TcpClient();

        // Checks if the any user logged (no logged user -> no logged)
        public static bool IsLogged => LoggedUser != null;

        // returns the current logged user
        public static string LoggedUser { get; set; } = null;

        // returns formatted string of logged user >> "Logged as USERNAME"
        public static string LoggedUserFormatted => IsLogged ? $" (Logged as {LoggedUser})" : "";

        // True if the server active (on the port), either - false
        public static bool Connected { get; set; }

        // Returns server connected address

        static Socket()
        {
            try
            {
                clientSocket.Connect("127.0.0.1", 1306);
            }
            catch
            {
                Connected = false;
                return;
            }
            Connected = true;
        }

        // Sends message to the active socket
        public static bool SendMsg(string msg)
        {
            try
            {
                NetworkStream stream = clientSocket.GetStream();
                byte[] outStream = Encoding.ASCII.GetBytes(msg);

                stream.Write(outStream, 0, outStream.Length);
                stream.Flush();
            }
            catch (Exception ex)
            {
                return false;
            }
            return true;
        }

        // Receive message from the active socket
        public static string RecvMsg()
        {
            try
            {
                NetworkStream stream = clientSocket.GetStream();
                byte[] inStream = new byte[8192];

                stream.Read(inStream, 0, 8192);
                return Encoding.ASCII.GetString(inStream);
            }
            catch (Exception ex)
            {
                return null;
            }
        }

        /// Receive message from the active socket server only if the response code matching, if not, wait for the right message.
        public static string RecvMsgByResponse(params int[] responseTypes)
        {
            string recvMsg;
            TriviaMessage response;

            do
            {
                recvMsg = RecvMsg();
                response = new TriviaMessage(recvMsg);
                if (response.Code == (int)TriviaResponse.ERROR)
                {
                    return null;
                }

            } while (!responseTypes.Contains(response.Code)); // Wait for the right message

            return recvMsg;
        }
    }
}