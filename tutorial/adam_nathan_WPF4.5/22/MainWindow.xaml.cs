using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.ComTypes;
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
using Windows.Data.Xml.Dom;
using Windows.UI.Notifications;
using Microsoft.WindowsAPICodePack.Shell.PropertySystem;
using MS.WindowsAPICodePack.Internal;
using System.Runtime.InteropServices;

[ComImport, Guid("000214F9-0000-0000-C000-000000000046"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
interface IShellLinkW
{
    void GetPath(
        [Out(), MarshalAs(UnmanagedType.LPWStr)] StringBuilder pszFile,
        int cchMaxPath,
        IntPtr pfd,
        uint fFlags);
    void GetIDList(out IntPtr ppidl);
    void SetIDList(IntPtr pidl);
    void GetDescription(
        [Out(), MarshalAs(UnmanagedType.LPWStr)] StringBuilder pszFile,
        int cchMaxName);
    void SetDescription(
        [MarshalAs(UnmanagedType.LPWStr)] string pszName);
    void GetWorkingDirectory(
        [Out(), MarshalAs(UnmanagedType.LPWStr)] StringBuilder pszDir,
        int cchMaxPath
        );
    void SetWorkingDirectory(
        [MarshalAs(UnmanagedType.LPWStr)] string pszDir);
    void GetArguments(
        [Out(), MarshalAs(UnmanagedType.LPWStr)] StringBuilder pszArgs,
        int cchMaxPath);
    void SetArguments(
        [MarshalAs(UnmanagedType.LPWStr)] string pszArgs);
    void GetHotKey(out short wHotKey);
    void SetHotKey(short wHotKey);
    void GetShowCmd(out uint iShowCmd);
    void SetShowCmd(uint iShowCmd);
    void GetIconLocation(
        [Out(), MarshalAs(UnmanagedType.LPWStr)] out StringBuilder pszIconPath,
        int cchIconPath,
        out int iIcon);
    void SetIconLocation(
        [MarshalAs(UnmanagedType.LPWStr)] string pszIconPath,
        int iIcon);
    void SetRelativePath(
        [MarshalAs(UnmanagedType.LPWStr)] string pszPathRel,
        uint dwReserved);
    void Resolve(IntPtr hwnd, uint fFlags);
    void SetPath(string pszFile);
}

[ComImport, Guid("0000010b-0000-0000-C000-000000000046"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
interface IPersistFile
{
    string GetCurFile();
    [PreserveSig]
    uint IsDirty();
    void Load(string pszFileName, long dwMode);
    void Save(string pszFileName, bool fRemember);
    void SaveCompleted(string pszFileName);
}

[ComImport, Guid("886D8EEB-8CF2-4446-8D02-CDBA1DBDCF99"), InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
interface IPropertyStore
{
    uint GetCount();
    PropertyKey GetAt(uint propertyIndex);
    PropVariant GetValue([In] ref PropertyKey key);
    void SetValue([In] ref PropertyKey key, PropVariant pv);
    void Commit();
}

[ComImport, Guid("00021401-0000-0000-C000-000000000046"), ClassInterface(ClassInterfaceType.None)]
class ShellLink { }

namespace ToastNotifications
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        string appID = "Chapter22 Sample";
        public MainWindow()
        {
            InitializeComponent();

            PinToStart();
        }

        void PinToStart()
        {
            string file = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData), @"Microsoft\Windows\Start Menu\Programs\" + appID + ".lnk");
            if (File.Exists(file))
                return;

            // Create a shortcut that invokes this app with no arguments
            IShellLinkW shortcut = (IShellLinkW)new ShellLink();
            shortcut.SetPath(Process.GetCurrentProcess().MainModule.FileName);
            shortcut.SetArguments("");

            // Set the AppUserModelID
            using (PropVariant variant = new PropVariant(appID))
            {
                (shortcut as IPropertyStore).SetValue(SystemProperties.System.AppUserModel.ID, variant);
                (shortcut as IPropertyStore).Commit();
            }

            // Save the shortcut
            (shortcut as IPersistFile).Save(file, true);
        }

        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);
            //ScheduleToast();
            SendToast();
        }

        void SendToast()
        {
            // create a string with the toast template xml
            string xmlString = @"
<toast>
  <visual>
    <binding template='ToastImageAndText04'>
      <text id='1'>id='1': A non-wrapping header</text>
      <text id='2'>id='2': A non-wrapping line</text>
      <text id='3'>id='3': A non-wrapping line</text>
      <image id='1' src='file:///INSERT FULL PATH HERE/Assets/tileImage.jpg' />
    </binding>  
  </visual>
</toast>";

            // Load the content into an XML document
            XmlDocument document = new XmlDocument();
            document.LoadXml(xmlString);

            // Create a toast notification and send it
            ToastNotification notification = new ToastNotification(document);
            ToastNotificationManager.CreateToastNotifier(appID).Show(notification);
        }

        void ScheduleToast()
        {
            // create a string with the toast template xml
            string xmlString = @"
<toast>
  <visual>
    <binding template='ToastText01'>
      <text id='1'>Alert!</text>
    </binding>  
  </visual>
</toast>";

            // Load the content into an XML document
            XmlDocument document = new XmlDocument();
            document.LoadXml(xmlString);

            // Create a toast notification and show it 5 seconds from now
            ScheduledToastNotification notification = new ScheduledToastNotification(document, DateTimeOffset.Now + TimeSpan.FromSeconds(2));
            ToastNotificationManager.CreateToastNotifier(appID).AddToSchedule(notification);
        }
    }
}
