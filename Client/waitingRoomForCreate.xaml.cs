using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using SimpleLoginApp;
using SimpleSignupApp;

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for waitingRoomForCreate.xaml
    /// </summary>
    public partial class waitingRoomForCreate : Window
    {
        public waitingRoomForCreate()
        {
            InitializeComponent();
        }
        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            // Close room
            string sendCloseRoomMsg = TriviaProtocol.CloseRoom();
            Socket.SendMsg(sendCloseRoomMsg);
            string recvCloseRoomMsg = Socket.RecvMsgByResponse((int)TriviaResponse.CREATE_ROOM);

            // Go back to menu
            SimpleLoginApp.Menu menu = new SimpleLoginApp.Menu();
            menu.Show();
            this.Close();
            
        }
        private void StartButton_Click(object sender, RoutedEventArgs e)
        {
            // Close room
            string sendCloseRoomMsg = TriviaProtocol.CloseRoom();
            Socket.SendMsg(sendCloseRoomMsg);
            string recvCloseRoomMsg = Socket.RecvMsgByResponse((int)TriviaResponse.CREATE_ROOM);

            // Go back to menu and show messsage
            MessageBox.Show("This feature isn't implemented yet!", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            SimpleLoginApp.Menu menu = new SimpleLoginApp.Menu();
            menu.Show();
            this.Close();
        }
    }
}
