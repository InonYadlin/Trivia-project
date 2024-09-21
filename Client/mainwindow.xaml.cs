using SimpleSignupApp;
using System.Windows;
using WpfApp1;

namespace SimpleLoginApp
{
    public partial class MainWindow : Window
    {
        public MainWindow()
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

            if (recvLoginMessage != null)
            {
                MessageBox.Show("Login successful!", "Success", MessageBoxButton.OK, MessageBoxImage.Information);
                Menu menu = new Menu();
                menu.Show();
                this.Close();
            }

            else
            {
                MessageBox.Show("Invalid username or password.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
        private void btnSignUp_Click(object sender, RoutedEventArgs e)
        {
            SignUp signUpWindow = new SignUp();
            signUpWindow.Show();
            this.Close();
        }
    }
}
