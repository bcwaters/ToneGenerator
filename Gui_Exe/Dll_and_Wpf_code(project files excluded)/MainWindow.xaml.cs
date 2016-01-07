using System;
using System.Collections;
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
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace ToneGeneratorGUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        List<Tone> ToneList;
        ToneGeneratorApi.ToneGeneratorApiClass testWav;
        public MainWindow()
        {
            ToneList = new List<Tone>();
            
            testWav   = new ToneGeneratorApi.ToneGeneratorApiClass();
            InitializeComponent();
        }

        private void testButton_Click(object sender, RoutedEventArgs e)
        {
            
            
            unsafe
            {
               byte[] fileNameBytes = Encoding.ASCII.GetBytes( loadedBlock.Text);
                 fixed (byte* p = fileNameBytes)
                     {
                        sbyte* sp = (sbyte*)p;
                        //SP is now what you want
                        testWav.loadWav(sp);
                     }
                Microsoft.Win32.SaveFileDialog dlg = new Microsoft.Win32.SaveFileDialog();
                dlg.ShowDialog();
                string newFileName = dlg.FileName;
                executeResult.Text = dlg.FileName ;
                byte[] newNameBytes = Encoding.ASCII.GetBytes(newFileName);
                fixed (byte* p = newNameBytes)
                {
                    sbyte* sp = (sbyte*)p;
                    //SP is now what you want
                    testWav.writeWav(sp);
                }  
            }
        }

        private void OpenClick(object sender, RoutedEventArgs e)
        {
            
            Microsoft.Win32.OpenFileDialog dlg = new Microsoft.Win32.OpenFileDialog();
            dlg.ShowDialog();
            loadedBlock.Text = dlg.FileName;
            unsafe
            {
                byte[] fileNameBytes = Encoding.ASCII.GetBytes(loadedBlock.Text);
                fixed (byte* p = fileNameBytes)
                {
                    sbyte* sp = (sbyte*)p;
                    //SP is now what you want
                    testWav.loadWav(sp);
                }
            }
                testButton.Visibility = Visibility.Visible;
        }

        private void CloseClick(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void AddToneClick(object sender, RoutedEventArgs e)
        {
            try {
                int tempFreq = Int32.Parse(ToneFrequency.Text);
                int tempDur = Int32.Parse(ToneDuration.Text);
                ToneList.Add(new Tone(tempFreq, tempDur));
                ToneCount.Text = ToneList.Count.ToString();
                EncodeButton.Visibility = Visibility.Visible;
                ToneListBox.Items.Add(tempFreq);
            }
            catch (Exception asd) { };
            ToneFrequency.Text = "";
            ToneDuration.Text = "";

        }

        private void EncodeButton_Click(object sender, RoutedEventArgs e)
        {

            int[] toneData = new int[1+ToneList.Count * 3];
           
            for(int i=0; i/3<ToneList.Count; i=i+3)
            {
                toneData[i ] = ToneList[i/3].freq;
                toneData[1+i] = ToneList[i/3].startTime;
                toneData[2+i] = ToneList[i/3].duration;
            }


            unsafe
            {
                fixed (int* p = toneData)
                {
                    testWav.encodeTones(p, ToneList.Count);
                }
               
            }

           SaveEncode.Visibility = Visibility.Visible;
        }

        private void SaveEncode_Click(object sender, RoutedEventArgs e)
        {
            Microsoft.Win32.SaveFileDialog dlg = new Microsoft.Win32.SaveFileDialog();
            dlg.Filter = "Wav file (*.wav)|*.wav";
            dlg.ShowDialog();
           
            string newFileName = dlg.FileName;
            executeResult.Text = dlg.FileName;
            
            byte[] newNameBytes = Encoding.ASCII.GetBytes(newFileName);
            unsafe
            {
                fixed (byte* p = newNameBytes)
                {
                    sbyte* sp = (sbyte*)p;
                    //SP is now what you want
                    testWav.writeWav(sp);
                }
            }
        }
        
    }



    class Tone
    {
        public int freq;
        public int duration = 2;
        public int startTime;

        public Tone(int _freq, int _startTime)
        {
            freq = _freq;
            startTime=_startTime;
        }
    }
}
