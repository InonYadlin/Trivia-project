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
using System.Windows.Shapes;
using WpfApp1;
using SimpleSignupApp;

namespace SimpleLoginApp
{
    public partial class AddQuestion : Window
    {
        public AddQuestion()
        {
            InitializeComponent();
        }
        private void btnAddQuestion_Click(object sender, RoutedEventArgs e)
        {
            string question = txtQuestion.Text;
            string wAnswer1 = txtWAnswer1.Text;
            string wAnswer2 = txtWAnswer2.Text;
            string wAnswer3 = txtWAnswer3.Text;
            string cAnswer = txtCAnswer.Text;

            if (question  == null || wAnswer1 == null || wAnswer2 == null || wAnswer3 == null || cAnswer == null)
            {
                MessageBox.Show("Please fill all the fields!", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }

            else 
            {
                string addQuestionAddMsg = TriviaProtocol.AddQuestion(question, cAnswer, wAnswer1, wAnswer2, wAnswer3);
                Socket.SendMsg(addQuestionAddMsg);

                string recvQuestionAdd = Socket.RecvMsgByResponse((int)TriviaResponse.ADD_QUESTION);
                if (recvQuestionAdd != null)
                {
                    MessageBox.Show("Question successfully added!", "Success", MessageBoxButton.OK, MessageBoxImage.Information);
                    Menu menu = new Menu();
                    menu.Show();
                    this.Close();
                }
            }
        }

        private void btnGoBack_Click(object sender, RoutedEventArgs e) 
        {
            Menu menu = new Menu();
            menu.Show();
            this.Close();
        } 
    }
}
