using System.Collections.Generic;
using System.Windows;
using WpfApp1;

namespace HighScoresApp
{
    public partial class HighScoresWindow : Window
    {
        private readonly string[] places = new string[3];
        private readonly string[] points = new string[3];

        public HighScoresWindow()
        {
            InitializeComponent();
            LoadHighScores();
        }

        private void LoadHighScores()
        {
            object[] statistics = TriviaGet.GetHighScoresStatistics();

            if (statistics != null)
            {
                int i = 0;
                foreach (Dictionary<string, object> stat in statistics)
                {
                    if (i < 3)
                    {
                        places[i] = stat["username"].ToString();
                        points[i] = string.Format("{0:0.00}", stat["score"]);
                        i++;
                    }
                }

                User1Value.Text = string.Join(places[1], points[1]);
                User2Value.Text = string.Join(places[2], points[2]);
                User3Value.Text = string.Join(places[3], points[3]);
            }
        }
    }
}
