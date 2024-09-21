using createRoom;
using joinRoom;
using StatisticsApp;
using System.Net;
using System.Windows;
using WpfApp1;

namespace SimpleLoginApp
{
    public partial class Menu : Window
    {
        public Menu()
        {
            InitializeComponent();
        }

        private void CreateRoom_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Create Room clicked", "Info", MessageBoxButton.OK, MessageBoxImage.Information);
            CreateRoomWindow createRoomWindow = new CreateRoomWindow();
            createRoomWindow.Show();
            this.Close();
        }

        private void JoinRoom_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Join Room clicked", "Info", MessageBoxButton.OK, MessageBoxImage.Information);
            JoinRoomWindow joinRoomWindow = new JoinRoomWindow();
            joinRoomWindow.Show();
            this.Close();
        }

        private void Statistics_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Statistics clicked", "Info", MessageBoxButton.OK, MessageBoxImage.Information);
            StatisticsWindow statisticsWindow = new StatisticsWindow();
            statisticsWindow.Show();
            this.Close();
        }

        private void SignOut_Click(object sender, RoutedEventArgs e)
        {
            string sendLogoutMsg = TriviaProtocol.Logout();
            Socket.SendMsg(sendLogoutMsg);

            string recvLogoutMsg = Socket.RecvMsgByResponse((int)TriviaResponse.SIGNUP);
            if (recvLogoutMsg != null)
            {
                MessageBox.Show("Signed out successfully!", "Info", MessageBoxButton.OK, MessageBoxImage.Information);
            }

            else
            {
                MessageBox.Show("Error encountered while signing out, Forcefully closing!", "Info", MessageBoxButton.OK, MessageBoxImage.Information);
            }
            this.Close();
        }

        private void AddQuestion_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("Add Question clicked", "Info", MessageBoxButton.OK, MessageBoxImage.Information);
            AddQuestion addQuestion = new AddQuestion();
            addQuestion.Show();
            this.Close();
        }
    }
}