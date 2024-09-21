using HighScoresApp;
using PersonalStatsApp;
using System.Windows;
using WpfApp1;

namespace StatisticsApp
{
    public partial class StatisticsWindow : Window
    {
        public StatisticsWindow()
        {
            InitializeComponent();
        }

        private void PersonalStatsButton_Click(object sender, RoutedEventArgs e)
        {
            PersonalStatsWindow personalStatsWindow = new PersonalStatsWindow();
            personalStatsWindow.Show();
            this.Close();
        }

        private void HighScoresButton_Click(object sender, RoutedEventArgs e)
        {
            HighScoresWindow highScoresWindow = new HighScoresWindow();
            highScoresWindow.Show();
            this.Close();
        }
    }
}
