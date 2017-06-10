using System;
using System.Diagnostics;
using System.IO;
using System.IO.Pipes;
using System.Text;
using System.Threading;
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
    Socket socket;
    VBox   vbox;
    HBox   hbox;

    enum Status {
         INITIAL,
         PLAYING,
         PAUSED
    }

    Status status;
    String fifoName;
    StreamWriter fifoWriter;
    String videoFile;


    public AppWindow()
    {
        fifoName = "/tmp/fifo-" + Process.GetCurrentProcess().Id;
        Execute ("mkfifo", fifoName);
        NamedPipeClientStream client = new NamedPipeClientStream(fifoName);
        client.Connect();
        fifoWriter = new StreamWriter(client);
        status = Status.INITIAL;

        Application.Init ();
        window = new Window ("C# simple player!");
        window.DeleteEvent += OnDelete;
        window.SetDefaultSize (200, 200);

        // a vbox for player wnd + buttons
        vbox = new VBox (false, 4);
        window.Add (vbox);

        // menu bar
        MenuBar mb = new MenuBar();
        MenuItem file_item = new MenuItem("File");
        Menu file_menu = new Menu();
        MenuItem open_item = new MenuItem("Open");
        open_item.Activated += new EventHandler(OnOpenMenuItem);
        file_menu.Append (open_item);
        file_item.Submenu = file_menu;
        mb.Append (file_item);
        vbox.Add (mb);


        // player window
        socket = new Socket();
        socket.WidthRequest = 320;
        socket.HeightRequest = 240;
        socket.Visible = true;
        // socket.Realized += new EventHandler(OnVideoWidgetRealized);
        vbox.Add (socket);

        // a hbox for media buttons
        hbox = new HBox (true, 4);
        vbox.Add (hbox);


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

        Execute("unlink", fifoName);
    }

    void Execute(String exe, String args)
    {
        Console.WriteLine(exe + " " + args);
        Process proc = new Process();
        proc.StartInfo.FileName = exe;
        proc.StartInfo.Arguments = args;
        proc.StartInfo.UseShellExecute = false;
        proc.StartInfo.RedirectStandardOutput = true;
        proc.StartInfo.RedirectStandardInput = true;
        proc.StartInfo.RedirectStandardError = true;
        proc.StartInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;
        proc.StartInfo.CreateNoWindow = true; // display no window
        proc.Start();
    }

    void OnDelete(object obj, DeleteEventArgs args)
    {
        fifoWriter.WriteLine("q");
        fifoWriter.Flush();
        Thread.Sleep(500);
        Application.Quit ();
    }

    void OnOpenMenuItem(object obj, EventArgs args)
    {
        Console.WriteLine("OnOpenMenuItem!");

        Gtk.FileChooserDialog fc=
            new Gtk.FileChooserDialog("Choose the file to open",
                                      null,
                                      FileChooserAction.Open,
                                      "Cancel", ResponseType.Cancel,
                                      "Open",   ResponseType.Accept);

        if (fc.Run() == (int)ResponseType.Accept)
        {
            videoFile = fc.Filename;
        }

        fc.Destroy();
    }

    void OnPlayBnClicked(object obj, EventArgs args)
    {
        Console.WriteLine ("OnPlayBnClicked!");

        if (status == Status.INITIAL)
        {
            if (String.IsNullOrEmpty(videoFile) || !File.Exists(videoFile))
            {
                Console.WriteLine("Error on video path: " + videoFile);
                return;
            }

            status = Status.PLAYING;
            int wid = (int) socket.Id;
            string arguments = string.Format("-input file={0} " +
                                             "-wid {1} -vo x11 -really-quiet " +
                                             "-msglevel all=-1 {2}",
                                             fifoName, wid, videoFile);

            Console.WriteLine("mplayer " + arguments);



            System.Diagnostics.Process proc = new System.Diagnostics.Process();
            proc.StartInfo.FileName = @"/usr/bin/mplayer";
            proc.StartInfo.Arguments = arguments;
            proc.StartInfo.UseShellExecute = false;
            proc.StartInfo.RedirectStandardOutput = true;
            proc.StartInfo.RedirectStandardInput = true;
            proc.StartInfo.RedirectStandardError = true;
            proc.StartInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;
            proc.StartInfo.CreateNoWindow = true; // display no window
            proc.Start();
            // string output = proc.StandardOutput.ReadToEnd(); // result
            // proc.WaitForExit();
        }
        else if (status == Status.PLAYING)
            return;
        else if (status == Status.PAUSED)
        {
            status = Status.PLAYING;
            fifoWriter.WriteLine("p");
            fifoWriter.Flush();
            return;
        }
    }

    void OnPauseBnClicked(object obj, EventArgs args)
    {
        Console.WriteLine ("OnPauseBnClicked!");
        if (status == Status.INITIAL)
            return;
        status = Status.PAUSED;
        fifoWriter.WriteLine("p");
        fifoWriter.Flush();
    }

    void OnStopBnClicked(object obj, EventArgs args)
    {
        Console.WriteLine ("OnStopBnClicked!");
        if (status == Status.INITIAL)
            return;
        status = Status.INITIAL;
        fifoWriter.WriteLine("q");
        fifoWriter.Flush();
    }

    void OnRewindBnClicked(object obj, EventArgs args)
    {
        Console.WriteLine ("OnRewindBnClicked!");
        if (status == Status.INITIAL)
            return;
        fifoWriter.WriteLine("seek -20");
        fifoWriter.Flush();
    }

    void OnForwardBnClicked(object obj, EventArgs args)
    {
        Console.WriteLine ("OnForwardBnClicked!");
        if (status == Status.INITIAL)
            return;
        fifoWriter.WriteLine("seek +20");
        fifoWriter.Flush();
    }
}; // Window