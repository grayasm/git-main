using System;
using System.Windows;
using System.Windows.Controls;

namespace PhotoGallery
{
    public partial class RenameDialog : Window
    {
        string newFilename;
        string oldFilename;

        public RenameDialog()
        {
            InitializeComponent();
            textBox.Text = oldFilename;
            textBox.Focus();
        }

        public RenameDialog(string oldFilename)
        {
            InitializeComponent();
            this.oldFilename = oldFilename;
            textBox.Text = oldFilename;
            textBox.Focus();
        }

        void textBox_TextChanged(object sender, RoutedEventArgs e)
        {
            newFilename = textBox.Text;
        }

        void okButton_Click(object sender, RoutedEventArgs e)
        {
            this.DialogResult = true;
        }

        public string OldFilename
        {
            get { return oldFilename; }
            set { oldFilename = value; }
        }

        public string NewFilename
        {
            get { return newFilename; }
        }
    }
}