
using System;
using System.Collections.ObjectModel;
using System.Windows;
using WpfApp1;

namespace createRoom
{
    public partial class CreateRoomWindow : Window
    {
        public ObservableCollection<string> Players { get; set; }
        public string Admin { get; set; }

        public CreateRoomWindow()
        {
            InitializeComponent();
            Players = new ObservableCollection<string>();
            PlayersListBox.ItemsSource = Players;
        }

        private void CreateRoomButton_Click(object sender, RoutedEventArgs e)
        {
            string roomName = RoomNameTextBox.Text;
            int questionTime;
            int playersCount;

            if (string.IsNullOrEmpty(roomName))
            {
                MessageBox.Show("Please enter a room name.");
                return;
            }

            if (!int.TryParse(QuestionAmountTextBox.Text, out questionTime))
            {
                MessageBox.Show("Please enter a valid number for question time.");
                return;
            }

            if (!int.TryParse(PlayersCountTextBox.Text, out playersCount))
            {
                MessageBox.Show("Please enter a valid number for players count.");
                return;
            }

            string sendCreateRoomMsg = TriviaProtocol.CreateRoom(roomName, playersCount, questionTime, 50);
            Socket.SendMsg(sendCreateRoomMsg);

            string recvCreateRoomMsg = Socket.RecvMsgByResponse((int)TriviaResponse.CREATE_ROOM);
            if (recvCreateRoomMsg != null)
            {
                MessageBox.Show("Room Successfully created", "Server Response", MessageBoxButton.OK, MessageBoxImage.Information);
                waitingRoomForCreate waitingRoom = new waitingRoomForCreate();
                waitingRoom.Show();
                this.Close();
            }
        }
    }
}
