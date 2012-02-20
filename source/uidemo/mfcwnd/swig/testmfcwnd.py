# This uidemo illustrates how MFC UI interfaces can be used from Python.

import wx
import uidemo.mfcwnd as test

class MyPanel(wx.Panel):
    def __init__(self, parent):
        wx.Panel.__init__(self, parent, -1)
        self._child = test.Simple("")
        
    @property
    def child(self):
        return self._child
    
    def createWnd(self):
        self._child.createWnd(self.Handle, 0)
        self._win = wx.PyAxBaseWindow_FromHWND(self, self._child.getHandle())
        self.PostCreate(self._win)
        
class MyFrame(wx.Frame):
    def __init__(self, parent=None):
        wx.Frame.__init__(self, parent, title='Test UI', size=(800,600))
        self.panel = MyPanel(self)

        button = wx.Button(self.panel, 1001, "ShowMessage")
        button.SetPosition((15, 15))
        self.Bind(wx.EVT_BUTTON, self.OnShowMessage, button)
    
    def createWnd(self):
        self.panel.createWnd()
        
    def OnShowMessage(self, event):
        self.panel.child.showMessage()
        
if __name__=='__main__':
    app = wx.App()
    frame = MyFrame()
    frame.Show()
    frame.createWnd()
    app.MainLoop()
