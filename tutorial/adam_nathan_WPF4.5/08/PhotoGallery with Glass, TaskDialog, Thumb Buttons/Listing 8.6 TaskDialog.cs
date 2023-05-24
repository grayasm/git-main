using System;
using System.Runtime.InteropServices;

    class TaskDialogHelper
    {
        [DllImport("comctl32.dll", PreserveSig = false, CharSet = CharSet.Unicode)]
        public static extern TaskDialogResult TaskDialog(IntPtr hwndParent, IntPtr hInstance,
            string title, string mainInstruction, string content,
            TaskDialogButtons buttons, TaskDialogIcon icon);
    }

    enum TaskDialogResult
    {
        Ok = 1,
        Cancel = 2,
        Retry = 4,
        Yes = 6,
        No = 7,
        Close = 8
    }

    [Flags]
    enum TaskDialogButtons
    {
        Ok = 0x0001,
        Yes = 0x0002,
        No = 0x0004,
        Cancel = 0x0008,
        Retry = 0x0010,
        Close = 0x0020
    }

enum TaskDialogIcon
{
    Warning = 65535,
    Error = 65534,
    Information = 65533,
    Shield = 65532
}