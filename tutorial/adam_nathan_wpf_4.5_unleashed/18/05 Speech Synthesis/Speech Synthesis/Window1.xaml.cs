using System;
using System.Speech.Synthesis;

namespace Speech_Synthesis
{
    public partial class Window1 : System.Windows.Window
    {
        public Window1()
        {
            InitializeComponent();

            SpeechSynthesizer synthesizer = new SpeechSynthesizer();
            PromptBuilder promptBuilder = new PromptBuilder();

            promptBuilder.AppendTextWithHint("WPF", SayAs.SpellOut);
            promptBuilder.AppendText("sounds better than WPF.");

            // Pause for 2 seconds
            promptBuilder.AppendBreak(new TimeSpan(0, 0, 2));
            
            promptBuilder.AppendText("The time is");
            promptBuilder.AppendTextWithHint(DateTime.Now.ToString("hh:mm"), SayAs.Time);
            
            // Pause for 2 seconds
            promptBuilder.AppendBreak(new TimeSpan(0, 0, 2));
            
            promptBuilder.AppendText("Hey Sam, can you spell queue?");
            
            promptBuilder.StartVoice("Microsoft Sam");
            promptBuilder.AppendTextWithHint("queue", SayAs.SpellOut);
            promptBuilder.EndVoice();
            
            promptBuilder.AppendText("Do it faster!");
            
            promptBuilder.StartVoice("Microsoft Sam");
            promptBuilder.StartStyle(new PromptStyle(PromptRate.ExtraFast));
            promptBuilder.AppendTextWithHint("queue", SayAs.SpellOut);
            promptBuilder.EndStyle();
            promptBuilder.EndVoice();
 
            // Speak all the content in the PromptBuilder
            synthesizer.SpeakAsync(promptBuilder);
        }
    }
}