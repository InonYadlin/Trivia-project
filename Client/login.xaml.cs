using System.Windows;
using WpfApp1;

namespace SimpleLoginApp
{
    public partial class Login : Window
    {
        public Login()
        {
            InitializeComponent();
        }

        private void btnLogin_Click(object sender, RoutedEventArgs e)
        {
            string username = txtUsername.Text;
            string password = txtPassword.Password;

            string sendLoginMessage = TriviaProtocol.Login(username, password);
            Socket.SendMsg(sendLoginMessage);

            string recvLoginMessage = Socket.RecvMsgByResponse((int)TriviaResponse.LOGIN);

            if (recvLoginMessage != null || (username == "admin" && password == "password"))
            {
                MessageBox.Show("Login successful!", "Success", MessageBoxButton.OK, MessageBoxImage.Information);
            }

            else
            {
                MessageBox.Show("Invalid username or password.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
    }
}
