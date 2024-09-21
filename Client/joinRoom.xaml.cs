using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;
using System.Text.Json;
using System.Windows;
using WpfApp1;
using System.Threading;
using Newtonsoft.Json.Linq;

namespace joinRoom
{
    public partial class JoinRoomWindow : Window
    {
        private Thread _thread;
        private CancellationTokenSource _token;
        private Mutex _mutex;
        public JoinRoomWindow()
        {
            InitializeComponent();

            // Initialize new thread, cancallation token and mutex
            _mutex = new Mutex();
            _token = new CancellationTokenSource();
            _thread = new Thread(new ThreadStart(LoadExistingRooms));

            // Set thread to run seperatly and start it
            _thread.IsBackground = true;
            _thread.Start();


        }

        ~JoinRoomWindow() 
        {
            _mutex.Dispose();
        }

        private void LoadExistingRooms()
        {   
            while (true)
            {
                if (_token.IsCancellationRequested)
                {
                    Console.WriteLine("Worker thread: Cancellation requested. Exiting.");
                    return;
                }
                string sendGetRoomsMsg = TriviaProtocol.GetRooms();
                Socket.SendMsg(sendGetRoomsMsg);

                string recvGetRoomsMsg = Socket.RecvMsgByResponse((int)TriviaResponse.GET_ROOMS);

                // Extract the JSON part from the message
                int jsonStartIndex = recvGetRoomsMsg.IndexOf("{");
                int jsonEndIndex = recvGetRoomsMsg.LastIndexOf("}") + 1;
                string jsonString = recvGetRoomsMsg.Substring(jsonStartIndex, jsonEndIndex - jsonStartIndex);

                // Parse the JSON string
                var jsonDoc = JsonDocument.Parse(jsonString);
                var root = jsonDoc.RootElement;

                // Extract all name attributes
                var names = new List<string>();
                foreach (var room in root.GetProperty("Rooms").EnumerateArray())
                {
                    string name = room.GetProperty("name").GetString();
                    names.Add(name);
                }

                try
                {
                    _mutex.WaitOne(1000);
                    RoomsListBox.ItemsSource = names;
                    _mutex.ReleaseMutex();
                }
                
                catch (Exception ex) { }

                Thread.Sleep(3000);
            }
        }

        private void JoinRoomButton_Click(object sender, RoutedEventArgs e)
        {
            string roomID = RoomIdTextBox.Text;
            bool isGameAlreadyRunning = false;
            int id = 0;

            if (string.IsNullOrEmpty(roomID))
            {
                MessageBox.Show("Please enter a room ID.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            try
            {
                id = Int32.Parse(roomID);
                isGameAlreadyRunning = TriviaGet.IsRoomActive(RoomsListBox.SelectedItem.ToString());
            }
            catch (Exception ex)
            {
                MessageBox.Show("Please enter a room ID and select a room from the list", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            _token.Cancel();

            if (!isGameAlreadyRunning)
            {
                string sendJoinMsg = TriviaProtocol.JoinRoom(id);
                Socket.SendMsg(sendJoinMsg);

                string recvJoinMsg = Socket.RecvMsgByResponse((int)TriviaResponse.JOIN_ROOM);
                if (recvJoinMsg != null)
                {
                    try
                    {
                        _mutex.WaitOne(1000);
                        MessageBox.Show($"Successfuly joined to room: {RoomsListBox.SelectedItem}", "Server Response", MessageBoxButton.OK, MessageBoxImage.Information);
                        _mutex.ReleaseMutex();
                    }

                    catch (Exception ex) { }
                }
            }

            else
            {
                MessageBox.Show("The game is already running in this room", "Can't Join", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
    }
}
