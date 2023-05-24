using System;
using System.Windows;
using System.Speech.Recognition;

namespace Speech_Recognition
{
    public partial class Window1 : System.Windows.Window
    {
        public Window1()
        {
            InitializeComponent();

            SpeechRecognitionEngine engine = new SpeechRecognitionEngine();
            GrammarBuilder builder = new GrammarBuilder();
            builder.Append(new Choices("two", "three", "four", "five", "six", "seven",
              "eight", "nine", "ten", "jack", "queen", "king", "ace"));
            builder.Append("of", 0, 1);
            builder.Append(new Choices("clubs", "diamonds", "spades", "hearts"));
            engine.LoadGrammar(new Grammar(builder));

            engine.SpeechRecognized +=
                new EventHandler<SpeechRecognizedEventArgs>(recognizer_SpeechRecognized);

            engine.SetInputToDefaultAudioDevice();
            engine.RecognizeAsync();
        }

        void recognizer_SpeechRecognized(object sender, SpeechRecognizedEventArgs e)
        {
            MessageBox.Show("You said: " + e.Result.Text);
        }
    }
}