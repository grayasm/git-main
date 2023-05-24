using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace DataGrid
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            dataGrid.ItemsSource = new Record[]
            {
                new Record { FirstName="Adam", LastName="Nathan", Website=new Uri("http://twitter.com/adamnathan"), Gender=Gender.Male },
                new Record { FirstName="Bill", LastName="Gates", Website=new Uri("http://twitter.com/billgates"), Gender=Gender.Male, IsBillionaire=true }
            };
        }
    }
}