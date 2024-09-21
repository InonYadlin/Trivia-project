using Newtonsoft.Json;
using System.Collections.Generic;
using System.Net.Sockets;

namespace WpfApp1
{
    public static class TriviaProtocol // Class which creates ready message
    {
        // Formats the returned response into one informatically message without any payload
        public static string FormatResponseByMessage(string recvMsg)
        {
            TriviaMessage message = new TriviaMessage(recvMsg);
            Dictionary<string, string> mDic = message.ToDict();

            return mDic.ContainsKey("message") ? mDic["message"] : "";
        }

        // Builds up sign in message
        public static string SignIn(string username, string password, string email, string address, string phoneNumber, string birthDate)
        {
            Dictionary<string, string> jsonDictionary = new Dictionary<string, string>
            {
                { "username", username },
                { "password", password },
                { "email", email },
                { "address", address },
                { "phoneNumber", phoneNumber },
                { "birthDate", birthDate }
            };

            TriviaMessage signUpMessage = new TriviaMessage
            {
                Code = (int)TriviaRequest.SIGN_UP,
                Content = JsonConvert.SerializeObject(jsonDictionary)
            };
            return signUpMessage.ToString();
        }

        // Builds up login message
        public static string Login(string username, string password)
        {
            Dictionary<string, string> jsonDictionary = new Dictionary<string, string>
            {
                { "username", username },
                { "password", password }
            };

            TriviaMessage loginMessage = new TriviaMessage
            {
                Code = (int)TriviaRequest.LOGIN,
                Content = JsonConvert.SerializeObject(jsonDictionary)
            };
            return loginMessage.ToString();
        }

        public static string Logout()
        {
            TriviaMessage logoutMessage = new TriviaMessage((int)TriviaRequest.EXIT_CLIENT, "");

            logoutMessage.Content = "logout";

            return logoutMessage.ToString();
        }

        // Builds up create room message
        public static string CreateRoom(string roomName, int maxUsers, int questionCount, int answerTimeout)
        {
            Dictionary<string, object> jsonDictionary = new Dictionary<string, object>
            {
                { "roomName", roomName },
                { "maxUsers", maxUsers },
                { "questionCount", questionCount },
                { "answerTimeout", answerTimeout },
            };

            TriviaMessage createRoomMessage = new TriviaMessage
            {
                Code = (int)TriviaRequest.CREATE_ROOM,
                Content = JsonConvert.SerializeObject(jsonDictionary)
            };
            return createRoomMessage.ToString();
        }

        // Builds up gets room message
        public static string GetRooms()
        {
            TriviaMessage getRoomsMessage = new TriviaMessage((int)TriviaRequest.GET_ROOMS, "");
            return getRoomsMessage.ToString();
        }

        // Builds up a get users in room message (called from menu handler)
        public static string GetUsersInRoom(int roomId)
        {
            Dictionary<string, int> jsonDictionary = new Dictionary<string, int>
            {
                { "roomId", roomId }
            };

            TriviaMessage getUsersInRoomMessage = new TriviaMessage
            {
                Code = (int)TriviaRequest.GET_USERS_IN_ROOM,
                Content = JsonConvert.SerializeObject(jsonDictionary)
            };
            return getUsersInRoomMessage.ToString();
        }

        // Builds up get room state (which contains current room data)
        public static string GetCurrentRoomState()
        {
            TriviaMessage getRoomStateMessage = new TriviaMessage((int)TriviaRequest.GET_ROOM_STATE, "");
            return getRoomStateMessage.ToString();
        }

        // Builds up join room message
        public static string JoinRoom(int roomId)
        {
            Dictionary<string, int> jsonDictionary = new Dictionary<string, int>
            {
                { "roomId", roomId }
            };

            TriviaMessage joinRoomMessage = new TriviaMessage
            {
                Code = (int)TriviaRequest.JOIN_ROOM,
                Content = JsonConvert.SerializeObject(jsonDictionary)
            };
            return joinRoomMessage.ToString();
        }

        // Builds up get personal statistics message
        public static string GetPersonalStatistics()
        {
            TriviaMessage getPesonalStatisticsMessage = new TriviaMessage((int)TriviaRequest.GET_PERSONAL_STATISTICS, "");
            return getPesonalStatisticsMessage.ToString();
        }

        // Builds up get high score message
        public static string GetHighScore()
        {
            TriviaMessage getHighScoreMessage = new TriviaMessage((int)TriviaRequest.GET_HIGH_SCORE_STATISTICS, "");
            return getHighScoreMessage.ToString();
        }

        // Builds up a add question message
        public static string AddQuestion(string question, string c_answer1, string w_answer2, string w_answer3, string w_answer4)
        {
            Dictionary<string, string> jsonDictionary = new Dictionary<string, string>
            {
                { "question", question },
                // Corrtect answer
                { "c_answer1", c_answer1 }, 
                { "w_answer2", w_answer2 },
                { "w_answer3", w_answer3 },
                { "w_answer4", w_answer4 }
            };

            TriviaMessage addQuestionMessage = new TriviaMessage
            {
                Code = (int)TriviaRequest.ADD_QUESTION,
                Content = JsonConvert.SerializeObject(jsonDictionary)
            };
            return addQuestionMessage.ToString();
        }

        // Builds up a close room message
        public static string CloseRoom()
        {
            TriviaMessage closeRoomMessage = new TriviaMessage((int)TriviaRequest.CLOSE_ROOM, "");
            return closeRoomMessage.ToString();
        }

        // Builds up a leave room message
        public static string LeaveRoom()
        {
            TriviaMessage leaveRoomMessage = new TriviaMessage((int)TriviaRequest.LEAVE_ROOM, "");
            return leaveRoomMessage.ToString();
        }
    }
}