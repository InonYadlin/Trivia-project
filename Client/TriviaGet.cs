using System;
using System.Collections.Generic;
using System.Linq;

namespace WpfApp1
{
    internal class TriviaGet
    {
        public static object[] GetRooms()
        {
            string sendRoomsMsg = TriviaProtocol.GetRooms();
            Socket.SendMsg(sendRoomsMsg);

            string recvRoomsMsg = Socket.RecvMsgByResponse((int)TriviaResponse.GET_ROOMS);
            if (recvRoomsMsg != null)
            {
                TriviaMessage roomsMessage = new TriviaMessage(recvRoomsMsg);
                try
                {
                    return (object[])roomsMessage.ToMultiDict()["Rooms"];
                }
                catch
                {
                    return null;
                }
            }
            return null;
        }

        public static object[] GetUsersInRoom(int roomId) // calls MenuRequestHandler->getPlayersInRoom
        {
            string sendUsersMsg = TriviaProtocol.GetUsersInRoom(roomId);
            Socket.SendMsg(sendUsersMsg);

            string recvUsersMsg = Socket.RecvMsgByResponse((int)TriviaResponse.GET_PLAYERS);
            if (recvUsersMsg != null)
            {
                TriviaMessage usersMessage = new TriviaMessage(recvUsersMsg);

                var dict = usersMessage.ToMultiDict();
                return dict.Values.ToArray();
                
            }
            return null;
        }

        public static Dictionary<string, object> GetCurrentRoomState()
        {
            string sendRoomStateMsg = TriviaProtocol.GetCurrentRoomState();
            Socket.SendMsg(sendRoomStateMsg);

            string recvRoomStateMsg = Socket.RecvMsgByResponse((int)TriviaResponse.GET_ROOM_STATE, (int)TriviaResponse.LEAVE_ROOM, (int)TriviaResponse.START_GAME);

            if (recvRoomStateMsg != null)
            {
                TriviaMessage roomStateMessage = new TriviaMessage(recvRoomStateMsg);

                switch (roomStateMessage.Code)
                {
                    case (int)TriviaRequest.GET_ROOM_STATE:
                        return roomStateMessage.ToMultiDict();

                    case (int)TriviaRequest.LEAVE_ROOM:
                        throw new Exception();

                    case (int)TriviaRequest.START_GAME:
                        throw new Exception();
                }
            }
            return null;
        }

        public static int GetRoomId(object[] rooms, string roomName)
        {
            if (rooms != null && roomName != null)
            {
                foreach (Dictionary<string, object> room in rooms)
                {
                    if (room["name"].ToString() == roomName)
                        return Convert.ToInt32(room["id"]);
                }
            }
            return -1;
        }

        public static Dictionary<string, object> GetRoomByName(object[] rooms, string roomName)
        {
            foreach (Dictionary<string, object> room in rooms)
            {
                if (room["name"].ToString() == roomName)
                    return room;
            }
            return null;
        }

        public static object[] GetPersonalStatistics()
        {
            string sendPersonalStatisticsMsg = TriviaProtocol.GetPersonalStatistics();
            Socket.SendMsg(sendPersonalStatisticsMsg);

            string recvPersonalStatisticsMsg = Socket.RecvMsgByResponse((int)TriviaResponse.GET_PERSONAL_STATS);
            if (recvPersonalStatisticsMsg != null)
            {
                TriviaMessage personalStatisticsMessage = new TriviaMessage(recvPersonalStatisticsMsg);

                return (object[])personalStatisticsMessage.ToMultiDict()["UserStatistics"];
            }
            return null;
        }

        public static object[] GetHighScoresStatistics()
        {
            string sendHighScoresMsg = TriviaProtocol.GetHighScore();
            Socket.SendMsg(sendHighScoresMsg);

            string recvHighScoresMsg = Socket.RecvMsgByResponse((int)TriviaResponse.GET_HIGHSCORE);
            if (recvHighScoresMsg != null)
            {
                TriviaMessage highScoresMessage = new TriviaMessage(recvHighScoresMsg);
                return (object[])highScoresMessage.ToMultiDict()["HighScores"];
            }
            return null;
        }

        public static bool IsRoomActive(string roomName)
        {
            object[] rooms = GetRooms();
            if (rooms != null)
            {
                foreach (Dictionary<string, object> room in rooms)
                {
                    if ((string)room["name"] == roomName)
                        return (int)room["isActive"] == 1;
                }
            }
            return false;
        }

    }
}