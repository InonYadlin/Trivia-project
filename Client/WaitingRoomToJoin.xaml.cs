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

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for WaitingRoomToJoin.xaml
    /// </summary>
    public partial class WaitingRoomToJoin : Window
    {
        public WaitingRoomToJoin()
        {
            InitializeComponent();
        }
        private void CancelButton_Click(object sender, RoutedEventArgs e)
        {
            // Leave room 
            string sendLeaveRoomMessage = TriviaProtocol.LeaveRoom();
            Socket.SendMsg(sendLeaveRoomMessage);
            string recvLeaveRoomResponse = Socket.RecvMsgByResponse((int)TriviaResponse.LEAVE_ROOM);

            // Go back to menu
            SimpleLoginApp.Menu menu = new SimpleLoginApp.Menu();
            menu.Show();
            this.Close();
        }
    }
}
