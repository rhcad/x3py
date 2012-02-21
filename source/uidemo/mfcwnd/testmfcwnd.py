#!/usr/bin/env python
# -*- coding: utf-8 -*-
# This uidemo illustrates how MFC UI interfaces can be used from wxPython.
# Renames this file as *.pyw to run without shell window.

import uidemo.mfcwnd as test
import wx

class MyPanel(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, -1)
        
        self._child = test.SimpleWnd("")
        self._child.createWnd(self.Handle, 0)
        win = wx.PyAxBaseWindow_FromHWND(self, self._child.getHandle())
        
        sizer = wx.BoxSizer(wx.HORIZONTAL)
        sizer.Add(win, proportion=1, flag=wx.EXPAND)
        self.SetSizer(sizer)
        
    @property
    def child(self):
        return self._child

class MyFrame(wx.Frame):
    def __init__(self, parent=None):
        wx.Frame.__init__(self, parent, title='Test UI', size=(800,600))
        self.panel = MyPanel(self)
        
        menuBar = wx.MenuBar()
        
        menu1 = wx.Menu()
        menu1.Append(102, "&Show Message", "Call the method 'ShowMessage' of the UI plugin")
        menu1.AppendSeparator()
        menu1.Append(101, "&Close", "Close this frame")
        menuBar.Append(menu1, "&Test")
        self.Bind(wx.EVT_MENU, self.CloseWindow, id=101)
        self.Bind(wx.EVT_MENU, self.OnShowMessage, id=102)
        
        self.SetMenuBar(menuBar)
        
    def CloseWindow(self, event):
        self.Close()

    def OnShowMessage(self, event):
        self.panel.child.showMessage()
        
if __name__=='__main__':
    app = wx.App()
    frame = MyFrame()
    frame.Show()
    app.MainLoop()
