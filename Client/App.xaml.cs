using SimpleLoginApp;
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using WpfApp1;

namespace WpfApp1
{
    /// <summary>
    /// Interaction logic for App.xaml
    /// </summary>
    public partial class App : Application
    {
        [STAThread] // Ensure the main thread is STA
        public static void Main()
        {
            App app = new App();
            MainWindow mainWindow = new MainWindow();
            app.Run(mainWindow); // Start the WPF application event loop with MainWindow
        }
    }
}
