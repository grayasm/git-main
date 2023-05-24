virtual bool TranslateAccelerator(MSG% msg, ModifierKeys modifiers) override
{
    if (msg.message == WM_KEYDOWN && msg.wParam == IntPtr(VK_TAB))
    {
        // Handle Shift+Tab
        if (GetKeyState(VK_SHIFT))
        {
            if (GetFocus() == hwndOfFirstControl)
            {
                // We're at the beginning, so send focus to the previous WPF element
                return this->KeyboardInputSite->OnNoMoreTabStops(
                gcnew TraversalRequest(FocusNavigationDirection::Previous));
            }
            else
                return (SetFocus(hwndOfPreviousControl) != NULL);
        }
        // Handle Shift without Tab
        else
        {
            if (GetFocus() == hwndOfLastControl)
            {
                // We're at the end, so send focus to the next WPF element
                return this->KeyboardInputSite->OnNoMoreTabStops(
                gcnew TraversalRequest(FocusNavigationDirection::Next));
            }
            else
                return (SetFocus(hwndOfNextControl) != NULL);
        }
    }
}