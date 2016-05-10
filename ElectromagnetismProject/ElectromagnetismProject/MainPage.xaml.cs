using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Media;
using System.Windows.Controls;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using ElectromagnetismProjectComp;
using System.Windows.Media.Animation;
using System.Windows.Controls.Primitives;

namespace ElectromagnetismProject
{

    public partial class MainPage : PhoneApplicationPage
    {
        // Constructor
        public MainPage()
        {
            InitializeComponent();

            //this.Background = new ImageBrush(new BitmapImage(new Uri("/Assets/science_cat.png", UriKind.Relative)));
        }

        private void aboutButton_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new Uri("/AboutPage.xaml", UriKind.Relative));
            //Button thing = (Button)sender;
            //shrinkTextBlock(thing);
        }

        private void gameButton_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new Uri("/GamePage.xaml", UriKind.Relative));

        }

        private void eqnButton_Click(object sender, RoutedEventArgs e)
        {
            NavigationService.Navigate(new Uri("/EquationsPage.xaml", UriKind.Relative));
        }

        private void about_button_Tap(object sender, System.Windows.Input.GestureEventArgs e)
        {
            NavigationService.Navigate(new Uri("/AboutPage.xaml", UriKind.Relative));
            //TextBlock thing = (TextBlock)sender;
            //shrinkTextBlock((TextBlock)sender);
        }

        private void game_button_Tap(object sender, System.Windows.Input.GestureEventArgs e)
        {
            NavigationService.Navigate(new Uri("/GamePage.xaml", UriKind.Relative));

        }

        private void eqn_button_Tap(object sender, System.Windows.Input.GestureEventArgs e)
        {
            NavigationService.Navigate(new Uri("/EquationsPage.xaml", UriKind.Relative));
        }

        private void shrinkTextBlock(Button sender)
        {
            sender.FontSize *= .8;
        }

        //private void TextBlock_DoubleTap(object sender, System.Windows.Input.GestureEventArgs e)
        //{
        //    NavigationService.Navigate(new Uri("/AboutPage.xaml", UriKind.Relative));
        //}
    }
}