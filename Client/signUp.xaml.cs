using System.Windows;
using System.Windows.Controls;
using WpfApp1;
using SimpleLoginApp;

namespace SimpleSignupApp
{
    public partial class SignUp : Window
    {
        public SignUp()
        {
            InitializeComponent();
        }

        private void btnSignup_Click(object sender, RoutedEventArgs e)
        {
            string username = txtUsername.Text;
            string password = txtPassword.Password;
            string email = txtEmail.Text;
            string birthDate = txtBirthDate.Text;
            string phoneNumber = txtPhoneNumber.Text;
            string address = "(" + txtStreet.Text + ", " + txtApartment.Text + ", " + txtCity.Text + ")";

            // Simple validation logic
            if (string.IsNullOrEmpty(username) || string.IsNullOrEmpty(password) || string.IsNullOrEmpty(email) || 
                string.IsNullOrEmpty(birthDate) || string.IsNullOrEmpty(phoneNumber) || string.IsNullOrEmpty(address))
            {
                MessageBox.Show("Please fill in all fields.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            string sendSignUpMsg = TriviaProtocol.SignIn(username, password, email, address, phoneNumber, birthDate);
            Socket.SendMsg(sendSignUpMsg);

            string recvSignUpMsg = Socket.RecvMsgByResponse((int)TriviaResponse.SIGNUP);
            if (recvSignUpMsg != null)
            {
                MessageBox.Show("Successfully signed up", "Server Response", MessageBoxButton.OK, MessageBoxImage.Information);
                SimpleLoginApp.Login loginWindow = new SimpleLoginApp.Login();
                loginWindow.Show();
                this.Close();
            }

            else
            {
                MessageBox.Show("Error encountered while signing up!", "Error", MessageBoxButton.OK, MessageBoxImage.Information);
            }
        }
    }
}