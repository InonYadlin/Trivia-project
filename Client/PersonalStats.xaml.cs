using System.Windows;
using WpfApp1;

namespace PersonalStatsApp
{
    public partial class PersonalStatsWindow : Window
    {
        public PersonalStatsWindow()
        {
            InitializeComponent();
            LoadPersonalStats();
        }

        private void LoadPersonalStats()
        {
            Username.Text = Socket.LoggedUser;
            object[] statistics = TriviaGet.GetPersonalStatistics();

            CAnswers.Text = statistics[0].ToString();
            WAnswers.Text = statistics[1].ToString();
            AVGTime.Text = statistics[2].ToString();
        }
    }
}
