using System;
using Gtk;

class MainEntry
{
    static void Main()
    {
        new AppWindow();
    }
}

class AppWindow
{
    Window window;
    HBox   hbox;

    public AppWindow()
    {
        Application.Init ();
        window = new Window ("C# simple player!");
        window.DeleteEvent += OnDelete;
        window.SetDefaultSize (200, 200);

        // a vbox for media buttons
        hbox = new HBox (true, 4);
        window.Add (hbox);

        // media buttons
        Button play_bn = new Button(Stock.MediaPlay);
        Button pause_bn = new Button(Stock.MediaPause);
        Button stop_bn = new Button(Stock.MediaStop);
        Button rw_bn = new Button(Stock.MediaRewind);
        Button fwd_bn = new Button(Stock.MediaForward);

        hbox.Add (play_bn);
        hbox.Add (pause_bn);
        hbox.Add (stop_bn);
        hbox.Add (rw_bn);
        hbox.Add (fwd_bn);

        play_bn.Clicked += OnPlayBnClicked;
        pause_bn.Clicked += OnPauseBnClicked;
        stop_bn.Clicked += OnStopBnClicked;
        rw_bn.Clicked += OnRewindBnClicked;
        fwd_bn.Clicked += OnForwardBnClicked;

        // show all
        window.ShowAll ();

        Application.Run ();
    }

    void OnDelete(object obj, DeleteEventArgs args)
    {
        Application.Quit ();
    }

    void OnPlayBnClicked(object obj, EventArgs args)
    {
        Console.WriteLine ("OnPlayBnClicked!");
    }

    void OnPauseBnClicked(object obj, EventArgs args)
    {
        Console.WriteLine ("OnPauseBnClicked!");
    }

    void OnStopBnClicked(object obj, EventArgs args)
    {
        Console.WriteLine ("OnStopBnClicked!");
    }

    void OnRewindBnClicked(object obj, EventArgs args)
    {
        Console.WriteLine ("OnRewindBnClicked!");
    }

    void OnForwardBnClicked(object obj, EventArgs args)
    {
        Console.WriteLine ("OnForwardBnClicked!");
    }
}; // Window